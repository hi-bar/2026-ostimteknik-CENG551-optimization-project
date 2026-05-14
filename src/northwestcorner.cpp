#include <iostream>
#include <vector>
#include <algorithm>

void northwestcorner() {
    int num_factories, num_markets;

    // 1. Get Problem Dimensions
    std::cout << "Enter number of Factories: ";
    while (!(std::cin >> num_factories)) {
        std::cout << "Invalid input. Please enter an integer only: ";
        std::cin.clear();  
        std::cin.ignore(1000, '\n');  
    }

    std::cout << "Enter number of Markets: ";
    while (!(std::cin >> num_markets)) {
        std::cout << "Invalid input. Please enter an integer only: ";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }

    std::vector<int> supply(num_factories);
    std::vector<int> demand(num_markets);

    // 2. Input Supply Values
    int total_supply = 0;
    std::cout << "\nEnter Supply for each Factory:\n";
    for (int i = 0; i < num_factories; ++i) {
        std::cout << "Factory " << i + 1 << ": ";
        std::cin >> supply[i];
        total_supply += supply[i];
    }

    // 3. Input Demand Values
    int total_demand = 0;
    std::cout << "\nEnter Demand for each Market:\n";
    for (int j = 0; j < num_markets; ++j) {
        std::cout << "Market " << j + 1 << ": ";
        std::cin >> demand[j];
        total_demand += demand[j];
    }

    // 4. Input Cost Matrix
    std::vector<std::vector<int>> cost(num_factories, std::vector<int>(num_markets));
    std::cout << "\nEnter Shipping Costs Matrix:\n";
    for (int i = 0; i < num_factories; ++i) {
        for (int j = 0; j < num_markets; ++j) {
            std::cout << "Cost from Factory " << i + 1 << " to Market " << j + 1 << ": ";
            std::cin >> cost[i][j];
        }
    }

    // 5. Handle Unbalanced Data
    if (total_supply < total_demand) {
        int difference = total_demand - total_supply;
        std::cout << "\n[Notice] Added Dummy Factory with " << difference << " supply.\n";
        num_factories++;
        supply.push_back(difference);
        cost.push_back(std::vector<int>(num_markets, 0)); 
    } 
    else if (total_demand < total_supply) {
        int difference = total_supply - total_demand;
        std::cout << "\n[Notice] Added Dummy Market with " << difference << " demand.\n";
        num_markets++;
        demand.push_back(difference);
        for (int i = 0; i < num_factories; ++i) {
            cost[i].push_back(0);
        }
    }

    // Prepare allocation matrix tracking system
    std::vector<std::vector<int>> allocation(num_factories, std::vector<int>(num_markets, 0));

    // 6. Run North-West Corner Algorithm
    int i = 0; 
    int j = 0; 
    int overall_total_cost = 0;

    std::vector<int> current_supply = supply;
    std::vector<int> current_demand = demand;

    while (i < num_factories && j < num_markets) {
        int quantity = std::min(current_supply[i], current_demand[j]);

        allocation[i][j] = quantity;
        overall_total_cost += quantity * cost[i][j];

        current_supply[i] -= quantity;
        current_demand[j] -= quantity;

        // FIXED INDEX LOGIC
        if (current_supply[i] == 0 && current_demand[j] == 0) {
            i++;
            j++;
        } else if (current_supply[i] == 0) {
            i++; 
        } else {
            j++; 
        }
    }

    // 7. Print Final Allocation Matrix Grid
    std::cout << "\n--- Shipping Distribution Matrix ---\n";
    for (int r = 0; r < num_factories; ++r) {
        for (int c = 0; c < num_markets; ++c) {
            std::cout << allocation[r][c] << "\t";
        }
        std::cout << "\n";
    }

    std::cout << "\n=========================================\n";
    std::cout << "Grand Total System Shipping Cost = " << overall_total_cost << "\n";
    std::cout << "=========================================\n";

    // 8. Cost Breakdown per Factory
    std::cout << "\n--- Total Cost Incurred by Each Factory ---\n";
    for (int r = 0; r < num_factories; ++r) {
        int factory_cost = 0;
        int items_sent = 0;
        for (int c = 0; c < num_markets; ++c) {
            factory_cost += allocation[r][c] * cost[r][c];
            items_sent += allocation[r][c];
        }
        std::cout << "Factory " << r + 1 << " shipped " << items_sent 
                  << " units | Total Cost: $" << factory_cost << "\n";
    }

    // 9. Cost Breakdown per Market
    std::cout << "\n--- Total Value Received by Each Market ---\n";
    for (int c = 0; c < num_markets; ++c) {
        int market_cost = 0;
        int items_received = 0;
        for (int r = 0; r < num_factories; ++r) {
            market_cost += allocation[r][c] * cost[r][c];
            items_received += allocation[r][c];
        }
        std::cout << "Market " << c + 1 << " received " << items_received 
                  << " units | Total Delivery Value: $" << market_cost << "\n";
    }

    std::cout << "\nPress Enter twice to exit...";
    std::cin.get(); 
    std::cin.get(); 
}
