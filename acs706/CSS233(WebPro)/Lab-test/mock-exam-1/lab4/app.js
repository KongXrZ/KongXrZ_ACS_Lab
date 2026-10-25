const messages = [
  "Keep going.",
  "Believe in yourself.",
  "Start before you're ready.",
  "Small progress is still progress.",
  "Focus on what you can control.",
];

const text_random = document.getElementById("text-random");

function getRandomInt(max) {
  return Math.floor(Math.random() * max);
}

text_random.innerText = messages[getRandomInt(5)];
