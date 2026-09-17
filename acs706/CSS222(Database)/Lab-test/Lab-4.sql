use sakila;

--HW_1
--List all films along with their language name.
--แสดงfilmทั้งหมดพร้อมกับ language name
SELECT film.*, language.name AS language_name
FROM film 
JOIN language USING(language_id);
-- ใช้ JOIN เพื่อเชื่อมตาราง film และ language โดยใช้ language_id เป็นตัวเชื่อม และใช้ AS เพื่อเปลี่ยนชื่อคอลัมน์ name เป็น language_name

--HW_2
--Show the first name and last name of customers along with the city they live in.
--แสดง first name และ last name ของ customers พร้อมกับ city ที่พวกเขาอาศัยอยู่
SELECT first_name, last_name, city 
FROM customer 
JOIN address USING(address_id)
JOIN city USING(city_id);
-- ใช้ JOIN เพื่อเชื่อมตาราง customer กับ address ด้วย address_id 
--และใช้ JOIN เพื่อเชื่อมตาราง customer กับ city โดยใช้ city_id เป็นตัวเชื่อม

--HW_3
--Find the titles of films and the names of the actors who acted in them.
-- หา title ของ film และ names ของ actors ที่แสดงในfilmเหล่านั้น
SELECT title, first_name, last_name 
FROM film 
JOIN film_actor USING(film_id)
JOIN actor USING(actor_id);
-- ใช้ JOIN เพื่อเชื่อมตาราง film กับ film_actor ด้วย film_id และเชื่อมตาราง film_actor กับ actor ด้วย actor_id

--HW_4
--Show the list of films rented by a particular customer named Mary Smith.
--แสดงรายการ film ที่ถูกเช่าโดย customer ชื่อ Mary Smith
SELECT film.*
FROM customer
JOIN rental USING(customer_id)
JOIN inventory USING(inventory_id)
JOIN film USING(film_id)
WHERE first_name = "Mary" AND last_name = "Smith";
-- ใช้ JOIN เพื่อเชื่อมตาราง customer กับ rental ด้วย customer_id, เชื่อมตาราง rental กับ inventory ด้วย inventory_id และเชื่อมตาราง inventory กับ film ด้วย film_id
-- ใช้ WHERE เพื่อกรองข้อมูลเฉพาะ customer ที่มี first_name เป็น "Mary" และ last_name เป็น "Smith"

--HW_5
--List all staff members and the store where they work.
--แสดง staff ทั้งหมดพร้อมกับ store ที่พวกเขาทำงานอยู่
SELECT staff.*, district, address 
FROM staff
JOIN store USING(store_id)
JOIN address ON store.address_id = address.address_id;
-- ใช้ JOIN เพื่อเชื่อมตาราง staff กับ store ด้วย store_id และเชื่อมตาราง store กับ address โดยใช้ address_id เป็นตัวเชื่อม
-- ใช้ ON เพื่อระบุเงื่อนไขการเชื่อมตาราง address กับ store โดยใช้ store.address_id = address.address_id

--HW_6
--Show all customers and their rental IDs, even if they have not rented anything.
--แสดง customer ทั้งหมดพร้อมกับ rental IDs ของพวกเขา แม้ว่าพวกเขาจะไม่ได้เช่าอะไรเลย
SELECT first_name, last_name, rental_id 
FROM customer
LEFT JOIN rental USING(customer_id);
-- ใช้ LEFT JOIN เพื่อเชื่อมตาราง customer กับ rental ด้วย customer_id เพื่อให้แสดง customer ทั้งหมดแม้ว่าพวกเขาจะไม่ได้เช่าอะไรเลย
-- customer left join rental จะทำให้แสดง customer ถ้าไม่มีการเช่า rental_id จะเป็น NULL


use university;

--HW_7
-- Display a list of all instructors, showing their ID, name, and the number of sections that they have taught. 
--แสดงรายการ instructor ทั้งหมด โดยแสดง ID, name และจำนวน section ที่พวกเขาได้สอน
SELECT ID, name, COUNT(sec_id)
FROM instructor
LEFT JOIN teaches USING(ID)
GROUP BY ID, name;
-- ใช้ LEFT JOIN เพื่อเชื่อมตาราง instructor กับ teaches ด้วย ID เพื่อให้แสดง instructor ทั้งหมดแม้ว่าพวกเขาจะไม่ได้สอน section ใด ๆ
-- ใช้ COUNT(sec_id) เพื่อหาจำนวน section ที่ instructor ได้สอน และใช้ GROUP BY ID, name เพื่อจัดกลุ่มข้อมูลตาม ID และ name ของ instructor

--HW_8
--Display the list of all course sections offered in Spring 2010, along with the names of the instructors teaching the section.
--If a section has more than one instructor, it should appear as many times in the result as it has instructors. 
--แสดงรายการ section ของ course ทั้งหมดที่เปิดสอนใน Spring 2010 พร้อมกับชื่อของ instructor ที่สอน section นั้น
--ถ้า section ใดมี instructor มากกว่า 1 คน มันควรปรากฏในผลลัพธ์มากเท่ากับจำนวน instructor ของมัน
SELECT title, section.sec_id, name
FROM instructor
JOIN teaches USING(ID)
JOIN course USING(course_id)
JOIN section USING (course_id, sec_id, semester, year)
WHERE section.semester = "Spring" AND section.year = 2010;
-- ใช้ SELECT title, section.sec_id, name เพื่อแสดง title ของ course, sec_id ของ section และ name ของ instructor
-- ใช้ JOIN เพื่อเชื่อมตาราง instructor กับ teaches ด้วย ID, เชื่อมตาราง teaches กับ course ด้วย course_id และเชื่อมตาราง course กับ section ด้วย course_id, sec_id, semester, year
-- ใช้ WHERE เพื่อกรองข้อมูลเฉพาะ section ที่เปิดสอนใน Spring 2010 โดยใช้ section.semester = "Spring" AND section.year = 2010

--HW_9
--Display the list of all departments, with the total number of instructors in each department, without using scalar subqueries.
--Make sure to correctly handle departments with no instructors.
--แสดงรายการ department ทั้งหมด พร้อมกับจำนวน instructor ทั้งหมดในแต่ละ department โดยไม่ใช้ scalar subqueries
--ตรวจสอบให้แน่ใจว่าจัดการ department ที่ไม่มี instructor อย่างถูกต้อง
SELECT dept_name , COUNT(ID) 
FROM department
LEFT JOIN instructor USING(dept_name)
GROUP BY dept_name;
-- ใช้ LEFT JOIN เพื่อเชื่อมตาราง department กับ instructor ด้วย dept_name เพื่อให้แสดง department ทั้งหมด
-- ใช้ COUNT(ID) เพื่อหาจำนวน instructor ในแต่ละ department และใช้ GROUP BY dept_name เพื่อจัดกลุ่มข้อมูลตาม dept_name ของ department