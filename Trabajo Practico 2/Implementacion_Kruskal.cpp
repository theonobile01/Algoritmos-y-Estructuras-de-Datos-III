#include <unordered_map>
#include <utility>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int weight;
    int src;
    int dest;
};

class DisjointSet {
    unordered_map<int, int> padres;
    unordered_map<int, int> rangos;

public:
    void crearSet(int n) {
        for (int i = 1; i <= n; i++) {
            padres[i] = i; // Each element i references itself
            rangos[i] = 0; // Initialize ranks
        }
    }

    int findSet(int elemento) {
        if (padres[elemento] != elemento) {
            padres[elemento] = findSet(padres[elemento]); // Path compression
        }
        return padres[elemento];
    }

    void unionSet(int x, int y) {
        int raizX = findSet(x);
        int raizY = findSet(y);

        if (raizX != raizY) { // Only union if they are different
            if (rangos[raizX] > rangos[raizY]) {
                padres[raizY] = raizX;
            } else {
                padres[raizX] = raizY;
                if (rangos[raizX] == rangos[raizY]) {
                    rangos[raizY]++;
                }
            }   
        }
    }

    int getRango(int x) {
        return rangos[findSet(x)];
    }

    int getRepresentante(int x) {
        return findSet(x);
    }
};

vector<Edge> correrKruskal(vector<Edge> edges, int n) {
    DisjointSet ds;
    ds.crearSet(n);

    
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    vector<Edge> AGM;
     // Minimum Spanning Tree
    for (Edge& edge_actual : edges) {
        int x = ds.findSet(edge_actual.src);
        int y = ds.findSet(edge_actual.dest);
        cout << edge_actual.src << "- " << edge_actual.dest << endl;
        cout <<"arista "<< edge_actual.src <<"-"<<edge_actual.dest << "reff "<< x << y << endl;
        if (x != y) {
            AGM.push_back(edge_actual); 
            ds.unionSet(x, y);
            cout <<"arista "<< edge_actual.src <<"-"<<edge_actual.dest << "reff "<< ds.findSet(edge_actual.src) << ds.findSet(edge_actual.dest) << endl;
        }

        // Stop if we have n-1 edges in the AGM
        /*if (AGM.size() == n - 1) {
            break;
        }*/
    }
    return AGM;
}

int main() {
    int n, m;
    cin >> n >> m;  // Read number of vertices and edges

    vector<Edge> grafo(m); // Create a vector of edges

    // Read all edges
    for (int i = 0; i < m; i++) {
        Edge arista;
        cin >> arista.src >> arista.weight >> arista.dest;
        grafo[i] = arista;
    }

    // Run Kruskal's algorithm
    vector<Edge> AGM = correrKruskal(grafo, n);

    // Output the resulting Minimum Spanning Tree (AGM)
    for (Edge& e : AGM) {
        std::cout << "Edge: " << e.src << " - " << e.dest << " (Weight: " << e.weight << ")\n";
    }

    return 0;
}
