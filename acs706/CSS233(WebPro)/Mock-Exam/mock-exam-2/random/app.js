const quotes = [
  {
    text: "Stay hungry, stay foolish.",
    author: "Steve Jobs",
  },
  {
    text: "Simplicity is the soul of efficiency.",
    author: "Austin Freeman",
  },
  {
    text: "Code is like humor. When you have to explain it, it's bad.",
    author: "Cory House",
  },
  {
    text: "First, solve the problem. Then, write the code.",
    author: "John Johnson",
  },
];

const quote = document.getElementById("quote");
const author = document.getElementById("author");

const random_num = Math.floor(Math.random() * quotes.length);

quote.innerText = quotes[random_num].text;
author.innerText = quotes[random_num].author;
