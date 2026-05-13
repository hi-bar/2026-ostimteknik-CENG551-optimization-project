#include <iostream>
#include <assert.h>
#include <cstdlib>
#include <ctime>

const long INF = (1L << 30); // 2^30 as large number -> infinity

int dijkstra()
{
    std::cout << "Please privode number of nodes!" << std::endl;

    int n = 1;
    if (!(std::cin >> n))
        return -1; // number of nodes taken from user (1..n)
    assert(n > 0); // assert an error if n is not greater than 0

    // adjacency matrix: weight[i][j] = -1 means no edge
    int weight[n][n] = {-1};
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            weight[i][j] = -1;

    srand((unsigned)time(NULL)); // seed randomization to fill edges (undirected)

    double density = 0.35; // 35 percent probability of an edge exists between any pair
    int maxW = 9;         // maximum edge weight/ distance

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if ((double)rand() / RAND_MAX < density)
            {
                int w = 1 + rand() % maxW; // 1--100
                weight[i][j] = w;
                weight[j][i] = w;
            }
        }
    }

    int s = 0; // source node (choosen 1 for simplicity)
               // Dijkstra without heap (O(n^2)), no vectors/pairs used
    long distance[n + 1];
    bool used[n + 1];
    for (int i = 0; i < n; ++i)
    {
        distance[i] = INF;
        used[i] = false;
    }
    distance[s] = 0;

    for (int it = 0; it < n; ++it)
    {
        int u = -1;
        long best = INF;
        for (int i = 0; i < n; ++i)
        {
            if (!used[i] && distance[i] < best)
            {
                best = distance[i];
                u = i;
            }
        }
        if (u == -1)
            break;
        used[u] = true;
        for (int v = 0; v < n; ++v)
        {
            if (weight[u][v] != -1 && !used[v])
            {
                if (distance[v] > distance[u] + weight[u][v])
                {
                    distance[v] = distance[u] + weight[u][v];
                }
            }
        }
    }

    // print adjacency matrix (optional) and distances
    std::cout << "Adjacency matrix (0 = no edge):\n";
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (weight[i][j] == -1)
                std::cout << 0;
            else
                std::cout << weight[i][j];
            if (j < n)
                std::cout << ' ';
        }
        std::cout << '\n';
    }

    std::cout << "\nShortest distances from node " << s+1 << "\n";
    for (int i = 0; i < n; ++i)
    {
        std::cout << "Node " << i + 1 << " has a distance of ";
        if (distance[i] == INF)
            std::cout << "unreachable";
        else
            std::cout << distance[i];
        if (i < n)
            std::cout << '\n';
    }
    std::cout << '\n';
    return 0;
}
