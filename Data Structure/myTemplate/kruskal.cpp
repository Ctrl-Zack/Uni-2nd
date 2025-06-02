#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define edge pair<int, int>
#define weighted_edge pair<int, edge>

void initialize_parent(vector<int>& parent, int V) {
    parent.resize(V);
    for (int i = 0; i < V; ++i)
        parent[i] = i;
}

int find_set(const vector<int>& parent, int i) {
    if (i == parent[i])
        return i;
    return find_set(parent, parent[i]);
}

void union_set(vector<int>& parent, int u, int v) {
    parent[u] = parent[v];
}

vector<weighted_edge> kruskal(int V, vector<weighted_edge>& G) {
    vector<weighted_edge> T;
    vector<int> parent;
    initialize_parent(parent, V);
    sort(G.begin(), G.end());
    for (auto& e : G) {
        int u = e.second.first;
        int v = e.second.second;
        int uRep = find_set(parent, u);
        int vRep = find_set(parent, v);
        if (uRep != vRep) {
            T.push_back(e);
            union_set(parent, uRep, vRep);
        }
    }
    return T;
}

void printMST(const vector<weighted_edge>& T) {
    cout << "Edge : Weight\n";
    for (auto& e : T) {
        cout << e.second.first << " - " << e.second.second << " : " << e.first << '\n';
    }
}

int main() {
    int V = 6;
    vector<weighted_edge> Graph;
    Graph.push_back({4, {0, 1}});
    Graph.push_back({4, {0, 2}});
    Graph.push_back({2, {1, 2}});
    Graph.push_back({4, {1, 0}});
    Graph.push_back({4, {2, 0}});
    Graph.push_back({2, {2, 1}});
    Graph.push_back({3, {2, 3}});
    Graph.push_back({2, {2, 5}});
    Graph.push_back({4, {2, 4}});
    Graph.push_back({3, {3, 2}});
    Graph.push_back({3, {3, 4}});
    Graph.push_back({4, {4, 2}});
    Graph.push_back({3, {4, 3}});
    Graph.push_back({2, {5, 2}});
    Graph.push_back({3, {5, 4}});
    vector<weighted_edge> MST = kruskal(V, Graph);
    printMST(MST);
    return 0;
}
