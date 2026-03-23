#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

//structเก็บข้อมูลใบเสร็จ
struct Transaction {
    int ID;
    vector<char> items; // เก็บตัวอักษร A-H 
};

int main(){
    srand(time(NULL));
    const int num_transactions = 10; //กำหนดจำนวนTransaction
    Transaction t_list[num_transactions]; //กำหนดขนาดArrayในStruct

    char storeItems[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

    for(int i = 0; i < num_transactions; i++){
        t_list[i].ID = 10001 + i;
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

    vector<int> ItemToTransaction[8];

    for(int i = 0; i < 5; i++){
        for(char item : t_list[i].items){
            int itemIndex = item - 'A';
            ItemToTransaction[itemIndex].push_back(t_list[i].ID);
        }
    }

    cout << "=== Item to Transaction Mapping ===" << endl;
    for (int i = 0; i < 8; i++) {
        // แสดงเฉพาะสินค้าที่มีรายการซื้อเท่านั้น
        if (!ItemToTransaction[i].empty()) {
            cout << "Item " << (char)('A' + i) << " appears in Transactions: ";
            for (int id : ItemToTransaction[i]) {
                cout << id << " ";
            }
            cout << endl;
        }
    }

    return 0;
}