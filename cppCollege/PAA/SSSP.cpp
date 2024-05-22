#include <iostream>
#include <vector>
#include <climits> // For INT_MAX

using namespace std;

class Edge
{
public:
    int src, dest, weight;
    Edge(int u, int v, int w) : src(u), dest(v), weight(w) {}
};

class Graph
{
public:
    int V, E;
    vector<Edge> edges;

    Graph(int V, int E) : V(V), E(E) {}

    void addEdge(int u, int v, int w)
    {
        edges.emplace_back(u, v, w);
    }

    void bellmanFord(int src)
    {
        vector<int> distance(V, INT_MAX);
        vector<int> predecessor(V, -1); // Track path
        distance[src] = 0;

        // Relax edges repeatedly
        for (int i = 1; i <= V - 1; i++)
        {
            for (int j = 0; j < E; j++)
            {
                int u = edges[j].src;
                int v = edges[j].dest;
                int weight = edges[j].weight;
                if (distance[u] != INT_MAX && distance[u] + weight < distance[v])
                {
                    distance[v] = distance[u] + weight;
                    predecessor[v] = u; // Track previous vertex
                }
            }
        }

        // Check for negative-weight cycles
        for (int j = 0; j < E; j++)
        {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (distance[u] != INT_MAX && distance[u] + weight < distance[v])
            {
                cout << "Graph contains a negative-weight cycle" << endl;
                return;
            }
        }

        printSolution(distance, predecessor, src);
    }

    void printPath(const vector<int> &predecessor, int vertex)
    {
        if (vertex == -1)
            return;
        printPath(predecessor, predecessor[vertex]);
        cout << vertex << " ";
    }

    void printSolution(const vector<int> &distance, const vector<int> &predecessor, int src)
    {
        cout << "Vertex Distance from Source" << endl;
        for (int i = 0; i < V; i++)
        {
            if (distance[i] == INT_MAX)
            {
                cout << i << "\t\t" << "Infinity" << endl;
            }
            else
            {
                cout << i << "\t\t" << distance[i] << "\t\tPath: ";
                if (i != src)
                {
                    printPath(predecessor, i);
                }
                else
                {
                    cout << i;
                }
                cout << endl;
            }
        }
    }
};

int main()
{
    int V = 7;  // Number of vertices
    int E = 10; // Number of edges
    Graph graph(V, E);

    // Adding edges to the graph
    graph.addEdge(0, 1, 6);
    graph.addEdge(0, 2, 5);
    graph.addEdge(0, 3, 5);
    graph.addEdge(1, 4, -1);
    graph.addEdge(2, 1, -2);
    graph.addEdge(2, 4, 1);
    graph.addEdge(3, 2, -2);
    graph.addEdge(3, 5, -1);
    graph.addEdge(4, 6, 3);
    graph.addEdge(5, 6, 3);

    int source = 0; // Source vertex
    graph.bellmanFord(source);

    return 0;
}
