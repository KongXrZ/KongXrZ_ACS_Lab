const menu = document.getElementById("menu");
const container = document.getElementById("container");
const all_menu = document.querySelectorAll(".list");

const profileMenu = `
    <p>My Profile</p>
    <hr />
    <dl>
        <dt>Name</dt>
        <dd>Alex Morgan</dd>

        <dt>Role</dt>
        <dd>Frontend Developer</dd>
    </dl>`;

const projectsMenu = `
    <p>My Projects</p>
    <hr />
    <dl>
        <dt>#1</dt>
        <dd>DTRACK</dd>
    
        <dt>#2</dt>
        <dd>Bangmod Guesser</dd>
    </dl>`;

const settingMenu = `
    <p>My Projects</p>
    <hr />
    <dl>
        <dt>Sound</dt>
        <dd>50%</dd>
    
        <dt>Quality</dt>
        <dd>High</dd>
    </dl>`;

menu.addEventListener("click", (event) => {
  if (event.target.classList.contains("list")) {
    all_menu.forEach((e) => e.classList.remove("active"));
    event.target.classList.add("active");
  }
  if (event.target.id === "profile") {
    container.innerHTML = profileMenu;
  } else if (event.target.id === "projects") {
    container.innerHTML = projectsMenu;
  } else if (event.target.id === "setting") {
    container.innerHTML = settingMenu;
  }
});
