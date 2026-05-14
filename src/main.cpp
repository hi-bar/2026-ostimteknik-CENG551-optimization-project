#include <iostream>
#include <assert.h>

void dijkstra();
void northwestcorner();
void graphical_method();
void revised_simplex();

int main(int argc, char **argv)
{
    std::cout << "Hello, Welcome to Optimization Selector!" << std::endl;
    std::cout << "Please select one of the below algorithms or press X to exit!" << std::endl;
    while (1)
    {
        std::cout << std::endl;
        std::cout << "1) Dijkstra's Algorithm" << std::endl;
        std::cout << "2) NorthWestCorner's Algorithm" << std::endl;
        std::cout << "3) Reversed Simplex Method" << std::endl;
        std::cout << "4) Graphical Method" << std::endl;
        std::cout << "5) ..." << std::endl;
        std::cout << std::endl
                  << "Your choice: ";

        const char selected = getchar();

        if (selected == 'X' || selected == 'x')
        {
            return 0;
        }

        assert(selected > 0); // assert an error if selected is not greater than 0

        switch (atoi(&selected))
        {
        case 1:
            std::cout << "You have selected 1) Dijkstra's Algorithm" << std::endl;
            dijkstra();
            break;
        case 2:
            std::cout << "You have selected 2) NorthWestCorner's Algorithm" << std::endl;
            northwestcorner();
            break;
        case 3:
            std::cout << "You have selected 3) Reversed Simplex Method" << std::endl;
            revised_simplex();
            break;
        case 4:
            std::cout << "You have selected 4) Graphical Method" << std::endl;
            graphical_method();
            break;

        default:
            std::cout << "Please select one of the algorithms listed or press X to exit!" << std::endl;
            break;
        }
    }

    return 0;
}