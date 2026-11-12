import express from "express";
import { timingSafeEqual } from "node:crypto";
import { pool } from "./db.js";

const app = express();

app.use(express.json());
app.use(express.static("public"));

function parseCourseId(rawId) {
  const id = Number(rawId);

  return Number.isSafeInteger(id) && id > 0
    ? id
    : null;
}

function validateCourse(data) {
  return (
    typeof data?.name === "string" &&
    data.name.trim().length > 0 &&
    data.name.length <= 150 &&
    Number.isInteger(data.credits) &&
    data.credits >= 1 &&
    data.credits <= 6
  );
}

function requireBearerToken(req, res, next) {
  const expectedToken = process.env.API_TOKEN;

  if (!expectedToken) {
    return res.status(503).json({
      error: "API authorization is not configured"
    });
  }

  const authorization = req.get("authorization")?.trim() ?? "";
  const [scheme, providedToken, ...extraParts] = authorization.split(/\s+/);

  if (
    scheme?.toLowerCase() !== "bearer" ||
    !providedToken ||
    extraParts.length > 0
  ) {
    res.set("WWW-Authenticate", "Bearer");
    return res.status(401).json({ error: "Unauthorized" });
  }

  const expected = Buffer.from(expectedToken);
  const provided = Buffer.from(providedToken);

  if (
    provided.length !== expected.length ||
    !timingSafeEqual(provided, expected)
  ) {
    res.set("WWW-Authenticate", "Bearer");
    return res.status(401).json({ error: "Unauthorized" });
  }

  next();
}

app.get("/api/courses", async (req, res) => {
  try {
    const result = await pool.query(
      `SELECT id, name, credits
       FROM courses
       ORDER BY id`
    );

    res.status(200).json(result.rows);
  } catch (error) {
    console.error(error);

    res.status(500).json({
      error: "Unable to retrieve courses"
    });
  }
});

app.get("/api/courses/:id", async (req, res) => {
  const id = parseCourseId(req.params.id);

  if (id === null) {
    return res.status(400).json({
      error: "Invalid course ID"
    });
  }

  try {
    const result = await pool.query(
      `SELECT id, name, credits
       FROM courses
       WHERE id = $1`,
      [id]
    );

    if (result.rows.length === 0) {
      return res.status(404).json({
        error: "Course not found"
      });
    }

    res.status(200).json(result.rows[0]);
  } catch (error) {
    console.error(error);

    res.status(500).json({
      error: "Unable to retrieve course"
    });
  }
});

app.post("/api/courses", async (req, res) => {
  if (!validateCourse(req.body)) {
    return res.status(400).json({
      error: "Invalid course data"
    });
  }

  const { name, credits } = req.body;

  try {
    const result = await pool.query(
      `INSERT INTO courses (name, credits)
       VALUES ($1, $2)
       RETURNING id, name, credits`,
      [name.trim(), credits]
    );

    res.status(201).json(result.rows[0]);
  } catch (error) {
    console.error(error);

    res.status(500).json({
      error: "Unable to create course"
    });
  }
});

app.put("/api/courses/:id", requireBearerToken, async (req, res) => {
  const id = parseCourseId(req.params.id);

  if (id === null) {
    return res.status(400).json({ error: "Invalid course ID" });
  }

  if (!validateCourse(req.body)) {
    return res.status(400).json({ error: "Invalid course data" });
  }

  const { name, credits } = req.body;

  try {
    const result = await pool.query(
      `UPDATE courses
       SET name = $1, credits = $2
       WHERE id = $3
       RETURNING id, name, credits`,
      [name.trim(), credits, id]
    );

    if (result.rows.length === 0) {
      return res.status(404).json({ error: "Course not found" });
    }

    return res.status(200).json(result.rows[0]);
  } catch (error) {
    console.error("PUT /api/courses/:id:", error);
    return res.status(500).json({ error: "Unable to update course" });
  }
});

app.delete("/api/courses/:id", requireBearerToken, async (req, res) => {
  const id = parseCourseId(req.params.id);

  if (id === null) {
    return res.status(400).json({ error: "Invalid course ID" });
  }

  try {
    const result = await pool.query(
      `DELETE FROM courses
       WHERE id = $1
       RETURNING id`,
      [id]
    );

    if (result.rows.length === 0) {
      return res.status(404).json({ error: "Course not found" });
    }

    return res.status(204).send();
  } catch (error) {
    console.error("DELETE /api/courses/:id:", error);
    return res.status(500).json({ error: "Unable to delete course" });
  }
});

const port = Number(process.env.PORT || 3000);

app.listen(port, () => {
  console.log(`Server running on port ${port}`);
});
