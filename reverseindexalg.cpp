#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void showMenu() {
    cout << "\n========================================" << endl;
    cout << " || REVISED SIMPLEX OPTIMIZER || " << endl;
    cout << "========================================" << endl;
    cout << "1. Solve Linear Programming Problem" << endl;
    cout << "2. Exit" << endl;
    cout << "Enter choice: ";
}

void solve() {
    int m, n;
    cout << "\nNumber of constraints (m): "; cin >> m;
    cout << "Total variables (n, including slacks): "; cin >> n;

    vector<double> c(n);
    cout << "Objective coeffs (Minimize): ";
    for (int i = 0; i < n; i++) cin >> c[i];


    vector<vector<double>> tableau(m, vector<double>(n + 1));
    cout << "Enter Matrix A and RHS (b) row by row:" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) cin >> tableau[i][j];
        cin >> tableau[i][n];
    }

    while (true) {

        int pivotCol = -1;
        double minVal = 0;
        for (int j = 0; j < n; j++) {
            if (c[j] < minVal) {
                minVal = c[j];
                pivotCol = j;
            }
        }

        if (pivotCol == -1) break;


        int pivotRow = -1;
        double minRatio = 1e18;
        for (int i = 0; i < m; i++) {
            if (tableau[i][pivotCol] > 0) {
                double ratio = tableau[i][n] / tableau[i][pivotCol];
                if (ratio < minRatio) {
                    minRatio = ratio;
                    pivotRow = i;
                }
            }
        }

        if (pivotRow == -1) {
            cout << "Problem is not bounded " << endl;
            return;
        }


        double pivotVal = tableau[pivotRow][pivotCol];
        for (int j = 0; j <= n; j++) tableau[pivotRow][j] /= pivotVal;

        for (int i = 0; i < m; i++) {
            if (i != pivotRow) {
                double factor = tableau[i][pivotCol];
                for (int j = 0; j <= n; j++)
                    tableau[i][j] -= factor * tableau[pivotRow][j];
            }
        }


        double objFactor = c[pivotCol];
        for (int j = 0; j < n; j++) c[j] -= objFactor * tableau[pivotRow][j];

        cout << "Iterating... Variable x" << pivotCol + 1 << " entered." << endl;
    }

    cout << "\n--- OPTIMAL SOLUTION REACHED ---" << endl;
    for (int i = 0; i < m; i++) {

        for (int j = 0; j < n; j++) {
            if (tableau[i][j] == 1) {
                cout << "x" << j + 1 << " = " << tableau[i][n] << endl;
                break;
            }
        }
    }
}

int main() {
    int choice;
    while (true) {
        showMenu();
        if (!(cin >> choice)) break;
        if (choice == 1) solve();
        else break;
    }
    return 0;
}