#include <vector>
#include <queue>
#include <iostream>

using namespace std;

vector<vector<int>> grafo;
vector<bool> visitados;
vector<int> niveles;
long long par, impar = 0;

void BFS(int vortex) {
    int nodoAux;
    queue<int> cola;
    niveles[vortex] = 0;
    visitados[vortex] = true;
    par ++; // vortex.nivel = 0 y 0mod2 == 0
    cola.push(vortex); //la travesia inicia desde vortex


    while (!cola.empty()) {
        nodoAux = cola.front(); // en la primer iteracion nodoAux == vortex
        cola.pop(); //elimino vortex de la cola

        for (int vecino : grafo[nodoAux]) { // exploro toda la vecindad de (en caso de primer iteracion) vortex

            if (!visitados[vecino]) { //en caso de no estar visitado (es decir que no pertenezca al sub arbol T_i) sumo la arista
                visitados[vecino] = true; // el nodo ahora pertence al arbol siendo generado (T_i) y en particular a la frontera
                niveles[vecino] = 1 + niveles[nodoAux]; //se incrementa el "nivel" en el contexto del arbol T_i y la distancia a vortex en el contexto de G

                if (niveles[vecino] % 2 == 1) { //se contabilizan los elementos de la biparticion. si existe (x,y) perteneciente a T ==> x e y pertencen a dos biparticiones distintas
                    impar++;                    // y la paridad de sus niveles sera distinta tambien.

                }
                else {
                    par++;

                }
                cola.push(vecino); //se agrega el nodo a la cola para proximamente explorar su vecindad
            }
        }
    }
}

int main() {
    long long nodos;
    long long v, w;
    cin >> nodos;

    grafo.assign(nodos + 1, vector<int>()); //n+1 puesto que los se indexan por numero y nodo e [1,n]
    visitados.assign(nodos + 1, false);
    niveles.assign(nodos + 1, -1);


    for (int i = 0; i < nodos - 1; i++) {
        cin >> v >> w;
        grafo[v].push_back(w);
        grafo[w].push_back(v);
    }
    BFS(w);
    cout << (par * impar )- (nodos - 1); // Observar que par * impar seria la cantidad de aristas si no fuera validad la biparticion
    return 0;                            // a esta cifra se le debera restar todas las aristas comformables dentro de cada conjunto (invalidas)
}