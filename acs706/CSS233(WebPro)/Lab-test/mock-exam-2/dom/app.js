const list = document.getElementById("student-list");
const input = document.getElementById("student-input");
const count = document.getElementById("count");

let total = 0;

const handleSubmit = (event) => {
  event.preventDefault();

  const value = document.getElementById("student-input").value;

  if (value === "") {
    return;
  }

  const el = document.createElement("li");
  el.innerHTML = `${value} <button class="delete-btn" id="delete-btn"> Delete </button>`;
  list.appendChild(el);
  total += 1;
  count.innerText = `Total: ${total}`;

  input.value = "";
};

const form = document.getElementById("student-form");

form.addEventListener("submit", (event) => handleSubmit(event));

list.addEventListener("click", (event) => {
  if (event.target.classList.value === "delete-btn") {
    event.target.closest("li").remove();
  }
});
