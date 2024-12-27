#include <vector>
#include <iostream>
#include <limits>
#include <queue>

using namespace std;

int n, m;
vector<vector<int>> capacidades;
vector<vector<int>> adyacencias;
vector<vector<int>> flujo;
vector<int> padres;
const int INF = numeric_limits<int>::max();

int bfs(int s, int t) {
    fill(padres.begin(), padres.end(), -1);
    padres[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int act = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int vecino = 0; vecino < 2*n+2; vecino ++) {
            if (padres[vecino] == -1 && capacidades[act][vecino]>0) {
                padres[vecino] = act;
                int incrFlow = min(flow, capacidades[act][vecino]);
                if (vecino == t)
                    return incrFlow;
                q.push({vecino, incrFlow});
            }
        }
    }
    return 0;
}

int correrFF(int s, int t) {
    int flow = 0;
    int incrFlow;

    while (incrFlow = bfs(s, t)) {
        flow += incrFlow;
        int act = t;
        while (act != s) {
            int padre = padres[act];
            capacidades[padre][act] -= incrFlow;
            capacidades[act][padre] += incrFlow;
            if (padre < act) 
                flujo[padre][act] += incrFlow;
            else {
                flujo[act][padre] -= incrFlow;
            }
            act = padre;
        }
    }
    return flow;
}

int main() {
    cin >> n >> m;
    int sumaCorteF = 0;
    int sumaCorteS = 0;
    int fuente = 2 * n;
    int sumidero = 2 * n+1;

    capacidades.assign(2 * n + 2, vector<int>(2 * n + 2, 0));
    flujo.assign(2 * n + 2, vector<int>(2 * n + 2, 0));
    padres.assign(2*n+2,-1);

    for (int i = 0; i < n; i++) {
        cin >> capacidades[fuente][i];
        sumaCorteF += capacidades[fuente][i];
    }

    for (int i = 0; i < n; i++) {
        cin >> capacidades[n + i][sumidero];
        sumaCorteS += capacidades[n + i][sumidero];
    }

    if (sumaCorteF != sumaCorteS) {
        cout << "NO\n";
        return 0;
    }

    int u, p;
    for (int e = 0; e < m; e++) {
        cin >> u >> p;
        u--; 
        p--;
        capacidades[p][u + n] = INF;
        capacidades[u][p + n] = INF;

    }
        for (int i = 0; i < n; i++){
        int copia = i + n;
        capacidades[i][copia] = INF;
    }


    int flujoMax = correrFF(fuente, sumidero);

    if (flujoMax == sumaCorteF) {
        cout << "YES\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << flujo[i][j + n] << " ";
            }
            cout << "\n";
        }
    } else {
        cout << "NO\n";
    }

    return 0;
}
