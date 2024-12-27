#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <limits>

using namespace std;

struct Edge {
    int src;
    int dest;
    int w;

    void crearEdge(int origen, int destino, int peso) {
        src = origen;
        dest = destino;
        w = peso;
    }
};

vector<vector<pair<int, int>>> grafo;
vector<Edge> edges;
vector<int> distanciasOrigen; //distancias respectivas de cada uno de los nodos de inicio de dikstra
vector<int> distanciasDestino;
int n, m;

const int INF = numeric_limits<int>::max();

bool relax(const pair<int, int>& vecino, int origen, vector<int>& dist) { // funcion que identifica si en el corte hay una arista de menor peso
    int vecinoNodo = vecino.first;
    int pesoArista = vecino.second;

    if (dist[vecinoNodo] > dist[origen] + pesoArista) {
        dist[vecinoNodo] = dist[origen] + pesoArista;
        return true; 
    }
    return false; 
}

void correrDijkstra(vector<int>& distancias, int fuente) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

    distancias[fuente] = 0;
    minHeap.push({0, fuente}); // se inicia el nodo fuente con peso asociado cero, desde modo es el primero que el algoritmo procesa

    while (!minHeap.empty()) { //mientras queden nodos por procesar, es decir que el algoritmo haya considerado todas las aristas del grafo y haya definido aquellas que de menor peso
        pair<int, int> nodo = minHeap.top(); //el ultimo nodo a la que su distancia es actiualizada por relax no es predecible a priori y dependera del grafo y la fuente de inicio
        minHeap.pop();

        if (nodo.first > distancias[nodo.second]) continue; //si la distancia actual es mayor que la asociada al nodo siendo evaluado, se saltea puesto que no hay nada que por mejorar

        for (const pair<int, int>& vecino : grafo[nodo.second]) { //para todas las aristas exedentes del nodo considero la posibilidad de relajar cada una de ellas
            if (relax(vecino, nodo.second, distancias)) {
                minHeap.push({distancias[vecino.first], vecino.first}); //c++ queue re estructura el minheap al re instertar un elemento con un valor de prioridad modificado
            }
        }
    }
}

int main() {
    cin >> n >> m;
    grafo.resize(n);
    edges.resize(2*m); // se haran dos Dikjstras distintos para definir los caminos minimos entre dos nodos (en ambos sentidos) 
    distanciasOrigen.assign(n, INF);
    distanciasDestino.assign(n, INF);
    Edge e;

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        grafo[a].push_back({b, w});
        grafo[b].push_back({a, w});
        e.crearEdge(a, b, w);
        edges.push_back(e);
        e.crearEdge(b,a,w);
        edges.push_back(e);
    }

    correrDijkstra(distanciasOrigen, 0); // generea un registro de las distancias minimas desde el nodo 0 hasta n-1
    correrDijkstra(distanciasDestino, n - 1); //genera un registro de las distancias minimas del nodo n-1 hasta 0
    //al haber duplicado las aristas y sus sentidos, por mas de generar aristas que no existen en el grafo, me garantiza no perderme de evaluar algun que puede formar parte de 
    // Pmin<0,n-1> oo Pmin<n-1,0>
    int ret = 0;

    for (Edge& e : edges) {
        if (distanciasOrigen[n - 1] == distanciasOrigen[e.src] + e.w + distanciasDestino[e.dest]) { //aquellas que cumplen ser 
            ret += 2 * e.w;
        }
    }

    cout << ret;

    return 0;
}
