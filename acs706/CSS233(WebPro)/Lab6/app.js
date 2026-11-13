const express = require("express");
const app = express();

app.use(express.json());

const books = [];


app.get("/", (req, res) => {
    res.send("Hello backend!");
});

app.get("/books", (req, res) => {
    res.json(books);
});

app.post("/books", (req, res) => {
    const title = req.body?.title;
    if (typeof title !== "string" || !title.trim()) {
        return res.status(400).json({ error: "Title required" });
    }
    const book = { id: books.length + 1, title: title.trim() };
    books.push(book);
    res.status(201).json(book);
});

app.listen(3000, () => {
    console.log("http://localhost:3000");
});
// Explain what happens to the data when the server restarts
// เมื่อrestart server ข้อมูลหนังสือทั้งหมดจะหายไป เพราะเก็บข้อมูลไว้ในarrayซึ่งอยู่ในRAMเมื่อถูกสร้างใหม่จากการrestartข้อมูลเดิมก็จะหายไปเหลือแค่arrayว่างจากserver (ถ้าเราฝังค่าไว้ในserver ค่านั้นก็จะไม่หายเมื่อถูกrestart server แต่ถ้าเราเก็บไว้ในRAMมันจะหายไปเมื่อserverถูกrestart)