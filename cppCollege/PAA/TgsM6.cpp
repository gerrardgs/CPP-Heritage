#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int minDistance = INT_MAX;
vector<int> shortestPath;

void findShortestPath(vector<vector<int>> &graph, vector<int> &path, vector<bool> &visited, int currentDistance) {
    int currentCity = path.back();

    if (path.size() == graph.size()) {
        currentDistance += graph[currentCity][0]; // Add distance back to the starting point
        if (currentDistance < minDistance) {
            minDistance = currentDistance;
            shortestPath = path;
        }
        return;
    }

    for (int i = 0; i < graph.size(); i++) {
        if (!visited[i]) {
            visited[i] = true;
            path.push_back(i);
            
            findShortestPath(graph, path, visited, currentDistance + graph[currentCity][i]);
            
            visited[i] = false;
            path.pop_back();
        }
    }
}

int main() {
    // Representasi graf berdasarkan soal
    vector<vector<int>> graph = {{0, 10, 30, 25}, {10, 0, 20, 15}, {30, 20, 0 ,35}, {25 ,15 ,35 ,0}};
    
    vector<bool> visited(4, false);
    visited[0] = true; // Start from city A
    
    vector<int> path = {0}; // Start from city A

    findShortestPath(graph, path, visited, 0);

    cout << "Rute terpendek: ";
    for (int city : shortestPath) {
        cout << char(city + 'A') << " ";
    }

    cout << char(0 + 'A'); // Go back to node A
    cout << "\nTotal Jarak: " << minDistance << endl;

    return 0;
}

// A - B - C - D (JALUR BARU DENGAN PENJUMLAHAN JALUR DARI BC DAN BD) - A (JALUR BARU DENGAN PENJUMLAHAN JALUR DARI BD DAN BA)
// 10 + 20 + (20+15) + (15+10)
// 90
