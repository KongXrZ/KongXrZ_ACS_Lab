use sakila;

--Challenge1
    SELECT title, rating, length
    FROM film
    WHERE rating IN ('PG','G') AND length >= 90
    ORDER BY length DESC, title
    LIMIT 10;

--Challenge2
SELECT payment_id, customer_id, amount, payment_date
FROM payment
WHERE (payment_date >= '2005-06-15' AND payment_date < '2005-06-21') and amount >= 5.00
ORDER BY payment_date DESC;

--Challenge3
SELECT * 
FROM actor 
WHERE last_name LIKE '_____';

SELECT * 
FROM actor 
WHERE CHAR_LENGTH(last_name) = 5; 

--Challenge4
SELECT title
FROM film
WHERE title LIKE '% % %' AND title NOT LIKE '% % % %'
ORDER BY title;

--Challenge5
SELECT DISTINCT rating, rental_duration 
FROM film
ORDER BY rating, rental_duration;
--Challenge6
SELECT * FROM payment WHERE amount = NULL;  --ไม่คืนข้อมูล เพราะไม่สามารถเปรียบเทียบ NULL ด้วย = ได้
SELECT * FROM payment WHERE amount IS NULL; --ต้องใช้ IS NULL


--Homework1
SELECT DISTINCT rental_duration 
FROM film
WHERE rental_duration IS NOT NULL; --กรอง NULL ออก

--Homework2
SELECT title, length 
FROM film
WHERE length BETWEEN 60 AND 100;

--Homework3
SELECT city 
FROM city
WHERE city LIKE 'G%' OR city LIKE '%Z%';

--Homework4
SELECT actor_id, first_name, last_name 
FROM actor
WHERE last_name IN('Williams','Davis');

--Homework5
SELECT * 
FROM film
ORDER BY rental_rate DESC
LIMIT 15;

--Homework6
SELECT COUNT(*)
FROM rental
WHERE rental_date >= '2005-07-01' AND rental_date < '2005-08-01';