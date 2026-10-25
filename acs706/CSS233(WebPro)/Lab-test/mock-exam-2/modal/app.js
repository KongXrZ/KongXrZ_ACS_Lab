const open_btn = document.getElementById("open-btn");
const close_btn = document.getElementById("close-btn");

open_btn.addEventListener("click", () => {
  const modal = document.getElementById("modal");
  modal.classList.remove("inactive");
  modal.classList.add("active");
});

close_btn.addEventListener("click", () => {
  const modal = document.getElementById("modal");
  modal.classList.remove("active");
  modal.classList.add("inactive");
});
