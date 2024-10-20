#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

int nodos, m;
vector<vector<int>> lista_de_ady;
vector<int> niveles;
vector<bool> visitados;
queue<int> cola;

bool existe_arista(vector<int>&vecinos , int v){
    for (int w : vecinos){
        if (w == v){
            return true;
        }
    }
    return false;
}

void BFS(int vortex) {
    int nodoAux;
    niveles[vortex] = 0;
    visitados[vortex] = true;
    cola.push(vortex);

    while (!cola.empty()) {
        nodoAux = cola.front();
        cola.pop();

        for (int v : lista_de_ady[nodoAux]) {
            if (!visitados[v]) {
                visitados[v] = true;
                niveles[v] = niveles[nodoAux] + 1;
                cola.push(v);
                //cout <<  v << " "<< niveles[v];
            }
        }
    }
}

int cuenta_vertices_nuevos (int nodo){
    int res = 0;

    for (int v = 1; v<= nodos; v++) {
            if (!existe_arista(lista_de_ady[nodo],v) && (niveles[nodo] - niveles[v])%2 != 0){
                res ++;
            }
    }
    return res;
}

int main() {
    int v, w;
    cin >> nodos;
    m = nodos - 1;

    lista_de_ady.assign(nodos + 1, vector<int>());
    visitados.assign(nodos + 1, false);
    niveles.assign(nodos + 1, -1);

    int i = 0;
    while (i < m) {
        cin >> v >> w;
        lista_de_ady[v].push_back(w);
        lista_de_ady[w].push_back(v);
        i++;
    }

    BFS(w);

    int contador = 0;
    for (int i = 1; i <= nodos; i++) {

            contador = contador + cuenta_vertices_nuevos(i);
        
    }
    cout << contador/2;   
    return contador;
}
