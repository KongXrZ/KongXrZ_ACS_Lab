USE sakila;

--HW_1
SELECT name,
	CASE 
		WHEN name IN ('English', 'Italian', 'French', 'German') THEN 'latin1'
        WHEN name IN ('Japanese', 'Mandarin') THEN 'utf8'
        ELSE 'Unknown'
	END AS character_set
FROM language;

--HW_2
SELECT payment_id, customer_id, amount,
	CASE 
		WHEN amount < 2.00 THEN 'Low'
		WHEN amount < 5.00 THEN 'Medium'
		WHEN amount < 8.00 THEN 'High'
        WHEN amount >= 8.00 THEN 'Very High'
        ELSE 'Unknown'
	END AS 'payment_level'
FROM payment;

--HW_3
SELECT customer_id, first_name, last_name,
COALESCE(CONCAT(last_name, ', ', first_name), first_name, last_name, 'Unknown Customer') AS display_name
FROM customer;

--HW_4
SELECT
    SUM(CASE WHEN amount < 2.00 THEN 1 ELSE 0 END) AS under_2,
    SUM(CASE WHEN amount >= 2.00 AND amount < 5.00 THEN 1 ELSE 0 END) AS from_2_to_5,
    SUM(CASE WHEN amount >= 5.00 AND amount < 8.00 THEN 1 ELSE 0 END) AS from_5_to_8,
    SUM(CASE WHEN amount >= 8.00 THEN 1 ELSE 0 END) AS over_8
FROM payment;

--HW_5
SELECT customer.customer_id, 
COUNT(DISTINCT rental_id) AS number_of_rentals,
COUNT(DISTINCT payment_id) AS number_of_payments,
COUNT(DISTINCT payment_id) / NULLIF(COUNT(DISTINCT rental_id), 0) AS payment_per_rental,
	CASE 
		WHEN COUNT(DISTINCT rental_id) = 0 THEN 'No Activity'
        WHEN COUNT(DISTINCT rental_id) <= 10 THEN 'Light'
        WHEN COUNT(DISTINCT rental_id) <= 25 THEN 'Moderate'
        WHEN COUNT(DISTINCT rental_id) > 25 THEN 'Frequent'
        ELSE 'Unknown'
	END AS 'rental_usage'
FROM customer
LEFT JOIN rental USING(customer_id)
LEFT JOIN payment USING(rental_id)
GROUP BY customer.customer_id;