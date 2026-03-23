#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

struct Student
{
    int ID;
    string name;
    int m_score;
    int f_score;
};

struct TreeNode {
    int keyFinalScore;
    vector<Student*> students; // รายชื่อนักศึกษาที่มี final เท่ากัน
    TreeNode* left;
    TreeNode* right;
};

TreeNode* createNode(Student* s) {
    TreeNode* newNode = new TreeNode();
    newNode->keyFinalScore = s->f_score;
    newNode->students.push_back(s);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TreeNode* insert(TreeNode* root, Student* s) {
    if (root == NULL) return createNode(s);
    if (s->f_score < root->keyFinalScore) {// เปรียบเทียบโดยใช้ student->f_score
        root->left = insert(root->left, s);
    } else if (s->f_score > root->keyFinalScore) {
        root->right = insert(root->right, s);
    } else {
        root->students.push_back(s);// กรณีคะแนนเท่ากัน ยัดลง vector
    }
    return root;
}
//O(\log n)

void inorder(TreeNode* root) {
    if (root == NULL) return;
    inorder(root->left);

    cout << "Final Score " << root->keyFinalScore << ":" << endl;
    for (Student* s : root->students) {
        cout << "   ID: " << s->ID 
             << ", Name: " << s->name 
             << ", Midterm: " << s->m_score 
             << ", Final: " << s->f_score << endl;
    }
    inorder(root->right);
}

int main() {
    srand(time(NULL));

    const int n_std = 25;
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

    Student* ptrList[n_std];
    for(int i =0; i < 25; i++){
        ptrList[i] = &students[i];
    }

    // สร้างpointer ที่เก็บที่อยู่ของ ptrList (Array ของ Pointer)
    Student** pp = ptrList;

    TreeNode* root = NULL;
    for (int i = 0; i < n_std; i++) {
        root = insert(root, *(pp + i));
    }

    cout << "\n===== Sorted by Final Score =====\n";
    inorder(root);
    
    return 0;
}