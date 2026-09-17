USE sakila;

--HW_1
--Find the top 5 most rented films.
--หาหนังที่ถูกเช่ามากที่สุด 5 อันดับแรก
SELECT film_id, title, COUNT(rental_id)
FROM film
JOIN inventory USING(film_id)
JOIN rental USING(inventory_id)
GROUP BY film_id, title
ORDER BY COUNT(rental_id) DESC --DESC เรียงจากมากไปน้อย
LIMIT 5;
-- ใช้ JOIN เพื่อเชื่อมตาราง film กับ inventory ด้วย film_id และเชื่อมตาราง inventory กับ rental ด้วย inventory_id
--ใช้ COUNT(rental_id) เพื่อหาจำนวนการเช่าของแต่ละ film และใช้ GROUP BY film_id, title เพื่อจัดกลุ่มข้อมูลตาม film_id และ title ของ film
-- ใช้ ORDER BY COUNT(rental_id) DESC เพื่อเรียงลำดับผลลัพธ์โดยเริ่มจากจำนวนการเช่ามากที่สุด และใช้ LIMIT 5 เพื่อจำกัดผลลัพธ์ให้แสดงแค่ 5 อันดับแรก

--HW_2
--List the customers who have rented at least 40 films.
--แสดงรายชื่อcustomers ที่ได้rental film อย่างน้อย 40 เรื่อง
SELECT customer_id, first_name, last_name, COUNT(rental_id)
FROM customer
JOIN rental USING(customer_id)
GROUP BY customer_id, first_name, last_name
HAVING COUNT(rental_id) >= 40;
-- ใช้ JOIN เพื่อเชื่อมตาราง customer กับ rental ด้วย customer_id
--ใช้ COUNT(rental_id) เพื่อหาจำนวนการเช่าของแต่ละ customer
--ใช้ GROUP BY customer_id, first_name, last_name เพื่อจัดกลุ่มข้อมูลตาม customer_id, first_name และ last_name ของ customer
--ใช้ HAVING COUNT(rental_id) >= 40 เพื่อกรองข้อมูลเฉพาะ customer ที่มีจำนวนการเช่าอย่างน้อย 40 เรื่อง

--Note: HAVING ใช้สำหรับกรองข้อมูลหลังจากที่ได้ทำการ GROUP BY แล้ว ส่วน WHERE ใช้สำหรับกรองข้อมูลก่อนที่จะทำการ GROUP BY

--HW_3
--Show all staff members and the total payment amounts they have collected.
--แสดง staff ทั้งหมดพร้อมกับtotal payment amountsที่พวกเขาได้รับจากการชำระเงิน
SELECT first_name, last_name, SUM(amount)
FROM staff
LEFT JOIN payment USING(staff_id)
GROUP BY staff_id, first_name, last_name;
--ใช้ SUM(amount) เพื่อหาผลรวมของจำนวนเงินที่ staff แต่ละคนได้รับจากการชำระเงิน
-- ใช้ LEFT JOIN เพื่อเชื่อมตาราง staff กับ payment ด้วย staff_id
--ใช้ GROUP BY staff_id, first_name, last_name เพื่อจัดกลุ่มข้อมูลตาม staff_id, first_name และ last_name ของ staff

--HW_4
--Find the first movie rented from a database
--หาหนังเรื่องแรกที่ถูกเช่าจากฐานข้อมูล
SELECT title, rental_date
FROM film
JOIN inventory USING(film_id)
JOIN rental USING(inventory_id)
ORDER BY rental_date
LIMIT 1;
-- ใช้ JOIN เพื่อเชื่อมตาราง film กับ inventory ด้วย film_id และเชื่อมตาราง inventory กับ rental ด้วย inventory_id
--ใช้ ORDER BY rental_date เพื่อเรียงลำดับผลลัพธ์โดยเริ่มจากวันที่เช่าที่เก่าที่สุด และใช้ LIMIT 1 เพื่อจำกัดผลลัพธ์ให้แสดงแค่ 1 เรื่องแรก

--HW_5
--Find the total payment amount collected in August 2005.
--หาผลรวมของจำนวนเงินที่ได้รับจากการชำระเงินในเดือนสิงหาคม 2005
SELECT SUM(amount)
FROM payment
WHERE payment_date >= '2005-08-01' AND payment_date < '2005-09-01';
-- ใช้ SUM(amount) เพื่อหาผลรวมของจำนวนเงินที่ได้รับจากการชำระเงิน
--ใช้ WHERE payment_date >= '2005-08-01' AND payment_date < '2005-09-01' เพื่อกรองข้อมูลเฉพาะการชำระเงินที่เกิดขึ้นในเดือนสิงหาคม 2005

--HW_6
--Find the average rental duration (in days) for all rentals
--หาค่าเฉลี่ยของระยะเวลาเช่า (เป็นวัน) สำหรับการเช่าทั้งหมด
SELECT AVG(DATEDIFF(return_date, rental_date))
FROM rental;
-- ใช้ DATEDIFF(return_date, rental_date) เพื่อหาความต่างของวันที่ระหว่าง return_date และ rental_date เป็นจำนวนวัน
--ใช้ AVG(DATEDIFF(return_date, rental_date)) เพื่อหาค่าเฉลี่ยของจำนวนวันเช่าทั้งหมด

--HW_7
--Show the average amount paid by customers grouped by month (2005 only).
--แสดงค่าเฉลี่ยของจำนวนเงินที่ลูกค้าชำระ โดยจัดกลุ่มตามเดือน (เฉพาะปี 2005)
SELECT MONTH(payment_date), AVG(amount)
FROM payment
WHERE YEAR(payment_date) = 2005
GROUP BY MONTH(payment_date)
ORDER BY MONTH(payment_date);
-- ใช้ MONTH(payment_date) เพื่อดึงเดือนจาก payment_date และใช้ AVG(amount) เพื่อหาค่าเฉลี่ยของจำนวนเงินที่ลูกค้าชำระ
--ใช้ WHERE YEAR(payment_date) = 2005 เพื่อกรองข้อมูลเฉพาะการชำระเงินที่เกิดขึ้นในปี 2005
--ใช้ GROUP BY MONTH(payment_date) เพื่อจัดกลุ่มข้อมูลตามเดือนของ payment_date 
--ใช้ ORDER BY MONTH(payment_date) เพื่อเรียงลำดับผลลัพธ์ตามเดือนของ payment_date

--HW_8
--Find the customer who rented the most films in July 2005.
--หาลูกค้าที่เช่าหนังมากที่สุดในเดือนกรกฎาคม 2005
SELECT customer_id, first_name, last_name, COUNT(rental_id)
FROM customer
JOIN rental USING(customer_id)
WHERE MONTH(rental_date) = 7 AND YEAR(rental_date) = 2005
GROUP BY customer_id, first_name, last_name
ORDER BY COUNT(rental_id) DESC
LIMIT 1;
--ใช้ COUNT(rental_id) เพื่อหาจำนวนการเช่าของแต่ละ customer
--ใช้ JOIN เพื่อเชื่อมตาราง customer กับ rental ด้วย customer_id
--ใช้ WHERE MONTH(rental_date) = 7 AND YEAR(rental_date) = 2005 เพื่อกรองข้อมูลเฉพาะการเช่าที่เกิดขึ้นในเดือนกรกฎาคม 2005
--ใช้ GROUP BY customer_id, first_name, last_name เพื่อจัดกลุ่มข้อมูลตาม customer_id, first_name และ last_name ของ customer
--ใช้ ORDER BY COUNT(rental_id) DESC เพื่อเรียงลำดับผลลัพธ์โดยเริ่มจากจำนวนการเช่ามากที่สุด และใช้ LIMIT 1 เพื่อจำกัดผลลัพธ์ให้แสดงแค่ 1 อันดับแรก


USE university;

--HW_9
--Count how many students are enrolled in each department.
--นับจำนวนของนักเรียนที่ลงทะเบียนในแต่ละ department
SELECT dept_name, COUNT(DISTINCT ID)
FROM department
LEFT JOIN student USING(dept_name)
GROUP BY dept_name;
-- ใช้ LEFT JOIN เพื่อเชื่อมตาราง department กับ student ด้วย dept_name เพื่อให้แสดง department ทั้งหมด
--ใช้ COUNT(DISTINCT ID) เพื่อหาจำนวนของนักเรียนที่ลงทะเบียนในแต่ละ department
--ใช้ GROUP BY dept_name เพื่อจัดกลุ่มข้อมูลตาม dept_name ของ department

--HW_10
--Find the instructor who taught the most courses in 2009.
--หานักสอนที่สอนคอร์สมากที่สุดในปี 2009
SELECT ID, name, COUNT(DISTINCT course_id)
FROM instructor
JOIN teaches USING(ID)
WHERE teaches.year = 2009
GROUP BY ID, name
ORDER BY COUNT(DISTINCT course_id) DESC
LIMIT 1;
-- ใช้ COUNT(DISTINCT course_id) เพื่อหาจำนวนคอร์สที่ instructor สอนในปี 2009
--ใช้ JOIN เพื่อเชื่อมตาราง instructor กับ teaches ด้วย ID
--ใช้ WHERE teaches.year = 2009 เพื่อกรองข้อมูลเฉพาะการสอนที่เกิดขึ้นในปี 2009
--ใช้ GROUP BY ID, name เพื่อจัดกลุ่มข้อมูลตาม ID และ name ของ instructor
--ใช้ ORDER BY COUNT(DISTINCT course_id) DESC เพื่อเรียงลำดับผลลัพธ์โดยเริ่มจากจำนวนคอร์สมากที่สุด และใช้ LIMIT 1 เพื่อจำกัดผลลัพธ์ให้แสดงแค่ 1 อันดับแรก

--HW_11
--Find the department with the highest average student credit load in 2010
--หาค่าเฉลี่ยของ credit ของนักเรียนในแต่ละ department ในปี 2010 และหาว่า department ไหนมีค่าเฉลี่ยสูงที่สุด
SELECT student.dept_name, SUM(credits) / COUNT(DISTINCT ID) --ใช้ student.dept_name เพื่อให้รู้ว่าเป็นdeptของstudent
FROM student
JOIN takes USING(ID)
JOIN course USING(course_id)
WHERE year = 2010
GROUP BY student.dept_name
ORDER BY SUM(credits) / COUNT(DISTINCT ID) DESC
LIMIT 1;
-- ใช้ SUM(credits) / COUNT(DISTINCT ID) เพื่อหาค่าเฉลี่ยของ credit ของนักเรียนในแต่ละ department ในปี 2010
--ใช้ JOIN เพื่อเชื่อมตาราง student กับ takes ด้วย ID และเชื่อมตาราง takes กับ course ด้วย course_id
--ใช้ WHERE year = 2010 เพื่อกรองข้อมูลเฉพาะการเรียนที่เกิดขึ้นในปี 2010
--ใช้ GROUP BY student.dept_name เพื่อจัดกลุ่มข้อมูลตาม dept_name ของ student
--ใช้ ORDER BY SUM(credits) / COUNT(DISTINCT ID) DESC เพื่อเรียงลำดับผลลัพธ์โดยเริ่มจากค่าเฉลี่ยของ credit สูงที่สุด
--ใช้ LIMIT 1 เพื่อจำกัดผลลัพธ์ให้แสดงแค่ 1 อันดับแรก

--HW_12
--Find the year in which the most distinct courses were offered.
--หาปีที่มีการเปิดสอนคอร์สที่แตกต่างกันมากที่สุด
SELECT year, COUNT(DISTINCT course_id)
FROM section
GROUP BY year
ORDER BY COUNT(DISTINCT course_id) DESC
LIMIT 1;
-- ใช้ COUNT(DISTINCT course_id) เพื่อหาจำนวนคอร์สที่แตกต่างกันในแต่ละปี
--ใช้ GROUP BY year เพื่อจัดกลุ่มข้อมูลตามปี
--ใช้ ORDER BY COUNT(DISTINCT course_id) DESC เพื่อเรียงลำดับผลลัพธ์โดยเริ่มจากจำนวนคอร์สที่แตกต่างกันมากที่สุด
--ใช้ LIMIT 1 เพื่อจำกัดผลลัพธ์ให้แสดงแค่ 1 อันดับแรก

--HW_13
--Find instructors who taught more than 3 different courses in the same semester and year.
--หาinstructors ที่สอนคอร์สที่แตกต่างกันมากกว่า 3 คอร์สใน semester และ year เดียวกัน
SELECT ID, name, semester, year, COUNT(DISTINCT course_id)
FROM instructor
JOIN teaches USING(ID)
GROUP BY ID, name, semester, year
HAVING COUNT(DISTINCT course_id) > 3;
-- ใช้ COUNT(DISTINCT course_id) เพื่อหาจำนวนคอร์สที่แตกต่างกันที่ instructor สอนใน semester และ year เดียวกัน
--ใช้ JOIN เพื่อเชื่อมตาราง instructor กับ teaches ด้วย ID
--ใช้ GROUP BY ID, name, semester, year เพื่อจัดกลุ่มข้อมูลตาม ID, name, semester และ year ของ instructor
--ใช้ HAVING COUNT(DISTINCT course_id) > 3 เพื่อกรองข้อมูลเฉพาะ instructor ที่สอนคอร์สที่แตกต่างกันมากกว่า 3 คอร์สใน semester และ year เดียวกัน