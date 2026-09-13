const course = {
    courseCode: "CSS233",
    title: "Web Programming I",
    studentsCount: 45
};

course.semester = "1/2026";

delete course.studentsCount;

const updatedCourse = { ...course, title: "Advanced Web Programming I" };