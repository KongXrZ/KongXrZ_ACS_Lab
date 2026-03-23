#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

const int STUDENT_COUNT = 10;

// เก็บข้อมูลของนักศึกษา 1 คน
struct Student {
    string name;
    double score;
    char grade;
};

// หานักศึกษาที่ได้คะแนนสูงสุด
Student MaxStudent(const Student students[], int size) {
    Student maxStudent = students[0];

    for (int i = 1; i < size; i++) {
        if (students[i].score > maxStudent.score) {
            maxStudent = students[i];
        }
    }

    return maxStudent;
}

// หานักศึกษาที่ได้คะแนนต่ำสุด
Student MinStudent(const Student students[], int size) {
    Student minStudent = students[0];

    for (int i = 1; i < size; i++) {
        if (students[i].score < minStudent.score) {
            minStudent = students[i];
        }
    }

    return minStudent;
}

// หาคะแนนเฉลี่ยของนักศึกษาทั้งหมด
double AvrScore(const Student students[], int size) {
    double sum = 0;

    for (int i = 0; i < size; i++) {
        sum += students[i].score;
    }

    return sum / size;
}

// หาฐานนิยม ถ้าไม่มีคะแนนซ้ำจะคืนค่า -1
double ModeScore(const Student students[], int size) {
    int maxCount = 1;
    double mode = -1;

    for (int i = 0; i < size; i++) {
        int count = 1;
        for (int j = i + 1; j < size; j++) {
            if (students[i].score == students[j].score) {
                count++;
            }
        }

        if (count > maxCount) {
            maxCount = count;
            mode = students[i].score;
        }
    }

    return mode;
}

// หาค่ามัธยฐานโดยเรียงคะแนนจากน้อยไปมากก่อน
double MedianScore(const Student students[], int size) {
    double sortedScores[STUDENT_COUNT];

    for (int i = 0; i < size; i++) {
        sortedScores[i] = students[i].score;
    }

    sort(sortedScores, sortedScores + size);

    if (size % 2 == 0) {
        return (sortedScores[size / 2 - 1] + sortedScores[size / 2]) / 2.0;
    }

    return sortedScores[size / 2];
}

// หาค่าส่วนเบี่ยงเบนมาตรฐาน
double SDScore(const Student students[], int size) {
    double average = AvrScore(students, size);
    double sum = 0;

    for (int i = 0; i < size; i++) {
        double diff = students[i].score - average;
        sum += diff * diff;
    }

    return sqrt(sum / size);
}

// กำหนดเกรดตามเงื่อนไขของโจทย์
// A: score > average + 2 * sd
// B: score > average + sd
// C: score > average
// D: score > average - sd
// F: score < average - sd
char CalculateGrade(double score, double average, double sd) {
    if (score > average + (2 * sd)) {
        return 'A';
    }
    if (score > average + sd) {
        return 'B';
    }
    if (score > average) {
        return 'C';
    }
    if (score > average - sd) {
        return 'D';
    }
    return 'F';
}

// แสดงรายชื่อนักศึกษาพร้อมคะแนนและเกรดที่คำนวณได้
void DisplayStudents(Student students[], int size, double average, double sd) {
    cout << "\nStudent List and Grades\n";
    cout << "-----------------------------\n";

    for (int i = 0; i < size; i++) {
        students[i].grade = CalculateGrade(students[i].score, average, sd);
        cout << right << setw(2) << i + 1 << ". "<< left << setw(12) << students[i].name
             << " Score: " << setw(6) << students[i].score
             << " Grade: " << students[i].grade << "\n";
    }
}

int main() {
    // ข้อมูลตัวอย่างนักศึกษา 10 คน โดยไม่ต้องรับค่าจากผู้ใช้
    Student students[STUDENT_COUNT] = {
        {"Kong", 78, '-'},
        {"Fructose", 92, '-'},
        {"Maxlnwza007", 85, '-'},
        {"PrabDragon", 67, '-'},
        {"Paitong", 74, '-'},
        {"OverDoze", 88, '-'},
        {"vixvify_v", 95, '-'},
        {"Sir_Park", 81, '-'},
        {"_aoocsnp", 70, '-'},
        {"kiitiz_", 88, '-'}
    };

    Student maxStudent = MaxStudent(students, STUDENT_COUNT);
    Student minStudent = MinStudent(students, STUDENT_COUNT);
    double average = AvrScore(students, STUDENT_COUNT);
    double mode = ModeScore(students, STUDENT_COUNT);
    double median = MedianScore(students, STUDENT_COUNT);
    double sd = SDScore(students, STUDENT_COUNT);

    // แสดงค่าสถิติก่อนสรุปเกรดของนักศึกษาแต่ละคน
    cout << fixed << setprecision(2);
    cout << "\nScore Analysis Summary\n";
    cout << "======================\n";
    cout << "Highest Score: " << maxStudent.name << " (" << maxStudent.score << ")\n";
    cout << "Lowest Score: " << minStudent.name << " (" << minStudent.score << ")\n";
    cout << "Average Score: " << average << "\n";

    if (mode == -1) {
        cout << "Mode: No repeated score\n";
    } else {
        cout << "Mode: " << mode << "\n";
    }

    cout << "Median: " << median << "\n";
    cout << "Standard Deviation: " << sd << "\n";

    DisplayStudents(students, STUDENT_COUNT, average, sd);

    return 0;
}

/* วิเคราะห์ Big O
MaxStudent() ใช้เวลา O(n) เพราะต้องวนดูคะแนนของนักศึกษาทุกคนเพื่อหาค่าสูงสุด (1 for loop)
MinStudent() ใช้เวลา O(n) เพราะต้องวนดูคะแนนของนักศึกษาทุกคนเพื่อหาค่าต่ำสุด (1 for loop)
AvrScore() ใช้เวลา O(n) เพราะต้องรวมคะแนนของนักศึกษาทุกคน (1 for loop)
ModeScore() ใช้เวลา O(n^2) เพราะใช้ลูปซ้อนเพื่อนับจำนวนคะแนนที่ซ้ำกัน (2 for loop)
MedianScore() ใช้เวลา O(n log n) เพราะมีการ sort คะแนนก่อนหามัธยฐาน (sortจาก lib algorithm)
SDScore() ใช้เวลา O(n) เพราะต้องวนคำนวณผลต่างของคะแนนทุกคนจากค่าเฉลี่ย (1 for loop)
CalculateGrade() ใช้เวลา O(1) เพราะเป็นการเปรียบเทียบเงื่อนไขคงที่ (if else)
DisplayStudents() ใช้เวลา O(n) เพราะต้องแสดงผลนักศึกษาทุกคน (1 for loop)

Time Complexity รวมของโปรแกรมคือ O(n^2)
*/
