#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <ctime>

using namespace std;

struct Customer {
    int id;
    string name;
    double totalSpending;
};

// ฟังก์ชันสำหรับสลับข้อมูล (Utility Function)
void swap(Customer &a, Customer &b) {
    Customer temp = a;
    a = b;
    b = temp;
}

// Partition logic แบบเดียวกับ Quicksort
int partition(vector<Customer> &customers, int left, int right) {
    // เทคนิค Senior: เลือก Pivot แบบสุ่มเพื่อป้องกัน Worst Case O(n^2)
    int pivotIndex = left + rand() % (right - left + 1);
    double pivotValue = customers[pivotIndex].totalSpending;
    
    // ย้าย pivot ไปเก็บไว้ท้ายสุดก่อน
    swap(customers[pivotIndex], customers[right]);
    
    int storeIndex = left;
    for (int i = left; i < right; i++) {
        if (customers[i].totalSpending < pivotValue) {
            swap(customers[i], customers[storeIndex]);
            storeIndex++;
        }
    }
    // ย้าย pivot กลับมาตรงกลาง
    swap(customers[storeIndex], customers[right]);
    return storeIndex;
}

// Quickselect Algorithm
double quickSelect(vector<Customer> &customers, int left, int right, int k) {
    if (left == right) {
        return customers[left].totalSpending;
    }

    int pivotIndex = partition(customers, left, right);

    if (k == pivotIndex) {
        return customers[k].totalSpending;
    } else if (k < pivotIndex) {
        return quickSelect(customers, left, pivotIndex - 1, k);
    } else {
        return quickSelect(customers, pivotIndex + 1, right, k);
    }
}

int main() {
    // Seed สำหรับการสุ่ม Pivot
    srand(time(NULL));

    // ตัวอย่างข้อมูลลูกค้า
    vector<Customer> customers = {
        {1, "A", 100.0}, {2, "B", 500.0}, {3, "C", 200.0},
        {4, "D", 800.0}, {5, "E", 300.0}, {6, "F", 700.0},
        {7, "G", 900.0}, {8, "H", 400.0}
    };

    int n = customers.size();
    
    // คำนวณหาตำแหน่ง Q3 (Index ที่ 75% ของข้อมูล)
    // สำหรับข้อมูล 8 ตัว Q3 คือ Index ที่ 6 (ตัวที่ 7 เมื่อเรียงจากน้อยไปมาก)
    int targetK = floor(0.75 * n);

    double q3Value = quickSelect(customers, 0, n - 1, targetK);

    cout << "------------------------------------------" << endl;
    cout << "Threshold for Top 25% (Q3) is: " << q3Value << endl;
    cout << "------------------------------------------" << endl;

    return 0;
}