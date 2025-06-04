#include <bits/stdc++.h>
using namespace std;

void addEdge(vector<vector<int>> &adjList, int src, int dest) {
        adjList[src].push_back(dest);
        adjList[dest].push_back(src);
}

bool bfs(vector<vector<int>> &adjList, int &V, int &L, int startVertex) {
    int depth = 0;
    bool ada = 0;
    vector<bool> visited(V, false);
    vector<int> nodeDepth(V, -1);
    queue<int> q;
    visited[startVertex] = true;
    nodeDepth[startVertex] = 0;
    q.push(startVertex);

    while (!q.empty()) {
        int currentVertex = q.front();
        // cout << "cur: " << currentVertex << " depth: " << depth << "\n";
        q.pop();
        
        depth = nodeDepth[currentVertex] + 1;
        for (int neighbor : adjList[currentVertex]) {
            if (!visited[neighbor]) {
                nodeDepth[neighbor] = depth;
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    for (int i = 0; i < V; i++) {
        if(nodeDepth[i] == L) {
            cout << i << endl;
            ada = 1;
        }
    }
    

    return ada;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int V, M, L, S;
    cin >> V >> M >> L;
    cin >> S;

    vector<vector<int>> adjList(V);

    int nu, nv;
    for (int i = 0; i < M; i++) {
        cin >> nu >> nv;
        addEdge(adjList, nu, nv);
    }
    
    if(!bfs(adjList, V, L, S)) cout << "Not Found";

}