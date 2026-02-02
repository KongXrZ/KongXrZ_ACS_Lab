#include <iostream>
using namespace std;

int findMax(int a , int b){
    if(a<b){
        return b;
    } else{
        return a;
    }
}
int main(){
    /*int n;
    cin >> n;
    if (n%2 == 0){
        cout << "Even" << endl;
    } else{
        cout << "Odd" << endl;
    }
    return 0;*/
    /*int n;
    cin >> n;
    for(int i = 1; i<=12; i++){
        cout << n << "x" << i << "=" << n*i << endl;
    }
    return 0;*/
    /*int sum = 0;
    double avg;
    int scores[5] = {10,20,30,40,50};
    for (int i =0; i<5;i++){
        sum+=scores[i];
    }
    avg = sum/5;
    cout << "sum = "<<sum<<endl;
    cout<< "avg = "<<avg<<endl;
    return 0;*/

    int max_val = findMax(45, 80);
    cout << "Max value is: " << max_val << endl;
    return 0;
}