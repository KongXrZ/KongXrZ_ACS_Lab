#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

//structเก็บข้อมูลใบเสร็จ
struct Transaction {
    int transactionID;
    vector<char> items; // เก็บตัวอักษร A-H (ใช้ vector เพราะจำนวนสินค้า 2-4 ชิ้นไม่คงที่)
};

int main(){
    srand(time(NULL));
    const int num_transactions = 10; //กำหนดจำนวนTransaction
    Transaction t_list[num_transactions]; //กำหนดขนาดArrayในStruct

    char storeItems[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

    for(int i = 0; i < num_transactions; i++){
        t_list[i].transactionID = 10001 + i;
        int num_item = (rand() %3) + 2; //สุ่มจำนวนสินค้า2-4ชิ้น
        bool selected[8] = {false};
        while(t_list[i].items.size() < num_item ){
            int idx = rand() %8;
            if(!selected[idx]){
                t_list[i].items.push_back(storeItems[idx]);
                selected[idx] = {true};
            }
        }
    }

    //display
    for (int i = 0; i < num_transactions; i++) {
        cout << "Transaction ID: " << t_list[i].transactionID << endl;
        cout << "Items: ";
        for (int j = 0; j < t_list[i].items.size(); j++) {
            cout << t_list[i].items[j] << (j == t_list[i].items.size() - 1 ? "" : ", ");
        }
        cout << "\n" << endl;
    }

    return 0;
}

