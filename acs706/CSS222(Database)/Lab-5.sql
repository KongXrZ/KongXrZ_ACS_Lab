USE sakila;

--HW_1
SELECT film_id, title, COUNT(rental_id)
FROM film
JOIN inventory USING(film_id)
JOIN rental USING(inventory_id)
GROUP BY film_id, title
ORDER BY COUNT(rental_id) DESC
LIMIT 5;

--HW_2
SELECT customer_id, first_name, last_name, COUNT(rental_id)
FROM customer
JOIN rental USING(customer_id)
GROUP BY customer_id, first_name, last_name
HAVING COUNT(rental_id) >= 40;

--HW_3
SELECT first_name, last_name, SUM(amount)
FROM staff
LEFT JOIN payment USING(staff_id)
GROUP BY staff_id, first_name, last_name;

--HW_4
SELECT title, rental_date
FROM film
JOIN inventory USING(film_id)
JOIN rental USING(inventory_id)
ORDER BY rental_date
LIMIT 1;

--HW_5
SELECT SUM(amount)
FROM payment
WHERE payment_date >= '2005-08-01' AND payment_date < '2005-09-01';

--HW_6
SELECT AVG(DATEDIFF(return_date, rental_date))
FROM rental;

--HW_7
SELECT MONTH(payment_date), AVG(amount)
FROM payment
WHERE YEAR(payment_date) = 2005
GROUP BY MONTH(payment_date)
ORDER BY MONTH(payment_date);

--HW_8
SELECT customer_id, first_name, last_name, COUNT(rental_id)
FROM customer
JOIN rental USING(customer_id)
WHERE MONTH(rental_date) = 7 AND YEAR(rental_date) = 2005
GROUP BY customer_id, first_name, last_name
ORDER BY COUNT(rental_id) DESC
LIMIT 1;


USE university;

--HW_9
SELECT dept_name, COUNT(DISTINCT ID)
FROM department
LEFT JOIN student USING(dept_name)
GROUP BY dept_name;

--HW_10
SELECT ID, name, COUNT(DISTINCT course_id)
FROM instructor
JOIN teaches USING(ID)
WHERE teaches.year = 2009
GROUP BY ID, name
ORDER BY COUNT(DISTINCT course_id) DESC
LIMIT 1;

--HW_11
SELECT student.dept_name, SUM(credits) / COUNT(DISTINCT ID) 
FROM student
JOIN takes USING(ID)
JOIN course USING(course_id)
WHERE year = 2010
GROUP BY student.dept_name
ORDER BY SUM(credits) / COUNT(DISTINCT ID) DESC
LIMIT 1;

--HW_12
SELECT year, COUNT(DISTINCT course_id)
FROM section
GROUP BY year
ORDER BY COUNT(DISTINCT course_id) DESC
LIMIT 1;

--HW_13
SELECT ID, name, semester, year, COUNT(DISTINCT course_id)
FROM instructor
JOIN teaches USING(ID)
GROUP BY ID, name, semester, year
HAVING COUNT(DISTINCT course_id) > 3;