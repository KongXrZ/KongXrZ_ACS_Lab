const all_btn = document.querySelectorAll("#btn");
const accordian = document.querySelectorAll(".accordian");

all_btn.forEach((btn) => {
  btn.addEventListener("click", (event) => {
    const current = event.currentTarget.parentElement.parentElement;
    const isActive = current.classList.contains("active");

    accordian.forEach((el) => {
      el.classList.remove("active");
    });
    all_btn.forEach((el) => {
      el.classList.remove("arrow-active");
    });
    if (!isActive) {
      current.classList.add("active");
      event.currentTarget.classList.add("arrow-active");
    }
  });
});
