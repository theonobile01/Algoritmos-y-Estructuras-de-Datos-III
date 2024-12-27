#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();
vector<vector<int>> distance_graph;
vector<int> node_order;
vector<long long> solution;
vector<bool> added_nodes;
int n;


void calcularOptimalidadDeK(int k, int indK) {
    long long distanciaTotal = 0;
    for (int j = 0; j < n; j++){
        for (int i = 0; i < n; i++){
            if (added_nodes[i] && added_nodes[j]){
                distanciaTotal += distance_graph[i][j];
            }
        }
    }

    solution[indK] = distanciaTotal;
}

void runFloydWarshall() {
    for (int k = n-1; k >= 0; k--) {
        int esquina = node_order[k];
        added_nodes[esquina] = true;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                    distance_graph[i][j] = min(distance_graph[i][j], distance_graph[i][esquina] + distance_graph[esquina][j]);
                }
            }
        calcularOptimalidadDeK(esquina, k);
    }
}

int main() {
    cin >> n;

    distance_graph.assign(n, vector<int>(n,0));
    node_order.resize(n);
    solution.assign(n,0);
    added_nodes.assign(n,false);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> distance_graph[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        cin >> node_order[i];
        node_order[i]--;
    }

    runFloydWarshall();

    for (int i = 0; i < n; i++) {
        if ( i == n-1){
            cout << solution[i];
        }
        else {
            cout << solution[i] << " ";
        }
    }
    return 0;
}
