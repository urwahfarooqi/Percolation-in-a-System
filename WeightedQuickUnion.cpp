#include <iostream>
#include <vector>

using namespace std;

class Graph {
private:
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency list

    void DFS(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                DFS(neighbor, visited);
            }
        }
    }

public:
    Graph(int V) : V(V) {
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // For undirected graph
    }

    void connectedComponents() {
        vector<bool> visited(V, false);

        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                cout << "Component: ";
                DFS(i, visited);
                cout << endl;
            }
        }
    }
};

// Example Usage
int main() {
    Graph g(5); // 5 vertices
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(3, 4);

    cout << "Connected Components:" << endl;
    g.connectedComponents();

    return 0;
}
