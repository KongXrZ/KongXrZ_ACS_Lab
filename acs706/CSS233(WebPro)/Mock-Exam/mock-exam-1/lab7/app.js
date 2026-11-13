const form = document.getElementById("form");
const result_label = document.getElementById("result-label");
const result = document.getElementById("result");

const name_error = document.getElementById("error-name");
const email_error = document.getElementById("error-email");
const score_error = document.getElementById("error-score");

form.addEventListener("submit", (event) => {
  event.preventDefault();

  const name = document.getElementById("name").value;
  const email = document.getElementById("email").value;
  const score = document.getElementById("score").value;

  if (!name) {
    name_error.innerText = "name must have value";
    return;
  }
  if (!email) {
    email_error.innerText = "email must have value";
    return;
  }
  if (!score) {
    score_error.innerText = "score must have value";
    return;
  }

  if (score < 0 || score > 100) {
    score_error.innerText = "score value must 1-100";
    return;
  }

  const status = Number(score) >= 50 ? "Pass" : "Fail";
  const res = `USER: ${name.trim().toUpperCase()} | Contact: ${email.trim()} | Status: ${status}`;

  name_error.innerText = "";
  email_error.innerText = "";
  score_error.innerText = "";

  result_label.classList.remove("inactive");
  result_label.classList.add("active");
  result.classList.remove("inactive");
  result.classList.add("active");

  result.innerText = res;
});
