#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Edge {
    int u, v, w;
};

void bellman_ford(int V, int src, const vector<Edge>& edges) {
    const long long INF = LLONG_MAX;
    vector<long long> dist(V, INF);
    dist[src] = 0;

    for (int iter = 0; iter < V - 1; iter++) {
        bool updated = false;
        for (const auto& e : edges) {
            if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
                updated = true;
            }
        }
        if (!updated) break;
    }

    bool neg_cycle = false;
    for (const auto& e : edges) {
        if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
            neg_cycle = true;
            break;
        }
    }

    if (neg_cycle) {
        cout << "Negative weight cycle detected! Shortest paths are undefined.\n";
        return;
    }

    cout << "Shortest distances from source vertex " << src << ":\n";
    for (int i = 0; i < V; i++) {
        cout << "  Vertex " << i << " : ";
        if (dist[i] == INF) cout << "INF\n";
        else                 cout << dist[i] << "\n";
    }
}

int main() {
    int V, E;
    cout << "Enter number of vertices V: ";
    cin >> V;
    cout << "Enter number of edges E: ";
    cin >> E;

    vector<Edge> edges(E);
    cout << "\nFor each edge, enter: source destination weight\n";
    cout << "  (vertices are 0-indexed; weights can be negative)\n";
    for (int i = 0; i < E; i++) {
        cout << "  Edge " << i + 1 << " (u v w): ";
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    int src;
    cout << "\nEnter source vertex (0 to " << V - 1 << "): ";
    cin >> src;

    bellman_ford(V, src, edges);
    return 0;
}
