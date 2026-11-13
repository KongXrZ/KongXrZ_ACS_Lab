const btn_all = document.querySelectorAll("#btn");

btn_all.forEach((btn) => {
  btn.addEventListener("click", () => {
    const el = btn.closest(".list-container").querySelector(".detail");
    const arrow = btn.closest(".list").querySelector("#btn");
    if (getComputedStyle(el).display == "none") {
      el.style.display = "block";
      arrow.classList.remove("inactive");
      arrow.classList.add("active");
    } else if (getComputedStyle(el).display == "block") {
      el.style.display = "none";
      arrow.classList.remove("active");
      arrow.classList.add("inactive");
    }
  });
});
