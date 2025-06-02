#include <bits/stdc++.h>
using namespace std;

// adjlist implementation

void addEdge(vector<vector<int>> &adjList, int src, int dest) {
        adjList[src].push_back(dest);
        adjList[dest].push_back(src);
}

void bfs(vector<vector<int>> &adjList, int &V, int startVertex) {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int currentVertex = q.front();
            cout << currentVertex << "\n";
            q.pop();

            for (int neighbor : adjList[currentVertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

int main() {
    int V = 7;
    vector<vector<int>> adjList(V);
    addEdge(adjList, 0, 1);
    addEdge(adjList, 0, 2);
    addEdge(adjList, 1, 3);
    addEdge(adjList, 1, 4);
    addEdge(adjList, 2, 5);
    addEdge(adjList, 2, 6);

    bfs(adjList, V, 2);

}