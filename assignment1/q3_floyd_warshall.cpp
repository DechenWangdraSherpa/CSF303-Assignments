#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const long long INF = 1e18;

void floyd_warshall(int V, vector<vector<long long>>& dist) {
    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (dist[i][k] != INF && dist[k][j] != INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            cout << "Negative weight cycle detected (e.g. at vertex " << i << ").\n";
            cout << "All-pairs shortest paths are undefined.\n";
            return;
        }
    }

    cout << "All-pairs shortest path distance matrix:\n";
    cout << "     ";
    for (int j = 0; j < V; j++) cout << "  [" << j << "]";
    cout << "\n";

    for (int i = 0; i < V; i++) {
        cout << "[" << i << "]  ";
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) cout << "  INF";
            else                    cout << "  " << dist[i][j];
        }
        cout << "\n";
    }
}

int main() {
    int V, E;
    cout << "Enter number of vertices V: ";
    cin >> V;
    cout << "Enter number of edges E: ";
    cin >> E;

    vector<vector<long long>> dist(V, vector<long long>(V, INF));
    for (int i = 0; i < V; i++) dist[i][i] = 0;

    cout << "\nFor each edge, enter: source destination weight\n";
    cout << "  (vertices are 0-indexed; parallel edges allowed — minimum is kept)\n";
    for (int i = 0; i < E; i++) {
        int u, v; long long w;
        cout << "  Edge " << i + 1 << " (u v w): ";
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w);
    }

    floyd_warshall(V, dist);
    return 0;
}

