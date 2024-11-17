#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>

using namespace std;

class DisjointSet {
public:
    vector<int> padres;
    vector<int> rangos;

    void crearSet(int n) {
        padres.resize(n);
        rangos.resize(n, 0);
        for (int i = 1; i < n; i++) {
            padres[i] = i; // each element is initially its o_inn parent
        }
    }

    int findSet(int elemento) {
        if (padres[elemento] != elemento) {
            padres[elemento] = findSet(padres[elemento]);
        }
        return padres[elemento];
    }

    void unionSet(int x, int y) {
        int raizX = findSet(x);
        int raizY = findSet(y);
        if (raizX != raizY) {
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
};

struct Edge {
    int x, y, w, index;
};

bool comparaEdges(const Edge &e1, const Edge &e2) {
    return e1.w < e2.w || (e1.w == e2.w && e1.index > e2.index);
}

vector<vector<pair<int, int>>> g; 
vector<bool> vis; 
vector<int> lo_in, in, respuesta;
DisjointSet bosque;
vector<Edge> edges;
int timer;

void dfs(int v, int p) {
    vis[v] = true;
    in[v] = lo_in[v] = timer++;
    for (pair<int, int> i : g[v]) {
        int c = i.first, id = i.second;
        if (id == p) continue;;
        if (vis[c]) {
            lo_in[v] = min(lo_in[v], in[c]);
            continue;;
        }
        dfs(c, id);
        lo_in[v] = min(lo_in[v], lo_in[c]);
        if (lo_in[c] > in[v]) {
            respuesta[id] = 2; 
        }
    }
}

void caracterizaEdges() {
    int i = 0;
    while (i < edges.size()){
        int r = i;
        while (r < edges.size() && edges[r].w == edges[i].w) r++;


        for (int j = i; j < r; j++) {
            int arbol1 = bosque.findSet(edges[j].x);
            int arbol2 = bosque.findSet(edges[j].y);
            
                if (arbol1 != arbol2) {
                g[arbol1].push_back({arbol2, edges[j].index});
                g[arbol2].push_back({arbol1, edges[j].index});
                respuesta[edges[j].index] = 1; 
            }
        }
        timer = 0;
        for (int j = i; j < r; j++) {
            int c1 = bosque.findSet(edges[j].x);
            int c2 = bosque.findSet(edges[j].y);
            if (!vis[c1]) dfs(c1, -1);
            if (!vis[c2]) dfs (c2 ,-1);
        }

        for (int j = i; j < r; j++) {
            int c1 = bosque.findSet(edges[j].x);
            int c2 = bosque.findSet(edges[j].y);
            vis[c1] = vis[c2] = false;
            g[c1].clear();
            g[c2].clear();
        }

        
        for (int j = i; j < r; j++) {
            bosque.unionSet(edges[j].x, edges[j].y);
        }

        i = r ;
    }
}

int main() {
    int n, m, w,a,b;
    cin >> n >> m;
    bosque.crearSet(n);

    respuesta.assign(m, 0); 
    edges.resize(m);
    vis.assign(n, false);
    g.resize(n);
    lo_in.resize(n);
    in.resize(n);

    for (int i = 0; i < m; i++) {
        cin >> a >> b >> edges[i].w;
        a --;
        b--;
        edges[i].x = a;
        edges[i].y = b;
        edges[i].index = i;
    }

    sort(edges.begin(), edges.end(), comparaEdges);
    caracterizaEdges();

    for (int i : respuesta) {
        if (i == 0) cout << "none" << "\n";
        else if (i == 1) cout << "at least one" << "\n";
        else if (i == 2) cout << "any" << "\n";
    }

    return 0;
}
