#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

class Graph {
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency list

public:
    Graph(int V) : V(V), adj(V) {}

    // Function to add an edge between vertices u and v
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Assuming undirected graph
    }

    // Breadth First Search
    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << current << " ";

            #pragma omp parallel for
            for (int i = 0; i < adj[current].size(); ++i) {
                int next = adj[current][i];
                if (!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                }
            }
        }
    }

    // Depth First Search
    void DFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        #pragma omp parallel for
        for (int i = 0; i < adj[v].size(); ++i) {
            int next = adj[v][i];
            if (!visited[next])
                DFSUtil(next, visited);
        }
    }

    void DFS(int start) {
        vector<bool> visited(V, false);
        DFSUtil(start, visited);
    }
};


int main() {
    Graph g(6); // Creating a graph with 6 vertices

    // Adding edges to the graph
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);


    cout << "BFS traversal starting from vertex 0: ";
    g.BFS(0);
    cout << endl;

    cout << "DFS traversal starting from vertex 0: ";
    g.DFS(0);
    cout << endl;

    return 0;
}


// g++ -fopenmp graph.cpp -o graph
