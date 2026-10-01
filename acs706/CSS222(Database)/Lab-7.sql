USE university;

--HW_1
SELECT title 
FROM course
WHERE credits = 3 
AND course_id IN
    (
        SELECT course_id 
        FROM course 
        WHERE dept_name = 'Comp. Sci.'
    );

--HW_2
SELECT DISTINCT ID 
FROM takes
WHERE (course_id, sec_id, semester, year) IN
    (
        SELECT course_id, sec_id, semester, year 
        FROM teaches
        WHERE ID IN (
            SELECT ID 
            FROM instructor 
            WHERE name = 'Einstein'
        )
    );

--HW_3
SELECT salary 
FROM instructor 
WHERE salary >= ALL 
(SELECT salary FROM instructor);

--HW_4
SELECT ID, name, salary 
FROM instructor
WHERE salary >= ALL 
(SELECT salary FROM instructor);

--HW_5
SELECT s.course_id, s.sec_id, s.semester, s.year,
    (   
        SELECT count(*)
        FROM takes t
        WHERE t.course_id = s.course_id
        AND t.sec_id = s.sec_id
        AND t.semester = s.semester
        AND t.year = s.year
    ) AS enrollment
FROM section s
WHERE s.semester = 'Autumn'
AND s.year = 2017;

--HW_6
SELECT max(enrollment)
FROM (
    SELECT s.course_id, s.sec_id,
    (
        SELECT count(*)
        FROM takes t
        WHERE t.course_id = s.course_id
          AND t.sec_id = s.sec_id
          AND t.semester = s.semester
          AND t.year = s.year
    ) AS enrollment
    FROM section s
    WHERE s.semester = 'Autumn'
      AND s.year = 2017
) AS t;

--HW_7
SELECT s.course_id, s.sec_id, s.semester, s.year
FROM section s
WHERE s.semester = 'Autumn'
  AND s.year = 2017
  AND (
      SELECT count(*)
      FROM takes t
      WHERE t.course_id = s.course_id
        AND t.sec_id = s.sec_id
        AND t.semester = s.semester
        AND t.year = s.year
    ) >= all (
        SELECT (
            SELECT count(*)
            FROM takes t
            WHERE t.course_id = s2.course_id
            AND t.sec_id = s2.sec_id
            AND t.semester = s2.semester
            AND t.year = s2.year
        )
        FROM section s2
        WHERE s2.semester = 'Autumn'
            AND s2.year = 2017
    );




--HW_8
INSERT INTO course (course_id, title, dept_name, credits)
VALUES ('CS-001', 'Weekly Seminar', 'Comp. Sci.', 0);

--HW_9
INSERT INTO section (course_id, sec_id, semester, year)
VALUES ('CS-001', 1, 'Autumn', 2017);

--HW_10
INSERT INTO takes (ID, course_id, sec_id, semester, year)
SELECT ID, 'CS-001', 1, 'Autumn', 2017
FROM student
WHERE dept_name = 'Comp. Sci.';

--HW_11
DELETE FROM takes
WHERE course_id = 'CS-001'
  AND sec_id = 1
  AND semester = 'Autumn'
  AND year = 2017
  AND ID IN (
      SELECT ID
      FROM student
      WHERE name = 'Chavez'
    );

--HW_12
DELETE FROM course
WHERE course_id =  'CS-001';
-- ลบไม่ได้ เพราะยังมีข้อมูลcourceในตารางsectionที่ผูกและอ้างอิงถึง course_id นี้อยู่ ต้องทำการลบsectionของวิชานี้ทิ้งก่อนจึงจะสามารถลบข้อมูลวิชาหลักได้

--HW_13
DELETE FROM takes
WHERE course_id IN
    (
	    SELECT course_id 
	    FROM course
        WHERE lower(title) LIKE '%database%' 
    );