const form = document.getElementById("todo-form");
const list = document.getElementById("todo-list");

form.addEventListener("submit", (event) => {
  event.preventDefault();
  const input = document.getElementById("todo-input");
  const value = document.getElementById("todo-input").value;
  const el = document.createElement("li");
  el.classList.add("task");
  el.innerHTML = `
          <p>${value}</p>
          <button id="del-btn">Delete</button>
        `;
  list.appendChild(el);
  input.value = "";
});

list.addEventListener("click", (event) => {
  const el = event.target.closest("li");
  el.remove();
});
