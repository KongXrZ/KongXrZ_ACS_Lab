#include <iostream>
using namespace std;

// โครงสร้าง Node สำหรับเก็บข้อมูลของพจน์แต่ละพจน์ในพหุนาม
struct Node {
    int coeff;   // สัมประสิทธิ์
    int expo;    // เลขชี้กำลัง
    Node* next;  // pointer ไปยัง node ถัดไป

    Node(int c, int e) {
        coeff = c;
        expo = e;
        next = nullptr;
    }
};

// คลาสสำหรับจัดการพหุนามด้วย Linked List
class Polynomial {
public:
    Node* head;

    Polynomial() {
        head = nullptr;
    }

    // ฟังก์ชัน insert()
    // ใช้แทรกพจน์ใหม่ลงในลิสต์ โดยเรียงเลขชี้กำลังจากมากไปน้อย
    // ถ้ามีพจน์ที่มีเลขชี้กำลังซ้ำกัน จะรวมสัมประสิทธิ์เข้าด้วยกัน
    void insert(int c, int e) {
        if (c == 0) return; // ถ้าสัมประสิทธิ์เป็น 0 ไม่ต้องเก็บ

        // กรณีลิสต์ว่าง หรือเลขชี้กำลังใหม่มากกว่าหัวลิสต์
        if (head == nullptr || e > head->expo) {
            Node* newNode = new Node(c, e);
            newNode->next = head;
            head = newNode;
            return;
        }

        // กรณีเลขชี้กำลังของ head ซ้ำกับพจน์ใหม่
        if (head->expo == e) {
            head->coeff += c;
            return;
        }

        // เดินหาตำแหน่งที่เหมาะสมสำหรับแทรก node ใหม่
        Node* temp = head;
        while (temp->next != nullptr && temp->next->expo > e) {
            temp = temp->next;
        }

        // ถ้ามีพจน์เลขชี้กำลังซ้ำกัน ให้รวมสัมประสิทธิ์
        if (temp->next != nullptr && temp->next->expo == e) {
            temp->next->coeff += c;
        }
        else {
            // ถ้าไม่ซ้ำ ให้สร้าง node ใหม่แล้วแทรกลงลิสต์
            Node* newNode = new Node(c, e);
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    // ฟังก์ชัน display()
    // ใช้แสดงผลพหุนามให้อยู่ในรูปแบบที่อ่านง่าย
    // เช่น 2x^5 + 4x^3 + 3x^2 + 5
    void display() {
        Node* temp = head;

        if (temp == nullptr) {
            cout << 0;
            return;
        }

        while (temp != nullptr) {
            int c = temp->coeff;
            int e = temp->expo;

            // กรณีเป็นค่าคงที่
            if (e == 0) {
                cout << c;
            }
            // กรณีเลขชี้กำลังเป็น 1
            else if (e == 1) {
                if (c == 1) cout << "x";
                else cout << c << "x";
            }
            // กรณีเลขชี้กำลังมากกว่า 1
            else {
                if (c == 1) cout << "x^" << e;
                else cout << c << "x^" << e;
            }

            // ถ้ายังมีพจน์ถัดไป ให้ใส่เครื่องหมายบวกคั่น
            if (temp->next != nullptr) {
                cout << " + ";
            }

            temp = temp->next;
        }
    }
};

// ฟังก์ชัน add()
// ใช้บวกพหุนาม 2 ตัว โดยเปรียบเทียบเลขชี้กำลังของแต่ละพจน์
Polynomial add(Polynomial p1, Polynomial p2) {
    Polynomial result;
    Node* ptr1 = p1.head;
    Node* ptr2 = p2.head;

    while (ptr1 != nullptr && ptr2 != nullptr) {
        // ถ้าเลขชี้กำลังเท่ากัน ให้นำสัมประสิทธิ์มาบวกกัน
        if (ptr1->expo == ptr2->expo) {
            result.insert(ptr1->coeff + ptr2->coeff, ptr1->expo);
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        // ถ้า p1 มีเลขชี้กำลังมากกว่า ให้นำพจน์ของ p1 ไปใส่ result
        else if (ptr1->expo > ptr2->expo) {
            result.insert(ptr1->coeff, ptr1->expo);
            ptr1 = ptr1->next;
        }
        // ถ้า p2 มีเลขชี้กำลังมากกว่า ให้นำพจน์ของ p2 ไปใส่ result
        else {
            result.insert(ptr2->coeff, ptr2->expo);
            ptr2 = ptr2->next;
        }
    }

    // ถ้ายังเหลือพจน์ใน p1 ให้นำมาใส่ต่อ
    while (ptr1 != nullptr) {
        result.insert(ptr1->coeff, ptr1->expo);
        ptr1 = ptr1->next;
    }

    // ถ้ายังเหลือพจน์ใน p2 ให้นำมาใส่ต่อ
    while (ptr2 != nullptr) {
        result.insert(ptr2->coeff, ptr2->expo);
        ptr2 = ptr2->next;
    }

    return result;
}

// ฟังก์ชัน multiply()
// ใช้คูณพหุนาม 2 ตัว โดยนำทุกพจน์ของ p1 ไปคูณกับทุกพจน์ของ p2
Polynomial multiply(Polynomial p1, Polynomial p2) {
    Polynomial result;

    Node* ptr1 = p1.head;
    while (ptr1 != nullptr) {
        Node* ptr2 = p2.head;
        while (ptr2 != nullptr) {
            // คูณสัมประสิทธิ์ และบวกเลขชี้กำลัง
            result.insert(ptr1->coeff * ptr2->coeff, ptr1->expo + ptr2->expo);
            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }

    return result;
}

int main() {
    Polynomial p1, p2;

    // กำหนดพหุนามตัวที่ 1
    // P1 = 2x^5 + 4x^3 + 3x^2 + 5
    p1.insert(2, 5);
    p1.insert(4, 3);
    p1.insert(3, 2);
    p1.insert(5, 0);

    // กำหนดพหุนามตัวที่ 2
    // P2 = 3x^4 + 2x^3 + x + 1
    p2.insert(3, 4);
    p2.insert(2, 3);
    p2.insert(1, 1);
    p2.insert(1, 0);

    // เรียกฟังก์ชันบวกและคูณพหุนาม
    Polynomial sum = add(p1, p2);
    Polynomial product = multiply(p1, p2);

    // แสดงผลลัพธ์
    cout << "P1 = ";
    p1.display();
    cout << endl;

    cout << "P2 = ";
    p2.display();
    cout << endl;

    cout << "P1 + P2 = ";
    sum.display();
    cout << endl;

    cout << "P1 * P2 = ";
    product.display();
    cout << endl;

    return 0;
}


/* วิเคราะห์ Big O
insert() = O(n)เพราะอาจต้องเดินลิสต์เพื่อหาตำแหน่งแทรก

display = O(n)เพราะต้องแสดงทุกพจน์ในลิสต์

add = O((n + m)^2)
เพราะแม้จะเดินผ่าน p1 และ p2 รวมกันเป็น O(n + m)
แต่การ insert ลง result แต่ละครั้งอาจต้องเดินลิสต์เพิ่ม

multiply = O(n^2 m^2) ในกรณีแย่ที่สุด
เพราะมีการคูณทุกพจน์ของ p1 กับ p2 ทั้งหมด n*m ครั้ง
และแต่ละครั้งที่ insert ลง result อาจใช้เวลาเพิ่มอีก

Overall Time Complexity = O(n^2 m^2)
Overall Space Complexity = O(nm)
*/