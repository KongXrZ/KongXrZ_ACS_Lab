#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>

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

    for(int i = 0; i < 10; i++){
        for(char item : t_list[i].items){
            int itemIndex = item - 'A';
            ItemToTransaction[itemIndex].push_back(t_list[i].ID);
        }
    }

    cout << "=== Frequent Pairs (Appear together >= 4 times) ===" << endl;

    for(int i = 0; i < 8; i++){
        for(int j = i + 1; j < 8; j++){
            vector<int> commonTransactions;
            set_intersection(
                ItemToTransaction[i].begin(), ItemToTransaction[i].end(),
                ItemToTransaction[j].begin(), ItemToTransaction[j].end(),
                back_inserter(commonTransactions)
            );

            if (commonTransactions.size() >= 4) {
                cout << "(" << (char)('A' + i) << ", " << (char)('A' + j) << ") -> " 
                     << commonTransactions.size() << " transactions" << endl;
            }
        }
    }

    return 0;
}