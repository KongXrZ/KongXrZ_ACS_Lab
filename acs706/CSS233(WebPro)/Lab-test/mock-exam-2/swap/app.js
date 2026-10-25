const box_1 = document.getElementById("box-1");
const box_2 = document.getElementById("box-2");
const box_3 = document.getElementById("box-3");
const box_4 = document.getElementById("box-4");
const parent = document.getElementById("parent");

parent.addEventListener("click", () => {
  box_1.classList.toggle("active");
  box_2.classList.toggle("active");
  box_3.classList.toggle("active");
  box_4.classList.toggle("active");
});
