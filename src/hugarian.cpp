#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <algorithm>
#include <string>
#include <iomanip>

using namespace std;

const int MAXN = 105;

int matrix_size;
int original_cost[MAXN][MAXN];
int cost[MAXN][MAXN];

// Matching arrays
int match_x[MAXN]; // Job matched to worker i
int match_y[MAXN]; // Worker matched to job j

// Functions for step-by-step matrix reduction

// Function to beautifully print the matrix
void print_matrix(const string &step_name)
{
    cout << "\n--- " << step_name << " ---\n";
    for (int i = 1; i <= matrix_size; i++)
    {
        for (int j = 1; j <= matrix_size; j++)
        {
            cout << setw(5) << cost[i][j];
        }
        cout << "\n";
    }
}

// Step 1: Subtract row minimums
void subtract_row_mins()
{
    for (int i = 1; i <= matrix_size; i++)
    {
        int min_val = INT_MAX;
        for (int j = 1; j <= matrix_size; j++)
        {
            min_val = min(min_val, cost[i][j]);
        }
        for (int j = 1; j <= matrix_size; j++)
        {
            cost[i][j] -= min_val;
        }
    }
}

// Step 2: Subtract column minimums
void subtract_col_mins()
{
    for (int j = 1; j <= matrix_size; j++)
    {
        int min_val = INT_MAX;
        for (int i = 1; i <= matrix_size; i++)
        {
            min_val = min(min_val, cost[i][j]);
        }
        for (int i = 1; i <= matrix_size; i++)
        {
            cost[i][j] -= min_val;
        }
    }
}

// Bipartite matching using DFS to find max number of assignments (zeros)
bool dfs(int u, vector<bool> &visited)
{
    for (int v = 1; v <= matrix_size; v++)
    {
        if (cost[u][v] == 0 && !visited[v])
        {
            visited[v] = true;
            if (match_y[v] == 0 || dfs(match_y[v], visited))
            {
                match_x[u] = v;
                match_y[v] = u;
                return true;
            }
        }
    }
    return false;
}

// Check if we have an optimal assignment (can we assign all N workers?)
bool check_optimal()
{
    fill(match_x, match_x + MAXN, 0);
    fill(match_y, match_y + MAXN, 0);

    int matches = 0;
    for (int i = 1; i <= matrix_size; i++)
    {
        vector<bool> visited(matrix_size + 1, false);
        if (dfs(i, visited))
        {
            matches++;
        }
    }
    return matches == matrix_size;
}

// Step 3-4: Draw lines and adjust matrix if not optimal
void adjust_matrix()
{
    // Find Minimum Vertex Cover (min lines to cover all zeros)
    vector<bool> row_covered(matrix_size + 1, false);
    vector<bool> col_covered(matrix_size + 1, false);

    // Rows not in matching
    queue<int> q;
    for (int i = 1; i <= matrix_size; i++)
    {
        if (match_x[i] == 0)
        {
            q.push(i);
            row_covered[i] = true;
        }
    }

    // BFS to find all reachable vertices via alternating paths
    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v = 1; v <= matrix_size; v++)
        {
            if (cost[u][v] == 0 && !col_covered[v])
            {
                col_covered[v] = true;
                int matched_u = match_y[v];
                if (matched_u != 0 && !row_covered[matched_u])
                {
                    row_covered[matched_u] = true;
                    q.push(matched_u);
                }
            }
        }
    }

    // The actual cover is (unvisited rows) AND (visited cols)
    for (int i = 1; i <= matrix_size; i++)
    {
        row_covered[i] = !row_covered[i];
    }

    // Find min uncovered value
    int min_uncovered = INT_MAX;
    for (int i = 1; i <= matrix_size; i++)
    {
        for (int j = 1; j <= matrix_size; j++)
        {
            if (!row_covered[i] && !col_covered[j])
            {
                min_uncovered = min(min_uncovered, cost[i][j]);
            }
        }
    }

    // Adjust matrix
    for (int i = 1; i <= matrix_size; i++)
    {
        for (int j = 1; j <= matrix_size; j++)
        {
            if (!row_covered[i] && !col_covered[j])
            {
                cost[i][j] -= min_uncovered; // Subtract from uncovered
            }
            else if (row_covered[i] && col_covered[j])
            {
                cost[i][j] += min_uncovered; // Add to double covered (intersections)
            }
        }
    }
}

// Main Hungarian Algorithm implementation (Matrix Iteration version)
void hungarian_algorithm()
{
    // Copy original costs
    for (int i = 1; i <= matrix_size; i++)
    {
        for (int j = 1; j <= matrix_size; j++)
        {
            cost[i][j] = original_cost[i][j];
        }
    }

    print_matrix("Initial State");

    // Step 1: Subtract row minimums
    subtract_row_mins();
    print_matrix("After Row Subtraction");

    // Step 2: Check if optimal, if so we are done early
    if (check_optimal())
    {
        cout << "\nOptimal assignment found early!\n";
        return;
    }

    // Step 3: Subtract column minimums
    subtract_col_mins();
    print_matrix("After Column Subtraction");

    // Loop until we find an optimal assignment
    int iteration = 1;
    while (!check_optimal())
    {
        adjust_matrix();
        print_matrix("After Matrix Adjustment (Round " + to_string(iteration) + ")");
        iteration++;
    }
}

// Extract final assignment from matching
void print_results()
{
    cout << "\n=== Optimal Assignment ===\n";
    int total_cost = 0;

    for (int worker = 1; worker <= matrix_size; worker++)
    {
        int assigned_job = match_x[worker];
        int assignment_cost = original_cost[worker][assigned_job];
        cout << "Worker " << worker
             << " -> Job " << assigned_job
             << " (Cost = " << assignment_cost << ")\n";
        total_cost += assignment_cost;
    }

    cout << "\nMinimum Total Cost = " << total_cost << endl;
}

void hungarian()
{
    cout << "Hungarian Algorithm - Assignment Problem Solver\n";
    cout << "================================================\n";

    while (true)
    {
        string input;
        cout << "\nEnter matrix size (n x n) or type 'x' to quit: ";
        cin >> input;

        if (input == "x" || input == "X")
        {
            cout << "Exiting program. Goodbye!\n";
            break;
        }

        try
        {
            matrix_size = stoi(input);
            if (matrix_size <= 0 || matrix_size >= MAXN)
            {
                cout << "That's not a valid number. Please type a number between 1 and " << MAXN - 1 << ".\n";
                continue;
            }
        }
        catch (...)
        {
            cout << "Invalid input. Please enter a valid number or 'x' to quit.\n";
            continue;
        }

        cout << "\nEnter the " << matrix_size << "x" << matrix_size
             << " cost matrix (row by row):\n";

        for (int i = 1; i <= matrix_size; i++)
        {
            for (int j = 1; j <= matrix_size; j++)
            {
                // Validate each matrix cell input
                while (!(cin >> original_cost[i][j]))
                {
                    cout << "That's not a number. Please type a number for row " << i << ", column " << j << ": ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }
        }

        // Run the Hungarian Algorithm
        hungarian_algorithm();

        // Display results
        print_results();
    }
}