USE university;

--HW_1
SELECT c1.title
FROM course c1
WHERE c1.credits = 3
    AND c1.course_id IN (
        SELECT c2.course_id
        FROM course c2
        WHERE c2.dept_name = 'Comp. Sci.'
    );


--HW_2
SELECT DISTINCT t1.ID
FROM takes t1
WHERE (
    t1.course_id,
    t1.sec_id,
    t1.semester,
    t1.year
) IN (
    SELECT t2.course_id, t2.sec_id, t2.semester, t2.year
    FROM teaches t2
    JOIN instructor i USING (ID)
    WHERE i.name = 'Einstein'
);


--HW_3
SELECT DISTINCT salary
FROM instructor
WHERE salary >= ALL (
    SELECT salary
    FROM instructor
);


--HW_4
SELECT name
FROM instructor
WHERE salary >= ALL (
    SELECT salary
    FROM instructor
);


--HW_5
SELECT
    s.course_id,
    s.sec_id,
    (
        SELECT COUNT(*)
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
SELECT MAX(enrollment) AS max_enrollment
FROM (
    SELECT
        s.course_id,
        s.sec_id,
        (
            SELECT COUNT(*)
            FROM takes t
            WHERE t.course_id = s.course_id
                AND t.sec_id = s.sec_id
                AND t.semester = s.semester
                AND t.year = s.year
        ) AS enrollment
    FROM section s
    WHERE s.semester = 'Autumn'
        AND s.year = 2017
) AS section_count;


--HW_7
SELECT
    t1.course_id,
    t1.sec_id
FROM takes t1
WHERE t1.semester = 'Autumn'
    AND t1.year = 2017
GROUP BY t1.course_id, t1.sec_id
HAVING COUNT(t1.ID) >= ALL (
    SELECT COUNT(t2.ID)
    FROM takes t2
    WHERE t2.semester = 'Autumn'
        AND t2.year = 2017
    GROUP BY t2.course_id, t2.sec_id
);


--HW_8
INSERT INTO course (
    course_id,
    title,
    dept_name,
    credits
)
VALUES (
    'CS-001',
    'Weekly Seminar',
    'Comp. Sci.',
    0
);


--HW_9
INSERT INTO section (
    course_id,
    sec_id,
    semester,
    year
)
VALUES (
    'CS-001',
    '1',
    'Autumn',
    2017
);


--HW_10
INSERT INTO takes (
    ID,
    course_id,
    sec_id,
    semester,
    year
)
SELECT
    s.ID,
    'CS-001',
    '1',
    'Autumn',
    2017
FROM student s
WHERE s.dept_name = 'Comp. Sci.';
