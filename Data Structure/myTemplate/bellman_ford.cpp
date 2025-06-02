#include <iostream>
#include <vector>
#include <set>
#include <climits>

std::vector<std::pair<int, int>> bellmanFord(int v, std::vector<std::pair<std::pair<int, int>, int>> &edges, int src)
{
    std::vector<std::pair<int, int>> dist(v, {INT_MAX, -1});
    dist[src] = {0, -1};

    for (size_t i = 0; i < v; i++)
    {
        for (auto j : edges)
        {
            int u = j.first.first;
			int vt = j.first.second;
			int wt = j.second;

            if (dist[u].first != INT_MAX && dist[u].first + wt < dist[vt].first)
            {
                if (i == v - 1)
                    return {{INT_MAX, -1}};
               
                dist[vt].first = dist[u].first + wt;
                dist[vt].second = u;
            }
        }
    }

    return dist;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    
    int src = 0;

    // std::vector<std::vector<int>> edgesWeight = {{0, 1, 4}, {0, 2, 8}, {1, 4, 6}, {2, 3, 2}, {3, 4, 10}};
    std::vector<std::pair<std::pair<int, int>, int>> edgesWeight = {
        {{0, 1}, 4},
        {{0, 2}, 8},
        {{1, 3}, 5},
        {{1, 4}, 7},
        {{2, 5}, 2},
        {{3, 6}, 3},
        {{4, 6}, 6},
        {{5, 7}, 1},
        {{6, 8}, 9},
        {{7, 8}, 4},
        {{7, 9}, 5},
        {{8, 9}, 3},
        {{3, 5}, 4},
        {{2, 4}, 10},
        {{1, 5}, 11}
    };
    
    int V = 0;
    std::set<int> vertices;
    
    for (auto i : edgesWeight)
    {
        vertices.insert(i.first.first);
        vertices.insert(i.first.second);
    }
    V = vertices.size();

    bellmanFord(V, edgesWeight, src);

    std::vector<std::pair<int, int>> result = bellmanFord(V, edgesWeight, src);

    int nvertex = 0;
    for (auto i : result)
    {
        std::cout << nvertex++ << " -- dist : " << i.first << " -- before : -> " << i.second << "\n";
    }
    return 0;
}