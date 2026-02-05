#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

//Gauss Elimination with Pivoting
void gaussEliminationPivoting(int n, vector<vector<double>> A, vector<double> b) {
    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int j = i + 1; j < n; j++) {
            if (abs(A[j][i]) > abs(A[pivot][i])) pivot = j;
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
void gaussJordan(int n, vector<vector<double>> A, vector<double> b) {
    for (int i = 0; i < n; i++) {
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
    
    cout << "Gauss-Jordan Result: ";
    for (double val : b) cout << fixed << setprecision(4) << val << " ";
    cout << endl;
}



int main() {
    //ขก.ทำUI รวมโค้ดค่อยทำ
    int n = 3; //ขนาดของmatrix 3*3
    vector<vector<double>> A = {{2, 1, 3}, {4, 3, 5}, {6, 5, 5}}; //Matrixแรก | สมการฝั่งซ้าย
    vector<double> b = {1, 1, -3}; //Matrixที่2 | สมการฝั่งขวา

    cout << "--- CSS114_Project - KongXrZ and Prabdragon ---" << endl;
    gaussEliminationPivoting(n, A, b);
    gaussJordan(n, A, b);

    return 0;
}