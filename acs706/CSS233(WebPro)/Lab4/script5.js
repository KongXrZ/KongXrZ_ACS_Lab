const box = document.querySelector("#counter-box");
const btnIncrease = document.querySelector("#btn-increase");
const btnReset = document.querySelector("#btn-reset");
const btnToggle = document.querySelector("#btn-toggle");

let count = 0;

const increment = () => {
    count++;
    box.textContent = count;
};

const reset = () => {
    count = 0;
    box.textContent = count;
    if (box.classList.contains("active")) {
        box.classList.remove("active");
    }
};

const toggle = () => {
    box.classList.toggle("active");
};

btnIncrease.addEventListener("click", increment);
btnReset.addEventListener("click", reset);
btnToggle.addEventListener("click", toggle);