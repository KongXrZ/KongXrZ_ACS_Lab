require("dotenv").config();

const express = require("express");
const session = require("express-session");
const bcrypt = require("bcryptjs");
const crypto = require("node:crypto");
const path = require("node:path");
const nodemailer = require("nodemailer");

const app = express();
const PORT = Number(process.env.PORT || 3000);
const isProduction = process.env.NODE_ENV === "production";
const SESSION_SECRET =
  process.env.SESSION_SECRET || "dev-only-replace-this-session-secret-123456";
const OTP_SECRET =
  process.env.OTP_SECRET || "dev-only-replace-this-otp-secret-123456789";
const OTP_TTL_MS = 5 * 60 * 1000;
const MAX_OTP_ATTEMPTS = 5;
const pendingOtps = new Map();

if (
  isProduction &&
  (!process.env.SESSION_SECRET || !process.env.OTP_SECRET ||
    SESSION_SECRET.length < 32 || OTP_SECRET.length < 32)
) {
  throw new Error(
    "Production requires SESSION_SECRET and OTP_SECRET (at least 32 characters each)",
  );
}
if (isProduction && !process.env.SMTP_HOST) {
  throw new Error("Configure SMTP_HOST before running in production");
}

const demoUser = {
  username: process.env.DEMO_USERNAME || "student",
  email: process.env.DEMO_EMAIL || "student@example.com",
  passwordHash: bcrypt.hashSync(
    process.env.DEMO_PASSWORD || "Password123!",
    12,
  ),
};

const mailer = process.env.SMTP_HOST
  ? nodemailer.createTransport({
      host: process.env.SMTP_HOST,
      port: Number(process.env.SMTP_PORT || 587),
      secure: process.env.SMTP_SECURE === "true",
      ...(process.env.SMTP_USER && process.env.SMTP_PASS
        ? { auth: { user: process.env.SMTP_USER, pass: process.env.SMTP_PASS } }
        : {}),
    })
  : null;

async function sendOtp(email, code) {
  if (!mailer) {
    if (isProduction) throw new Error("SMTP is not configured");
    console.log(`\n[DEV ONLY] OTP for ${email}: ${code}\n`);
    return;
  }
  await mailer.sendMail({
    from: process.env.SMTP_FROM || "OTP Demo <no-reply@example.com>",
    to: email,
    subject: "Your one-time login code",
    text: `Your login code is ${code}. It expires in 5 minutes. Do not share it.`,
  });
}

function maskEmail(email) {
  const [local, domain] = email.split("@");
  if (!domain) return "your email";
  return `${local.slice(0, 2)}***@${domain}`;
}

function otpHash(code, salt) {
  return crypto
    .createHmac("sha256", OTP_SECRET)
    .update(`${salt}:${code}`)
    .digest("hex");
}

function sessionRegenerate(req) {
  return new Promise((resolve, reject) =>
    req.session.regenerate((error) => (error ? reject(error) : resolve())),
  );
}

function sessionSave(req) {
  return new Promise((resolve, reject) =>
    req.session.save((error) => (error ? reject(error) : resolve())),
  );
}

const cookieOptions = {
  httpOnly: true,
  sameSite: "strict",
  secure: isProduction,
  maxAge: 60 * 60 * 1000,
};

if (isProduction) app.set("trust proxy", 1);
app.disable("x-powered-by");
app.use(express.json({ limit: "10kb" }));
app.use(
  session({
    name: "otp.sid",
    secret: SESSION_SECRET,
    resave: false,
    saveUninitialized: false,
    cookie: cookieOptions,
  }),
);
app.post("/api/auth/login", async (req, res, next) => {
  try {
    const { username, password } = req.body || {};
    if (
      typeof username !== "string" ||
      typeof password !== "string" ||
      !username.trim() ||
      !password
    ) {
      return res.status(400).json({ error: "กรุณากรอก Username และ Password" });
    }

    const validPassword = await bcrypt.compare(password, demoUser.passwordHash);
    if (username !== demoUser.username || !validPassword) {
      return res
        .status(401)
        .json({ error: "Username หรือ Password ไม่ถูกต้อง" });
    }

    const code = String(crypto.randomInt(0, 1_000_000)).padStart(6, "0");
    const ref = crypto.randomBytes(32).toString("hex");
    const salt = crypto.randomBytes(16).toString("hex");
    const pending = {
      salt,
      otpHash: otpHash(code, salt),
      expiresAt: Date.now() + OTP_TTL_MS,
      attempts: 0,
    };

    try {
      await sendOtp(demoUser.email, code);
    } catch (error) {
      console.error("Could not send OTP:", error.message);
      return res.status(502).json({ error: "ส่ง OTP ทางอีเมลไม่สำเร็จ" });
    }

    pendingOtps.set(ref, pending);
    setTimeout(() => pendingOtps.delete(ref), Math.max(0, pending.expiresAt - Date.now())).unref();
    return res.json({
      message: "ส่ง OTP แล้ว",
      ref,
      email: maskEmail(demoUser.email),
    });
  } catch (error) {
    next(error);
  }
});

app.post("/api/auth/verify-otp", async (req, res, next) => {
  try {
    const { ref, otp: code } = req.body || {};
    const pending = pendingOtps.get(ref);
    if (!pending)
      return res
        .status(401)
        .json({ error: "ไม่พบ OTP หรือ OTP หมดอายุ กรุณา Login ใหม่" });

    if (Date.now() >= pending.expiresAt) {
      pendingOtps.delete(ref);
      return res.status(401).json({ error: "OTP หมดอายุ กรุณา Login ใหม่" });
    }

    if (typeof code !== "string" || !/^\d{6}$/.test(code)) {
      return res.status(400).json({ error: "OTP ต้องเป็นตัวเลข 6 หลัก" });
    }

    const actualHash = Buffer.from(otpHash(code, pending.salt), "hex");
    const expectedHash = Buffer.from(pending.otpHash, "hex");
    if (!crypto.timingSafeEqual(actualHash, expectedHash)) {
      pending.attempts += 1;
      const remaining = MAX_OTP_ATTEMPTS - pending.attempts;
      if (remaining === 0) pendingOtps.delete(ref);
      return res.status(remaining === 0 ? 403 : 401).json({
        error:
          remaining === 0
            ? "OTP ผิดครบ 5 ครั้ง กรุณา Login ใหม่"
            : `OTP ไม่ถูกต้อง (เหลืออีก ${remaining} ครั้ง)`,
      });
    }

    pendingOtps.delete(ref);
    await sessionRegenerate(req);
    req.session.user = {
      username: demoUser.username,
      email: demoUser.email,
      loggedInAt: new Date().toISOString(),
    };
    await sessionSave(req);
    return res.json({ message: "ยืนยัน OTP สำเร็จ" });
  } catch (error) {
    next(error);
  }
});

app.get("/api/profile", (req, res) => {
  if (req.session.user) return res.json(req.session.user);
  return res.status(401).json({ error: "ยังไม่ได้เข้าสู่ระบบ" });
});

app.post("/api/auth/logout", (req, res, next) => {
  req.session.destroy((error) => {
    if (error) return next(error);
    res.clearCookie("otp.sid", {
      path: "/",
      httpOnly: true,
      sameSite: "strict",
      secure: isProduction,
    });
    res.json({ message: "ออกจากระบบแล้ว" });
  });
});

app.get(["/profile", "/profile.html"], (req, res) => {
  if (!req.session.user) {
    return res.redirect("/login");
  }
  return res.sendFile(path.join(__dirname, "profile.html"));
});
app.get(["/app.js", "/styles.css"], (req, res) =>
  res.sendFile(path.join(__dirname, path.basename(req.path))),
);
app.get("/", (_req, res) => res.redirect("/login"));
app.get(["/login", "/login.html"], (_req, res) =>
  res.sendFile(path.join(__dirname, "login.html")),
);
app.get(["/otp", "/otp.html"], (_req, res) => res.sendFile(path.join(__dirname, "otp.html")));
app.use((error, _req, res, _next) => {
  if (error.type === "entity.parse.failed") {
    return res.status(400).json({ error: "JSON ไม่ถูกต้อง" });
  }
  console.error(error);
  return res.status(500).json({ error: "เกิดข้อผิดพลาดภายใน Server" });
});

if (require.main === module) {
  app.listen(PORT, () => console.log(`Open http://localhost:${PORT}/login`));
}

module.exports = app;