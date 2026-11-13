const delay = async () => {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve(true);
    }, 1000);
  });
};

async function loadUsers(url) {
  const users = await fetch(url);
  const data = await users.json();

  await delay();

  return data;
}

const load_btn = document.getElementById("btn-load");
const btn_empty = document.getElementById("btn-empty");
const btn_error = document.getElementById("btn-error");

const loading = document.getElementById("loading");

let isLoading = false;
let isError = false;
let data;

const fetchData = async (url) => {
  isLoading = true;

  load_btn.disabled = true;
  btn_empty.disabled = true;
  btn_error.disabled = true;

  loading.style.display = "block";

  const list = document.getElementById("user-list");

  const task_remain = document.querySelectorAll("li");
  const text_remain = document.querySelectorAll("p");

  task_remain.forEach((el_remain) => {
    list.removeChild(el_remain);
  });

  text_remain.forEach((text) => {
    if (text.classList.contains("error") || text.classList.contains("empty")) {
      list.removeChild(text);
    }
  });

  isError = false;

  try {
    data = await loadUsers(url);
  } catch (error) {
    isError = true;
  }

  load_btn.disabled = false;
  btn_empty.disabled = false;
  btn_error.disabled = false;

  loading.style.display = "none";

  if (isError) {
    const el = document.createElement("p");
    el.classList.add("error");
    const text = "เกิดข้อผิดพลาด กรุณาลองใหม่";
    el.innerText = text;
    list.appendChild(el);
    return;
  }

  if (data.length === 0) {
    const el = document.createElement("p");
    el.classList.add("empty");
    const text = "ไม่พบรายชื่อ";
    el.innerText = text;
    list.appendChild(el);
    return;
  }

  data.map((user) => {
    const el = document.createElement("li");
    el.classList.add("task");
    const text = `${user.name} | ${user.email}`;
    el.innerText = text;
    list.appendChild(el);
  });
};

const url = "./users.json";
const url_empty = "./empty-users.json";
const url_error = "missing-users.json";

load_btn.addEventListener("click", async () => {
  return fetchData(url);
});

btn_empty.addEventListener("click", async () => {
  return fetchData(url_empty);
});

btn_error.addEventListener("click", async () => {
  return fetchData(url_error);
});
