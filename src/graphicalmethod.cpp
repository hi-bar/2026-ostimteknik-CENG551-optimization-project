// CENG 551 - Term Project
// ID: 250902900
// Graphical Method

#include <iostream>
#include <cmath>
#include <iomanip>

// this function is the equation we want to solve
// we are looking for x where f(x) = 0
double f(double x)
{
    return pow(x, 3) - x - 2; // x^3 - x - 2
}

void graphical_method()
{
    std::cout << "Graphical Method" << std::endl;
    std::cout << "f(x) = x^3 - x - 2" << std::endl;

    // ask the user for the range of x values and the step size
    double xStart, xEnd, step;
    std::cout << "\nEnter start x: ";
    std::cin >> xStart;
    std::cout << "Enter end x: ";
    std::cin >> xEnd;
    std::cout << "Enter step: ";
    std::cin >> step;

    // print table header
    std::cout << "\n";
    std::cout << std::left << std::setw(12) << "x" << std::setw(15) << "f(x)" << std::endl;
    std::cout << "----------------------------" << std::endl;

    // save the first x and f(x) to compare with next one
    double prevX = xStart;
    double prevFx = f(xStart);
    bool found = false;

    std::cout << std::setw(12) << std::fixed << std::setprecision(4) << xStart << std::setw(15) << prevFx << std::endl;

    double x = xStart + step;

    // loop through all x values from start to end
    while (x <= xEnd + 1e-9)
    {

        double fx = f(x);

        std::cout << std::setw(12) << x << std::setw(15) << fx;

        // if prevFx and fx have different signs, the root is between them
        if (prevFx * fx < 0)
        {
            double root = (prevX + x) / 2.0; // midpoint as approximate root
            std::cout << "  <-- root between " << prevX << " and " << x << "  approx = " << root;
            found = true;
        }

        std::cout << std::endl;

        // update previous values for next step
        prevX = x;
        prevFx = fx;
        x += step;
    }

    // draw a simple ASCII graph to visualize f(x)
    std::cout << "\n--- Graph ---" << std::endl;

    // find the max value of f(x) to scale the graph
    double maxVal = 0;
    for (double xi = xStart; xi <= xEnd + 1e-9; xi += step)
    {
        double val = fabs(f(xi));
        if (val > maxVal)
            maxVal = val;
    }

    int width = 40; // width of the graph in characters

    for (double xi = xStart; xi <= xEnd + 1e-9; xi += step)
    {
        double fx = f(xi);

        // calculate position of * based on the value of f(x)
        int pos = (int)((fx / maxVal + 1.0) / 2.0 * width);

        if (pos < 0)
            pos = 0;
        if (pos > width)
            pos = width;

        std::cout << std::setw(6) << std::fixed << std::setprecision(2) << xi << " | ";

        // print the graph row
        for (int i = 0; i < width; i++)
        {
            if (i == width / 2)
                std::cout << "|"; // this is the center line where f(x) = 0
            else if (i == pos)
                std::cout << "*"; // this is where f(x) is
            else
                std::cout << " ";
        }

        std::cout << " f=" << fx << std::endl;
    }

    std::cout << std::endl;
    if (found)
        std::cout << "Root found!" << std::endl;
    else
        std::cout << "No root found. Try a wider range or smaller step." << std::endl;
}