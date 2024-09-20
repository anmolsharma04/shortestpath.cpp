#include <iostream>
#include <vector>
#include <set>
#include <climits>  // for INT_MAX

using namespace std;

// Class representing a graph using adjacency list representation
class Graph {
    int vertices;  // Number of vertices
    vector<vector<pair<int, int>>> adjList;  // Adjacency list, each node points to a vector of pairs (neighbor, weight)

public:
    // Constructor
    Graph(int v) : vertices(v) {
        adjList.resize(vertices);
    }

    // Function to add an edge to the graph (u -> v with weight w)
    void addEdge(int u, int v, int w) {
        adjList[u].push_back(make_pair(v, w));
        adjList[v].push_back(make_pair(u, w));  // For undirected graph
    }

    // Dijkstra's algorithm to find shortest path from source to all other nodes
    void dijkstra(int source) {
        // Create a set to store the nodes being processed
        set<pair<int, int>> setds;

        // Create a vector for distances and initialize them to infinity
        vector<int> dist(vertices, INT_MAX);

        // Insert the source node with distance 0
        setds.insert(make_pair(0, source));
        dist[source] = 0;

        while (!setds.empty()) {
            // The first vertex in set is the minimum distance vertex, extract it
            pair<int, int> tmp = *(setds.begin());
            setds.erase(setds.begin());

            int u = tmp.second;  // Get the vertex number

            // Traverse the neighbors of u
            for (auto i = adjList[u].begin(); i != adjList[u].end(); ++i) {
                int v = (*i).first;
                int weight = (*i).second;

                // If there is a shorter path to v through u
                if (dist[v] > dist[u] + weight) {
                    // If dist[v] was already in set, remove it
                    if (dist[v] != INT_MAX) {
                        setds.erase(setds.find(make_pair(dist[v], v)));
                    }

                    // Update dist[v]
                    dist[v] = dist[u] + weight;
                    setds.insert(make_pair(dist[v], v));
                }
            }
        }

        // Print the calculated shortest distances
        cout << "Vertex\tDistance from Source\n";
        for (int i = 0; i < vertices; ++i) {
            cout << i << "\t\t" << dist[i] << endl;
        }
    }
};

int main() {
    // Example: Graph with 5 vertices
    int V = 5;
    Graph g(V);

    // Adding edges with weights (u, v, w)
    g.addEdge(0, 1, 10);
    g.addEdge(0, 4, 5);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 4, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 0, 7);
    g.addEdge(4, 3, 2);
    g.addEdge(4, 2, 9);

    // Starting Dijkstra from vertex 0
    g.dijkstra(0);

    return 0;
}
