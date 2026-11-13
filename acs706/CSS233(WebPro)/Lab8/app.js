"use strict";

const statusElement = document.querySelector("[data-status]");

function showError(error) {
  statusElement.hidden = false;
  statusElement.replaceChildren();

  const heading = document.createElement("strong");
  heading.textContent = error.status ? `HTTP ${error.status}` : "NETWORK ERROR";
  const message = document.createElement("span");
  message.textContent = error.message || "เกิดข้อผิดพลาด กรุณาลองอีกครั้ง";
  statusElement.append(heading, message);
}

function clearError() {
  statusElement.hidden = true;
  statusElement.replaceChildren();
}

async function api(url, options = {}) {
  let response;
  try {
    response = await fetch(url, {
      ...options,
      credentials: "same-origin",
      headers: {
        "Content-Type": "application/json",
        ...(options.headers || {}),
      },
    });
  } catch (_error) {
    throw { status: 0, message: "ไม่สามารถเชื่อมต่อ Server ได้" };
  }

  const data = await response.json().catch(() => ({}));
  if (!response.ok) {
    throw { status: response.status, message: data.error || "คำขอไม่สำเร็จ" };
  }
  return data;
}

function withLoading(button, operation) {
  button.disabled = true;
  return operation().finally(() => {
    button.disabled = false;
  });
}

const page = document.body.dataset.page;

if (page === "login") {
  const form = document.getElementById("login-form");
  form.addEventListener("submit", async (event) => {
    event.preventDefault();
    clearError();
    const username = form.elements.username.value.trim();
    const password = form.elements.password.value;
    await withLoading(form.querySelector("button"), async () => {
      try {
        const data = await api("/api/auth/login", {
          method: "POST",
          body: JSON.stringify({ username, password }),
        });
        sessionStorage.setItem("otpRef", data.ref);
        sessionStorage.setItem("otpEmail", data.email);
        window.location.assign("/otp");
      } catch (error) {
        showError(error);
      }
    });
  });
}

if (page === "otp") {
  const ref = sessionStorage.getItem("otpRef");
  if (!ref) {
    window.location.replace("/login");
  }
  document.getElementById("masked-email").textContent =
    sessionStorage.getItem("otpEmail") || "อีเมลของคุณ";

  const form = document.getElementById("otp-form");
  const otpInput = document.getElementById("otp");
  otpInput.addEventListener("input", () => {
    otpInput.value = otpInput.value.replace(/\D/g, "").slice(0, 6);
  });
  form.addEventListener("submit", async (event) => {
    event.preventDefault();
    clearError();
    await withLoading(form.querySelector("button"), async () => {
      try {
        await api("/api/auth/verify-otp", {
          method: "POST",
          body: JSON.stringify({ ref, otp: otpInput.value }),
        });
        sessionStorage.removeItem("otpRef");
        sessionStorage.removeItem("otpEmail");
        window.location.assign("/profile");
      } catch (error) {
        showError(error);
      }
    });
  });
}

if (page === "profile") {
  api("/api/profile")
    .then((data) => {
      document.getElementById("profile-username").textContent = data.username;
      document.getElementById("profile-email").textContent = data.email;
      document.getElementById("profile-time").textContent = new Date(
        data.loggedInAt,
      ).toLocaleString("th-TH");
      document.getElementById("profile-data").hidden = false;
    })
    .catch(showError)
    .finally(() => {
      document.getElementById("loading-profile").hidden = true;
    });

  const logout = document.getElementById("logout-button");
  logout.addEventListener("click", () => {
    clearError();
    withLoading(logout, async () => {
      try {
        await api("/api/auth/logout", { method: "POST" });
        window.location.replace("/login");
      } catch (error) {
        showError(error);
      }
    });
  });
}