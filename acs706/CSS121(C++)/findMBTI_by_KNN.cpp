#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

struct Character {
    string name;
    double functions[8];
    string type;
    double distance;
};

vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

double calculateDistance(const double q[8], const double p[8]) {
    double sum = 0;
    for (int i = 0; i < 8; ++i) sum += pow(q[i] - p[i], 2);
    return sqrt(sum);
}

bool stringToDouble(const string &text, double &value) {
    stringstream ss(text);
    ss >> value;
    return !ss.fail() && ss.eof();
}

string calculateMajority(const vector<Character>& neighbors, int k) {
    string result = "";
    char labels[4][2] = {{'I', 'E'}, {'N', 'S'}, {'T', 'F'}, {'J', 'P'}};

    for (int i = 0; i < 4; ++i) {
        int countFirst = 0; // นับตัวอักษรฝั่งซ้าย (I, N, T, J)
        
        for (int j = 0; j < k; ++j) {
            if (neighbors[j].type[i] == labels[i][0]) {
                countFirst++;
            }
        }

        // ถ้าฝั่งซ้ายชนะ (เกินครึ่งของ k) ให้ใช้ตัวอักษรนั้น
        if (countFirst > k / 2.0) {
            result += labels[i][0];
        } else {
            result += labels[i][1];
        }
    }
    return result;
}

int main() {


    double query[8] = {32, 32, 27, 36, 29, 31, 28, 23};//ค่าที่จะเอาไปหา
    vector<Character> dataset;
    
    ifstream file("CSS121_MBTI_2026-68.csv"); //ถ้ารันไม่ได้ลองแก้Pathนะครับ
    
    if (!file.is_open()) {
        cerr << "Error: Can't open file" << endl;
        return 1;
    }

    string line;
    getline(file, line); // ข้าม Header

    while (getline(file, line)) {
        if (line.empty()) continue; // ข้ามบรรทัดว่าง
        vector<string> row = split(line, ',');
        
        // ไฟล์นี้มี 14 columns เราต้องการถึง index 11 (Type)
        if (row.size() < 12) continue; 

        Character c;
        c.name = row[1];
        c.type = row[11];

        bool validRow = true;

        for (int i = 0; i < 8; ++i) {
            if (!stringToDouble(row[i + 3], c.functions[i])) {
                validRow = false;
                break;
            }
        }

        if (!validRow) continue;

        c.distance = calculateDistance(query, c.functions);
        dataset.push_back(c);
    }

    int k = 3;
    if (dataset.size() >= k) {
        nth_element(dataset.begin(), dataset.begin() + k, dataset.end(),
            [](const Character &a, const Character &b) {
                return a.distance < b.distance;
            });

        cout << "--- 3 Nearest Neighbors (O(N) Result) ---" << endl;
        for (int i = 0; i < k; ++i) {
            cout << "Name: " << dataset[i].name 
                 << " | Type: " << dataset[i].type 
                 << " | Distance: " << dataset[i].distance << endl;
        }
        string finalType = calculateMajority(dataset, k);
        cout << "================================" << endl;
        cout << "your MBTI is: " << finalType << endl;
        cout << "================================" << endl;
    } else {
        cout << "Not enough data in dataset" << endl;
    }

    return 0;
}

/*วิเคราะห์ Big O
split() ใช้เวลา O(L) เพราะต้องอ่านตัวอักษรทุกตัวใน 1 บรรทัดเพื่อแยกข้อมูล
calculateDistance() ใช้เวลา O(1) เพราะคำนวณระยะห่างจากข้อมูล 8 มิติ ซึ่งเป็นค่าคงที่
calculateMajority() ใช้เวลา O(k) เพราะตรวจสอบ MBTI 4 ตำแหน่งจากเพื่อนบ้านจำนวน k ตัว

ใน main() ลูปอ่านไฟล์ทำงานทั้งหมด N รอบ
แต่ละรอบมีการ split + แปลงข้อมูล + คำนวณ distance
โดยส่วนที่ใช้เวลาหลักคือ split() = O(L)
ดังนั้นส่วนประมวลผลข้อมูลจากไฟล์รวมเป็น O(NL)

nth_element() ใช้หา k nearest neighbors ได้ในเวลาเฉลี่ย O(N)
ส่วนการโหวตผลลัพธ์สุดท้ายใช้เวลา O(k)

ดังนั้น Time Complexity รวมของโปรแกรมคือ O(NL + N + k)
และถ้าถือว่า L และจำนวนมิติเป็นค่าคงที่ จะสรุปได้เป็น O(N)

Space Complexity รวมของโปรแกรมคือ O(N)
เพราะต้องเก็บข้อมูลทั้งหมดไว้ใน vector<Character> dataset*/