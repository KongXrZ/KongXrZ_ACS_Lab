#include <iostream>
using namespace std;

// โครงสร้าง Node สำหรับเก็บพจน์ของพหุนาม
struct Node {
    float coeff;    // สัมประสิทธิ์ (เช่น 5, 3, 7)
    int expo;       // เลขชี้กำลัง (เช่น 2, 1, 0)
    Node* next;

    Node(float c, int e) : coeff(c), expo(e), next(nullptr) {}
};

// คลาสสำหรับจัดการพหุนาม
class Polynomial {
public:
    Node* head;

    Polynomial() : head(nullptr) {}

    // ฟังก์ชันเพิ่มพจน์ (Insert) โดยเรียงจากเลขชี้กำลังมากไปน้อย
    void insert(float c, int e) {
        Node* newNode = new Node(c, e);
        if (!head || e > head->expo) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next && temp->next->expo >= e) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    // ฟังก์ชันแสดงผลพหุนาม
    void display() {
        Node* temp = head;
        while (temp) {
            cout << temp->coeff << "x^" << temp->expo;
            temp = temp->next;
            if (temp) cout << " + ";
        }
        cout << endl;
    }
};

// ฟังก์ชันบวกพหุนาม 2 ชุด (Polynomial Addition)
Polynomial add(Polynomial p1, Polynomial p2) {
    Polynomial result;
    Node* ptr1 = p1.head;
    Node* ptr2 = p2.head;

    while (ptr1 && ptr2) {
        if (ptr1->expo == ptr2->expo) {
            result.insert(ptr1->coeff + ptr2->coeff, ptr1->expo);
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        } else if (ptr1->expo > ptr2->expo) {
            result.insert(ptr1->coeff, ptr1->expo);
            ptr1 = ptr1->next;
        } else {
            result.insert(ptr2->coeff, ptr2->expo);
            ptr2 = ptr2->next;
        }
    }

    // เก็บพจน์ที่เหลือ
    while (ptr1) { result.insert(ptr1->coeff, ptr1->expo); ptr1 = ptr1->next; }
    while (ptr2) { result.insert(ptr2->coeff, ptr2->expo); ptr2 = ptr2->next; }

    return result;
}

int main() {
    Polynomial poly1, poly2;

    // พหุนามที่ 1: 5x^2 + 4x^1 + 2x^0
    poly1.insert(5, 2); poly1.insert(4, 1); poly1.insert(2, 0);

    // พหุนามที่ 2: 3x^2 + 2x^1 + 8x^0
    poly2.insert(3, 2); poly2.insert(2, 1); poly2.insert(8, 0);

    cout << "Poly 1: "; poly1.display();
    cout << "Poly 2: "; poly2.display();

    Polynomial sum = add(poly1, poly2);
    cout << "Sum   : "; sum.display();

    return 0;
}