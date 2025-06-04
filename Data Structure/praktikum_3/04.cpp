#include <bits/stdc++.h>
using namespace std;


void dfsRec(vector<vector<int>> &adj, vector<bool> &visited, vector<int> &parent, int current, int cur_parent, int &cyc) {
    visited[current] = true;
    for (int &neighbor : adj[current]) {
        if (!visited[neighbor]) {
            parent[neighbor] = current;
            dfsRec(adj, visited, parent, neighbor, current, cyc);
        } else if (neighbor != cur_parent && cyc == -1) {
            parent[neighbor] = current;
            cyc = current;
        }
    }
}

void addEdge(vector<vector<int>> &adj, int s, int t) {
    adj[s].push_back(t);
    adj[t].push_back(s);
}

void solve() {
    int cycEnd = -1;
    int V, N;
    cin >> V >> N;
    vector<vector<int>> adj(V);
    vector<bool> visited(V, false);
    vector<int> parent(V);
    
    int nu, nv;
    for (int i = 0; i < N; i++) {
        cin >> nu >> nv;
        addEdge(adj, nu, nv);
    }
        
    for (int i = 0; i < V; i++) {
        if(!visited[i]) {
            parent[i] = i;
            dfsRec(adj, visited, parent, i, -1, cycEnd);
        }
    }
    
    if (cycEnd != -1) {
        cout << "VOCALOID CYCLE PROGRAM (VCP) : CYCLE DETECTED ";
        set<int> cycle;
        while (cycle.find(cycEnd) == cycle.end()) {
            cycle.insert(cycEnd);
            cycEnd = parent[cycEnd];
        }

        for (auto &i : cycle)
            cout << i << ' ';
        
        cout << '\n';
    } else
        cout << "VOCALOID CYCLE PROGRAM (VCP) : NO CYCLE DETECTED\n";
}

int main() {
    int T;
    cin >> T;
    while (T--) solve();
}