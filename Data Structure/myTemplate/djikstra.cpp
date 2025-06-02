#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <climits>

void addEdge(std::vector<std::vector<std::pair<int, int>>> &adj, int u, int v, int w)
{
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
}

std::vector<std::pair<int, int>> djikstra(int v, std::vector<std::vector<std::pair<int, int>>> &adj, int src)
{
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::greater<std::vector<int>>> pq;

    std::vector<std::pair<int, int>> dist(v, {INT_MAX, -1});

    pq.push({0, src});
    dist[src].first = 0;

    while (!pq.empty())
    {
        int u = pq.top()[1];
        pq.pop();

        for (auto i : adj[u])
        {
            int vt = i.first;
            int wt = i.second;

            if (dist[vt].first > dist[u].first + wt)
            {
                dist[vt].first = dist[u].first + wt;
                pq.push({dist[vt].first, vt});
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
    std::vector<std::vector<int>> edgesWeight = {
        {0, 1, 4},
        {0, 2, 8},
        {1, 3, 5},
        {1, 4, 7},
        {2, 5, 2},
        {3, 6, 3},
        {4, 6, 6},
        {5, 7, 1},
        {6, 8, 9},
        {7, 8, 4},
        {7, 9, 5},
        {8, 9, 3},
        {3, 5, 4},
        {2, 4, 10},
        {1, 5, 11}
    };
    
    int V = 0;
    std::set<int> vertices;
    
    for (auto i : edgesWeight)
    {
        vertices.insert(i[0]);
        vertices.insert(i[1]);
    }
    V = vertices.size();

    std::vector<std::vector<std::pair<int, int>>> adj(V);

    for (auto i : edgesWeight)
        addEdge(adj, i[0], i[1], i[2]);

    std::vector<std::pair<int, int>> result = djikstra(V, adj, src);

    int nvertex = 0;
    for (auto i : result)
        std::cout << nvertex++ << " -- dist : " << i.first << " -- before : -> " << i.second << "\n";
    
    return 0;
}