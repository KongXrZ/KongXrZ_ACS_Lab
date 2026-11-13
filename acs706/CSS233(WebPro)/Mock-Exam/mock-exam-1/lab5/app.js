const open_btn = document.getElementById("open-btn");
const cancel_btn = document.getElementById("cancel-btn");
const del_btn = document.getElementById("del-btn");
const modal = document.getElementById("modal");
const alert = document.getElementById("alert");
const close_btn = document.getElementById("close-btn");

const container = document.getElementById("container");

container.addEventListener("click", (event) => {
  if (event.target === container) {
    modal.style.transform = "scale(0)";
    alert.style.transform = "scale(0)";
  }
});

open_btn.addEventListener("click", () => {
  modal.style.transform = "scale(1)";
});

cancel_btn.addEventListener("click", () => {
  modal.style.transform = "scale(0)";
});

del_btn.addEventListener("click", () => {
  modal.style.transform = "scale(0)";
  alert.style.transform = "scale(1)";
});

close_btn.addEventListener("click", () => {
  alert.style.transform = "scale(0)";
});
