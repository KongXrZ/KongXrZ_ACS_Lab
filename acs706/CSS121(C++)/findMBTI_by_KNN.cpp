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

string calculateMajority(const vector<Character>& neighbors, int k) {
    string result = "";
    // ตำแหน่ง MBTI ทั้ง 4 (0:I/E, 1:N/S, 2:T/F, 3:J/P)
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
    
    ifstream file("CSS121_MBTI_2026-68.csv"); 
    
    if (!file.is_open()) {
        cerr << "Error: ไม่สามารถเปิดไฟล์ได้! เช็คชื่อไฟล์และโฟลเดอร์อีกครั้ง" << endl;
        return 1;
    }

    string line;
    getline(file, line); // ข้าม Header

    while (getline(file, line)) {
        if (line.empty()) continue; // ข้ามบรรทัดว่าง
        vector<string> row = split(line, ',');
        
        // ไฟล์นี้มี 14 columns เราต้องการถึง index 11 (Type)
        if (row.size() < 12) continue; 

        try {
            Character c;
            c.name = row[1]; //name
            
            for (int i = 0; i < 8; ++i) {//NE-FI
                c.functions[i] = stod(row[i + 3]); //เริ่มที่Index3 (NE)
            }
            
            c.type = row[11]; //Type (Index 11)
            c.distance = calculateDistance(query, c.functions);
            dataset.push_back(c);
        } catch (...) {
            // ถ้าแถวไหนมีข้อมูลผิดพลาด ให้ข้ามไป
            continue; 
        }
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
        cout << "\n================================" << endl;
        cout << "your MBTI is: " << finalType << endl;
        cout << "================================" << endl;
    } else {
        cout << "Not enough data in dataset" << endl;
    }

    return 0;
}