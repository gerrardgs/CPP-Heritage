#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm> // Untuk reverse()

using namespace std;

#define INF INT_MAX

// Struktur untuk menyimpan informasi simpul
struct Node
{
    int vertex;
    int distance;
    int parent;
};

// Fungsi untuk menampilkan jalur terpendek
void printPath(vector<Node> &shortestPath, int source, int destination)
{
    if (shortestPath[destination].parent == -1)
    {
        cout << "Tidak ada jalur dari " << source << " ke " << destination << endl;
        return;
    }

    vector<int> path;
    int current = destination;
    while (current != source)
    {
        path.push_back(current);
        current = shortestPath[current].parent;
    }

    path.push_back(source);
    reverse(path.begin(), path.end());

    cout << "Jalur terpendek: ";
    for (size_t i = 0; i < path.size(); i++)
    { // Mengubah int ke size_t
        cout << path[i] << " ";
    }
    cout << endl;
}

// Algoritma Multistage Graph (Dynamic Programming)
void multistageGraph(vector<vector<int>> &graph, int source)
{
    int n = graph.size();
    vector<Node> shortestPath(n, {0, INF, -1});
    shortestPath[source].distance = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (graph[i][j] != INF && shortestPath[i].distance + graph[i][j] < shortestPath[j].distance)
            {
                shortestPath[j].distance = shortestPath[i].distance + graph[i][j];
                shortestPath[j].parent = i;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        printPath(shortestPath, source, i);
    }
}

// Algoritma Bellman Ford (Dynamic Programming)
void bellmanFord(vector<vector<int>> &graph, int source)
{
    int n = graph.size();
    vector<Node> shortestPath(n, {0, INF, -1});
    shortestPath[source].distance = 0;

    // Relaksasi
    for (int i = 0; i < n - 1; i++)
    {
        for (int u = 0; u < n; u++)
        {
            for (int v = 0; v < n; v++)
            {
                if (graph[u][v] != INF && shortestPath[u].distance + graph[u][v] < shortestPath[v].distance)
                {
                    shortestPath[v].distance = shortestPath[u].distance + graph[u][v];
                    shortestPath[v].parent = u;
                }
            }
        }
    }

    // Mendeteksi siklus negatif
    for (int u = 0; u < n; u++)
    {
        for (int v = 0; v < n; v++)
        {
            if (graph[u][v] != INF && shortestPath[u].distance + graph[u][v] < shortestPath[v].distance)
            {
                cout << "Siklus negatif terdeteksi!" << endl;
                return;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        printPath(shortestPath, source, i);
    }
}

int main()
{
    // Menginisialisasi graf
    int n;
    cout << "Masukkan jumlah simpul: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n, INF)); // Menginisialisasi graf dengan INF

    cout << "Masukkan bobot tepi untuk setiap pasangan simpul (masukkan -1 jika tidak ada tepi):\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                cout << "Bobot tepi dari " << i << " ke " << j << ": ";
                int weight;
                cin >> weight;
                if (weight != -1)
                {
                    graph[i][j] = weight;
                }
            }
        }
    }

    // Menampilkan graf
    cout << "Graf:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (graph[i][j] == INF)
                cout << "INF ";
            else
                cout << graph[i][j] << " ";
        }
        cout << endl;
    }

    int source;
    cout << "Masukkan simpul sumber: ";
    cin >> source;

    int pilihan;
    cout << "Pilih algoritma:\n";
    cout << "1. Multistage Graph\n";
    cout << "2. Bellman-Ford\n";
    cout << "Masukkan pilihan: ";
    cin >> pilihan;

    switch (pilihan)
    {
    case 1:
        multistageGraph(graph, source);
        break;
    case 2:
        bellmanFord(graph, source);
        break;
    default:
        cout << "Pilihan tidak valid!" << endl;
    }

    return 0;
}
