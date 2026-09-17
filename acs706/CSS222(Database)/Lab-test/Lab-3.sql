use sakila;

--Challenge1
--Films rated 'PG' or 'G' with length of at least 90 minutes. Show title , rating , length —longest first, break ties by title. Show only the top 10.
--หาหนัง (จากตาราง film) ที่มี rating เป็น 'PG' หรือ 'G' และมี length อย่างน้อย 90 นาที 
--ให้แสดง title, rating, และ length โดยเรียงจาก length ที่ยาวที่สุดขึ้นก่อน หาก length เท่ากันให้ตัดสินด้วยการเรียงตาม title (เรียงตามตัวอักษร) และให้แสดงผลลัพธ์แค่ 10 อันดับแรกเท่านั้น
    SELECT title, rating, length
    FROM film
    WHERE rating IN ('PG','G') AND length >= 90
    ORDER BY length DESC, title
    LIMIT 10;
-- IN บอกว่าให้แสดง rating ที่มีค่าเท่ากับ 'PG' หรือ 'G' เท่านั้น 
--ใช้ And เชื่อมเงื่อนไข length >= 90 เพื่อให้แสดงเฉพาะหนังที่มีความยาวมากกว่า 90 นาที
--Order by length DESC, title คือการเรียงลำดับผลลัพธ์โดยเริ่มจาก length ที่มากที่สุดก่อน และหาก length เท่ากันให้เรียงตาม title (เรียงตามตัวอักษร)
-- Limit 10 คือการจำกัดผลลัพธ์ให้แสดงแค่ 10 อันดับแรกเท่านั้น

----------------------------------------------------------------------------------------------------

--Challenge2
--Payments made from 2005-06-15 up to (but not including) 2005-06-21 with amount of 5.00 ormore.
--Show payment_id , customer_id , amount , payment_date , newest first.
--หาการชำระเงิน (จากตาราง payment) ที่เกิดขึ้นตั้งแต่วันที่ 2005-06-15 ไปจนถึง (แต่ไม่รวม) วันที่ 2005-06-21 โดยที่มียอด amount ตั้งแต่ 5.00 ขึ้นไป
--ให้แสดง payment_id, customer_id, amount, และ payment_date โดยเรียงจากวันที่ใหม่ที่สุดขึ้นก่อน (Newest first)
SELECT payment_id, customer_id, amount, payment_date
FROM payment
WHERE (payment_date >= '2005-06-15' AND payment_date < '2005-06-21') and amount >= 5.00
ORDER BY payment_date DESC;
--Where ใช้ AND เชื่อมเงื่อนไข 2 ข้อ คือ payment_date ต้องอยู่ระหว่างวันที่ 2005-06-15 00:00:00 ถึง วันที่ 2005-06-20 23:59:59 และ amount ต้องมีค่าเท่ากับหรือมากกว่า 5.00
--Order by payment_date DESC คือการเรียงลำดับผลลัพธ์โดยเริ่มจากวันที่ใหม่ที่สุดขึ้นก่อน (Newest first)

---------------------------------------------------------------------------------------------------

--Challenge3
--Actors whose last_name is exactly 5 characters long
--write it two different ways: once withLIKE, once with CHAR_LENGTH. Do both return the same rows?
--หานักแสดง (จากตาราง actor) ที่มี last_name ยาว 5 ตัวอักษรพอดี
--ให้เขียน query 2 แบบ คือแบบที่ใช้ LIKE และแบบที่ใช้ CHAR_LENGTH โดยทั้งสองแบบจะได้ผลลัพธ์เหมือนกันหรือไม่
SELECT * 
FROM actor 
WHERE last_name LIKE '_____';
--where last_name LIKE '_____' คือการใช้ LIKE เพื่อหาค่า last_name ที่มีความยาว 5 ตัวอักษรพอดี โดยใช้ _ แทนตัวอักษรแต่ละตัว (5 ตัว _ = 5 ตัวอักษร)

SELECT * 
FROM actor 
WHERE CHAR_LENGTH(last_name) = 5; 
--where CHAR_LENGTH(last_name) = 5 คือการใช้ฟังก์ชัน CHAR_LENGTH เพื่อหาค่า last_name ที่มีความยาว 5 ตัวอักษร

---------------------------------------------------------------------------------------------------

--Challenge4
--Find films whose title contains exactly two spaces (i.e. three words). Show title only,alphabetically.
--หาหนัง (จากตาราง film) ที่มี title มีช่องว่าง (space) อยู่ 2 ช่องพอดี (คือมี 3 คำ), ให้แสดง title เท่านั้น โดยเรียงตามตัวอักษร (Alphabetically)
SELECT title
FROM film
WHERE title LIKE '% % %' AND title NOT LIKE '% % % %'
ORDER BY title;
-- Where title LIKE '% % %' คือการใช้ LIKE เพื่อหาค่า title ที่มีช่องว่าง (space) อยู่ 2 ช่องพอดี โดยใช้ % แทนตัวอักษรใด ๆ และ _ แทนตัวอักษรแต่ละตัว

---------------------------------------------------------------------------------------------------

--Challenge5
--List the distinct combinations of rating and rental_duration that exist in film, ordered by rating then duration.
--แสดงความแตกต่างของ rating และ rental_duration ที่มีอยู่ในตาราง film, จัดเรียงตาม rating แล้วตาม duration
SELECT DISTINCT rating, rental_duration 
FROM film
ORDER BY rating, rental_duration;
--ใช้ DISTINCT เพื่อหาค่าที่ไม่ซ้ำกันของ rating และ rental_duration

---------------------------------------------------------------------------------------------------

--Challenge6
--Why does this return nothing?
SELECT * FROM payment WHERE amount = NULL;  --ไม่คืนข้อมูล เพราะไม่สามารถเปรียบเทียบ NULL ด้วย = ได้
SELECT * FROM payment WHERE amount IS NULL; --ต้องใช้ IS NULL


--Homework1
--Write a query to display all unique rental_duration that exist in the film table.
--เขียน query เพื่อแสดง rental_duration ที่ไม่ซ้ำกันทั้งหมดที่มีอยู่ในตาราง film
SELECT DISTINCT rental_duration 
FROM film
WHERE rental_duration IS NOT NULL;
-- ใช้ DISTINCT เพื่อหาค่าที่ไม่ซ้ำกันของ rental_duration และใช้ NOT NULL เพื่อกรองค่า NULL ออก

---------------------------------------------------------------------------------------------------

--Homework2
--Display title and length of all film having length between 60 and 100.
--แสดง title และ length ของหนังทั้งหมดที่มี length อยู่ระหว่าง 60 ถึง 100
SELECT title, length 
FROM film
WHERE length BETWEEN 60 AND 100;
-- ใช้ BETWEEN เพื่อหาค่า length ที่อยู่ระหว่าง 60 ถึง 100

---------------------------------------------------------------------------------------------------

--Homework3
--Show the city that start with ‘G’ or contain ‘Z’ in the city table.
--แสดง city ที่ขึ้นต้นด้วยตัวอักษร ‘G’ หรือมีตัวอักษร ‘Z’ อยู่ใน city table
SELECT city 
FROM city
WHERE city LIKE 'G%' OR city LIKE '%Z%';
-- ใช้ LIKE เพื่อหาค่า city ที่ขึ้นต้นด้วยตัวอักษร ‘G’ หรือมีตัวอักษร ‘Z’ อยู่ใน city table โดยใช้ % แทนตัวอักษรใด ๆ

---------------------------------------------------------------------------------------------------

--Homework4
--Retrieve the actor ID, first name, and last name for all actors whose last name equals ‘Williams’ or ‘Davis
--ดึง actor ID, first name, และ last name ของนักแสดงทั้งหมดที่มี last name เท่ากับ ‘Williams’ หรือ ‘Davis’
SELECT actor_id, first_name, last_name 
FROM actor
WHERE last_name IN('Williams','Davis');
-- ใช้ IN เพื่อหาค่า last_name ที่เท่ากับ ‘Williams’ หรือ ‘Davis’

---------------------------------------------------------------------------------------------------

--Homework5
-- Display all information from the film table in descending order of the rental price and show only the first 15 rows.
--แสดงข้อมูลทั้งหมดจากตาราง film โดยเรียงลำดับจาก rental price มากไปน้อย และแสดงผลลัพธ์แค่ 15 แถวแรก
SELECT * 
FROM film
ORDER BY rental_rate DESC
LIMIT 15;
-- ใช้ ORDER BY rental_rate DESC เพื่อเรียงลำดับจาก rental price มากไปน้อย และใช้ LIMIT 15 เพื่อแสดงผลลัพธ์แค่ 15 แถวแรก

---------------------------------------------------------------------------------------------------

--Homework6
--Count rentals that happened in July 2005.
--นับจำนวนการเช่าที่เกิดขึ้นในเดือนกรกฎาคม 2005
SELECT COUNT(*)
FROM rental
WHERE rental_date >= '2005-07-01' AND rental_date < '2005-08-01';
-- ใช้ COUNT(*) เพื่อนับจำนวนการเช่า โดยใช้ WHERE rental_date >= '2005-07-01' AND rental_date < '2005-08-01' เพื่อกรองข้อมูลเฉพาะการเช่าที่เกิดขึ้นในเดือนกรกฎาคม 2005