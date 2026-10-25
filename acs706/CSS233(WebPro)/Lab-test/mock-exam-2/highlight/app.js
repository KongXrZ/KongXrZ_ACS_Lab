const list = document.getElementById("list");
const highlight = document.getElementById("highlight");
const list_img = document.querySelectorAll(".list-img");

list.addEventListener("click", (event) => {
  const value = event.target.getAttribute("src");
  if (value) {
    highlight.setAttribute("src", value);
    list_img.forEach((img) => img.classList.remove("active"));
    event.target.classList.add("active");
  }
});
