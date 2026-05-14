// CENG 551 - Term Project
// ID: 250902900
// Graphical Method

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// this function is the equation we want to solve
// we are looking for x where f(x) = 0
double f(double x) {
    return pow(x, 3) - x - 2; // x^3 - x - 2
}

int main() {

    cout << "CENG 551 - Term Project" << endl;
    cout << "Graphical Method" << endl;
    cout << "ID: 250902900" << endl;
    cout << "f(x) = x^3 - x - 2" << endl;

    // ask the user for the range of x values and the step size
    double xStart, xEnd, step;
    cout << "\nEnter start x: ";
    cin >> xStart;
    cout << "Enter end x: ";
    cin >> xEnd;
    cout << "Enter step: ";
    cin >> step;

    // print table header
    cout << "\n";
    cout << left << setw(12) << "x" << setw(15) << "f(x)" << endl;
    cout << "----------------------------" << endl;

    // save the first x and f(x) to compare with next one
    double prevX = xStart;
    double prevFx = f(xStart);
    bool found = false;

    cout << setw(12) << fixed << setprecision(4) << xStart << setw(15) << prevFx << endl;

    double x = xStart + step;

    // loop through all x values from start to end
    while (x <= xEnd + 1e-9) {

        double fx = f(x);

        cout << setw(12) << x << setw(15) << fx;

        // if prevFx and fx have different signs, the root is between them
        if (prevFx * fx < 0) {
            double root = (prevX + x) / 2.0; // midpoint as approximate root
            cout << "  <-- root between " << prevX << " and " << x << "  approx = " << root;
            found = true;
        }

        cout << endl;

        // update previous values for next step
        prevX = x;
        prevFx = fx;
        x += step;
    }

    // draw a simple ASCII graph to visualize f(x)
    cout << "\n--- Graph ---" << endl;

    // find the max value of f(x) to scale the graph
    double maxVal = 0;
    for (double xi = xStart; xi <= xEnd + 1e-9; xi += step) {
        double val = fabs(f(xi));
        if (val > maxVal) maxVal = val;
    }

    int width = 40; // width of the graph in characters

    for (double xi = xStart; xi <= xEnd + 1e-9; xi += step) {
        double fx = f(xi);

        // calculate position of * based on the value of f(x)
        int pos = (int)((fx / maxVal + 1.0) / 2.0 * width);

        if (pos < 0) pos = 0;
        if (pos > width) pos = width;

        cout << setw(6) << fixed << setprecision(2) << xi << " | ";

        // print the graph row
        for (int i = 0; i < width; i++) {
            if (i == width / 2) cout << "|"; // this is the center line where f(x) = 0
            else if (i == pos)  cout << "*"; // this is where f(x) is
            else                cout << " ";
        }

        cout << " f=" << fx << endl;
    }

    cout << endl;
    if (found)
        cout << "Root found!" << endl;
    else
        cout << "No root found. Try a wider range or smaller step." << endl;

    return 0;
}