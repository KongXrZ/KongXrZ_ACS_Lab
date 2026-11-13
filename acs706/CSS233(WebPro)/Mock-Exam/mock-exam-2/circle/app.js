const parent = document.getElementById("parent");
const child_1 = document.getElementById("child-1");
const child_2 = document.getElementById("child-2");
const btn = document.getElementById("btn");

parent.addEventListener("click", (event) => {
  if (
    (parent.classList.contains("active") &&
      event.target.classList.value.includes("child-1") &&
      child_1.classList.contains("active")) ||
    (parent.classList.contains("active") &&
      event.target.classList.value.includes("child-2") &&
      child_2.classList.contains("active"))
  ) {
    return;
  }

  if (event.target.classList.value.includes("parent")) {
    child_1.classList.remove("active");
    child_2.classList.remove("active");
  }

  parent.classList.toggle("active");
});

child_1.addEventListener("click", (event) => {
  if (
    child_1.classList.contains("active") &&
    event.target.classList.value.includes("child-2") &&
    child_2.classList.contains("active")
  ) {
    return;
  }
  if (event.target.classList.value.includes("child-1")) {
    child_2.classList.remove("active");
  }
  child_1.classList.toggle("active");
});

child_2.addEventListener("click", () => {
  child_2.classList.toggle("active");
});

btn.addEventListener("click", () => {
  parent.classList.remove("active");
  child_1.classList.remove("active");
  child_2.classList.remove("active");
});
