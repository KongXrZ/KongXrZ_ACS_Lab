#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>

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
    const int n_std = 25;
    Student students[n_std]; //กำหนดขนาดArray

    for(int i = 0; i < 20; i++){
        students[i].ID = 10001 + i; //สร้างID
        
        string randname = "";
        for(int j=0; j<4; j++) randname += (char)('A' + rand() % 26); // สร้างชื่อ สุ่มลำดับที่ 0-25 
        students[i].name = randname;

        students[i].m_score = (rand() % 16) + 35;
        students[i].f_score = (rand() % 16) + 35;
    }

    //สร้างpointer
    Student* ptrList[n_std];
    for(int i =0; i < 20; i++){
        ptrList[i] = &students[i];
    }

    //sortด้วยpointer
    for (int i = 0; i < n_std - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n_std; j++) {
            if (ptrList[j]->m_score < ptrList[min_idx]->m_score) min_idx = j;
        }
        swap(ptrList[i], ptrList[min_idx]); // สลับแค่ Pointer
    }

    //display
    cout << "Sorted by Midterm (Students = 20):\n";
    cout << left << setw(10) << "ID" << setw(10) << "Name" << setw(10) << "Midterm" << "Final" << endl;
    for(int i=0; i<20; i++) {
        cout << left << setw(10) << ptrList[i]->ID 
             << setw(10) << ptrList[i]->name 
             << setw(10) << ptrList[i]->m_score 
             << ptrList[i]->f_score << endl;
    }

    cout << "-------------------------------------\n" ;

    //เพิ่มอีก5คน
    for(int i = 20; i < 25; i++){
        students[i].ID =10001 + i;

        string randname = "";
        for(int j=0; j<4; j++) randname += (char)('A' + rand() % 26); // สร้างชื่อ สุ่มลำดับที่ 0-25 
        students[i].name = randname;

        students[i].m_score = (rand() % 16) + 35;
        students[i].f_score = (rand() % 16) + 35;

        ptrList[i] = &students[i]; //เอาpointerไปชี้ค่า
    }

    //sortด้วยpointer
    for(int i = 0; i < 25-1; i++){
        for(int j = 0; j < 25-1-i; j++){
            if(ptrList[j]->m_score > ptrList[j+1]->m_score){
                swap(ptrList[j],ptrList[j+1]);
            }
        }
    }
    //O(n^2)


    //display
    cout << "Sorted by Midterm (Students = 25):\n";
    cout << left << setw(10) << "ID" << setw(10) << "Name" << setw(10) << "Midterm" << "Final" << endl;
    for(int i=0; i<25; i++) {
        cout << left << setw(10) << ptrList[i]->ID 
             << setw(10) << ptrList[i]->name 
             << setw(10) << ptrList[i]->m_score 
             << ptrList[i]->f_score << endl;
    }

    return 0;
}