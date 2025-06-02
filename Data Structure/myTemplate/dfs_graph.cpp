#include <bits/stdc++.h>
using namespace std;

void dfsRec(vector<vector<int>> &adj, vector<bool> &visited, int s, vector<int> &res) {

    visited[s] = true;

    res.push_back(s);

    for (int i : adj[s])
        if (visited[i] == false)
            dfsRec(adj, visited, i, res);
}

vector<int> DFS(vector<vector<int>> &adj, int src) {
    vector<bool> visited(adj.size(), false);
    vector<int> res;
    dfsRec(adj, visited, src, res);
    return res;
}

void addEdge(vector<vector<int>> &adj, int s, int t) {
    adj[s].push_back(t);
    adj[t].push_back(s);
}

int main() {
    int V = 5;
    vector<vector<int>> adj(V);

    vector<vector<int>> edges = {{1, 2}, {1, 0}, {2, 0}, {2, 3}, {2, 4}};
    for (auto &e : edges)
        addEdge(adj, e[0], e[1]);

    vector<int> res = DFS(adj, 4);

    for (int i = 0; i < V; i++)
        cout << res[i] << " ";
}