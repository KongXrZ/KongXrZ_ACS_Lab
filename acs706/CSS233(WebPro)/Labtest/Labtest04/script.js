// Keep this API unchanged
const COURSE_NAMES=['Web Programming','Web Design','Web Services','Database Systems','Software Engineering','Network Security','Advanced Web Applications'];
let requestCount=0;
function searchCourses(keyword){
  requestCount++;
  document.querySelector('#requests').textContent=String(requestCount);
  const q=keyword.toLowerCase();
  const delay=q==='web'?900:q==='web p'?600:q==='web pro'?170:300;
  return new Promise(resolve=>setTimeout(()=>resolve(COURSE_NAMES.filter(c=>c.toLowerCase().includes(q))),delay));
}
const input=document.querySelector('#query');
const status=document.querySelector('#status');
const results=document.querySelector('#results');

