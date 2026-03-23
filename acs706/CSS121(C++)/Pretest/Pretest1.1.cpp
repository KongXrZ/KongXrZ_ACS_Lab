#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

struct Student
{
    int ID;
    string name;
    int m_score;
    int f_score;
};


int main() {
    srand(time(NULL));

    const int n_std = 20;
    Student students[n_std]; //กำหนดขนาดArray

    for(int i = 0; i < n_std; i++){
        students[i].ID = 10001 + i; //สร้างID

        string randname = "";
        for(int j = 0; j < 4; j++){
            char c = 'A' + (rand() % 26); // สุ่มลำดับที่ 0-25 
            randname += c;
        }
        students[i].name = randname;

        students[i].m_score = (rand() % 16) + 35;
        students[i].f_score = (rand() % 16) + 35;
    }

    //ตั้งหัวตาราง
    cout << left << setw(10) << "ID" 
         << setw(10) << "Name" 
         << setw(10) << "Midterm" 
         << "Final" << endl;
    cout << "---------------------------------------" << endl;    

    //ใส่ค่า 10 ชื่อ
    for (int i = 0; i < 10; i++) {
        cout << left << setw(10) << students[i].ID 
             << setw(10) << students[i].name 
             << setw(10) << students[i].m_score
             << students[i].f_score << endl;
    }

    return 0;


}