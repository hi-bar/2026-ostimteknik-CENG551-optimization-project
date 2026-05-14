#include <iostream>
#include <vector>
#include <iomanip>

void revised_simplex() {
    int m, n;
    std::cout << "\nNumber of constraints (m): "; 
    std::cin >> m;
    std::cout << "Total variables (n, including slacks): "; 
    std::cin >> n;

    std::vector<double> c(n);
    std::cout << "Objective coeffs (Minimize): ";
    for (int i = 0; i < n; i++) std::cin >> c[i];


    std::vector<std::vector<double>> tableau(m, std::vector<double>(n + 1));
    std::cout << "Enter Matrix A and RHS (b) row by row:" << std::endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) std::cin >> tableau[i][j];
        std::cin >> tableau[i][n];
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
            std::cout << "Problem is not bounded " << std::endl;
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

        std::cout << "Iterating... Variable x" << pivotCol + 1 << " entered." << std::endl;
    }

    std::cout << "\n--- OPTIMAL SOLUTION REACHED ---" << std::endl;
    for (int i = 0; i < m; i++) {

        for (int j = 0; j < n; j++) {
            if (tableau[i][j] == 1) {
                std::cout << "x" << j + 1 << " = " << tableau[i][n] << std::endl;
                break;
            }
        }
    }
}
