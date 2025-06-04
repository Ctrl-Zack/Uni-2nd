#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <climits>

void addEdge(std::vector<std::vector<std::pair<int, int>>> &adj, int u, int v, int w)
{
    adj[u].push_back({v, w});
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

void printPath(std::vector<std::pair<int, int>> &result, int now) {
    if(now == -1) return;
    printPath(result, result[now].second);
    std::cout << now << " ";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    
    int V, N, S, E;
    std::cin >> V >> N;

    std::vector<std::vector<std::pair<int, int>>> adj(V);

    int a, b, c;
    for (int i = 0; i < N; i++) {
        std::cin >> a >> b >> c;
        addEdge(adj, a, b, c);
    }

    std::cin >> S >> E;

    std::vector<std::pair<int, int>> result = djikstra(V, adj, S);

    // int nvertex = 0;
    // for (auto i : result)
    //     std::cout << nvertex++ << " -- dist : " << i.first << " -- before : -> " << i.second << "\n";
    bool found = (result[E].first == INT_MAX && result[E].second == -1) ? 0 : 1;
    if(found)
    {
        std::cout << "Path found with cost " << result[E].first << ": ";
        printPath(result, E);
    }
    else
        std::cout << "Impossible to find the path";

    
    return 0;
}