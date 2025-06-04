#include <bits/stdc++.h>
using namespace std;

bool dfsRec(int current, int total, int target, vector<vector<pair<int, int>>> &adj, set<pair<int, int>> &usedEdge) {
    if (total == target) return true;
    else if (total > target) return false;

    for (auto &[neighbor, weight] : adj[current]) {
        int u = min(current, neighbor), v = max(current, neighbor);
        if (usedEdge.count({u, v})) continue;

        usedEdge.insert({u, v});
        if (dfsRec(neighbor, total + weight, target, adj, usedEdge)) return true;
        usedEdge.erase({u, v});
    }

    return false;
}

void addEdge(vector<vector<pair<int, int>>> &adj, int u, int v, int w) {
    int N = max(u, v) + 1;
    if (adj.size() < N) adj.resize(N);
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
}

void solve() {
    vector<vector<pair<int, int>>> adj;
    int u, v, w, target;
    bool present = false;

    while (cin >> u >> v >> w) {
        if (u == 0 && v == 0 && w == 0) break;
        addEdge(adj, u, v, w);
    }

    cin >> target;

    for (int i = 1; i < adj.size(); i++) {
        set<pair<int, int>> usedEdge;
        if (dfsRec(i, 0, target, adj, usedEdge)) {
            present = true;
            break;
        }
    }

    cout << (present ? "YES\n" : "NO\n");
}

int main() {
    int t;
    cin >> t;
    while (t--) solve();
}