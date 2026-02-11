#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
//#include <algorithm>

using namespace std;

//Gauss Elimination with Pivoting
void gaussEliminationPivoting(int n, vector<vector<double>> A, vector<double> b) {
    const double EPSILON = 1e-9;

    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int j = i + 1; j < n; j++) {
            if (abs(A[j][i]) > abs(A[pivot][i])) pivot = j;
        }

        if (abs(A[pivot][i]) < EPSILON) {
            cout << "Gauss Elimination: Can't find the answers (Singular Matrix)" << endl;
            return;
        }

        swap(A[i], A[pivot]);
        swap(b[i], b[pivot]);

        for (int k = i + 1; k < n; k++) {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j < n; j++) {
                A[k][j] -= factor * A[i][j];
            }
            b[k] -= factor * b[i];
        }
    }

    vector<double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }

    cout << "Gauss Elimination Result: ";
    for (double val : x) cout << fixed << setprecision(2) << val << " ";
    cout << endl;
}

//Gauss-Jordan Elimination
bool gaussJordan(int n, vector<vector<double>> A, vector<double> &b, bool printOutput = true) {
    const double EPSILON = 1e-9;

    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int j = i + 1; j < n; j++) {
            if (abs(A[j][i]) > abs(A[pivot][i])) pivot = j;
        }

        if (abs(A[pivot][i]) < EPSILON) {
            if (printOutput) cout << "Gauss-Jordan: Can't find the answers (Singular Matrix)" << endl;
            return false;
        }

        swap(A[i], A[pivot]);
        swap(b[i], b[pivot]);

        double divisor = A[i][i];
        for (int j = i; j < n; j++) A[i][j] /= divisor;
        b[i] /= divisor;

        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = A[k][i];
                for (int j = i; j < n; j++) A[k][j] -= factor * A[i][j];
                b[k] -= factor * b[i];
            }
        }
    }
    
    if (printOutput) {
        cout << "Gauss-Jordan Result: ";
        for (double val : b) cout << fixed << setprecision(2) << val << " ";
        cout << endl;
    }
    return true;
}

void LUFactorization(int n, vector<vector<double>> A, vector<double> B) {

    vector<vector<double>> L(n, vector<double>(n, 0));
    vector<vector<double>> U = A;
    vector<double> Y(n, 0);
    vector<double> X(n, 0);

    const double EPS = 1e-12;

    // กำหนด L diagonal = 1
    for (int i = 0; i < n; i++)
        L[i][i] = 1.0;

    // ===== LU Decomposition with Partial Pivoting =====
    for (int i = 0; i < n; i++) {

        //หา pivot แถวที่มีค่าสูงสุด
        int pivot = i;
        for (int r = i + 1; r < n; r++)
            if (fabs(U[r][i]) > fabs(U[pivot][i]))
                pivot = r;

        //เช็ค singular
        if (fabs(U[pivot][i]) < EPS) {
            cout << "LU Factorization Result: ";
            cout << "Matrix is singular\n";
            return;
        }

        //สลับแถว U และ B
        if (pivot != i) {
            swap(U[i], U[pivot]);
            swap(B[i], B[pivot]);

            // ต้องสลับ L เฉพาะคอลัมน์ก่อนหน้า
            for (int k = 0; k < i; k++)
                swap(L[i][k], L[pivot][k]);
        }

        //คำนวณค่า L และ U
        for (int j = i + 1; j < n; j++) {

            L[j][i] = U[j][i] / U[i][i];

            for (int k = i; k < n; k++)
                U[j][k] -= L[j][i] * U[i][k];
            U[j][i] = 0.0;
        }
    }

    // ===== Forward Substitution =====
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < i; j++)
            sum += L[i][j] * Y[j];

        Y[i] = B[i] - sum;
    }

    // ===== Back Substitution =====
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < n; j++)
            sum += U[i][j] * X[j];

        X[i] = (Y[i] - sum) / U[i][i];
    }

    // ===== แสดงคำตอบ =====
    cout << "LU Factorization Result:\n";
    cout << fixed << setprecision(2);
    for (int i = 0; i < n; i++)
        cout << "x" << i + 1 << " = " << X[i] << endl;
}


// ================= Inverse Matrix =================
vector<vector<double>> inverseMatrix(vector<vector<double>> A) {
    int n = A.size();
    vector<vector<double>> inv(n, vector<double>(n));

    for (int j = 0; j < n; j++) {
        
        //สร้างMatrixเอกลักษณ์จาก n
        vector<double> b(n, 0.0);
        b[j] = 1.0; 

        bool success = gaussJordan(n, A, b, false);

        if (!success) {
            cout << "Inverse Matrix: Matrix is singular (no inverse exists)\n";
            return {};
        }

        // เอาMatrix b (A Inverse) มาใส่
        for (int i = 0; i < n; i++) {
            inv[i][j] = b[i];
        }
    }

    return inv;
}
void printMatrix(vector<vector<double>> M) {

    if (M.empty()) {
        cout << "Can't show matrix (No inverse matrix)\n";
        return;
    }

    cout << "\nA^-1 (Inverse Matrix):\n";
    cout << fixed << setprecision(2);

    for (int i = 0; i < M.size(); i++) {
        for (int j = 0; j < M.size(); j++) {
            cout << setw(12) << M[i][j] << " ";
        }
        cout << endl;
    }
}


int main() {
    
    cout << "--- CSS114_Project - KongXrZ and Prabdragon ---" << endl;

    //โจทย์1
    int n = 3; //ขนาดของmatrix 3*3
    vector<vector<double>> A = {
        {2, 1, 3}, 
        {4, 3, 5},
        {6, 5, 5}
    };
    vector<double> b = {1, 1, -3};
    gaussEliminationPivoting(n, A, b);
    gaussJordan(n, A, b);
    LUFactorization(n,A,b);
    cout << "-------------------------------------------------\n" << endl;

    //โจทย์2
    int n2 = 4;
    vector<vector<double>> C = {
        {2, -1, -3, 1},
        {1, 1, 1, -2},
        {3, 2, -3, -4},
        {-1, -4, 1, 1}
    };
    vector<double> d = {9, 10, 6, 6};

    gaussEliminationPivoting(n2, C, d);
    gaussJordan(n2, C, d);
    LUFactorization(n2, C, d);
    cout << "-------------------------------------------------\n" << endl;

    //โจทย์3 Inverse
    vector<vector<double>> E = {
        {1, 2, -3},
        {-1, 1, -1},
        {0, -2, 3}
    };
    vector<vector<double>> invA = inverseMatrix(E);
    printMatrix(invA);
    cout << "-------------------------------------------------\n" << endl;

    //โจทย์4 
    int n4 = 3;
    vector<vector<double>> F = {
        {1, 2, 3},     // แถว 1
        {-1, -1, -1},  // แถว 2
        {1, 2, 3}      // แถว 3 (ซ้ำกับแถว 1 --> ทำให้เป็น Singular)
    };
    vector<double> g = {5, 3, -1};

    // 2. เรียกฟังก์ชันทดสอบ
    
    //cout << ">> Gauss Elimination:" << endl;
    gaussEliminationPivoting(n4, F, g);

    //cout << "\n>> Gauss-Jordan:" << endl;
    gaussJordan(n4, F, g);

    //cout << "\n>> LU Factorization:" << endl;
    LUFactorization(n4, F, g);
    
    //cout << "\n>> Finding Inverse Matrix:" << endl;
    vector<vector<double>> invF = inverseMatrix(F);
    printMatrix(invF); // ต้องขึ้นว่า No inverse matrix
    
    cout << "-------------------------------------------------" << endl;

    return 0;
}