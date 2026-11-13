const container = document.getElementById("container");
const stars = document.querySelectorAll(".star");

stars.forEach((star, selected) => {
  star.addEventListener("click", () => {
    stars.forEach((star, check) => {
      if (check <= selected) {
        star.classList.add("active");
      } else {
        star.classList.remove("active");
      }
    });
  });
});
