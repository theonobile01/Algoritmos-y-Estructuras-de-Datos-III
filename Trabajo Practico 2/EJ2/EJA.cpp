#include <vector>
#include <iostream>
#include <utility>


using namespace std;


class DisjointSet {

    public:

    vector <long> padres;
    vector <long> rangos;



    void crearSet(long n){
        padres.resize(n);
        rangos.resize(n,0);

        for (long i =0 ;  i< n; i++ ){
            
            padres[i] = i; // cada elemento en primera instancia es su propia componentes conexa y por lo tanto referencia a si mismo
        }
    }

    long findSet (long elemento){

        if (padres[elemento] != elemento){
            padres[elemento] = findSet(padres[elemento]);
        }

        return padres[elemento];
    }

    void unionSet(long x, long y) {
            long raizX = findSet(x);
            long raizY = findSet(y);

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

    long getRango(long x){
        return rangos[findSet(x)];
    }

    long getRepresentante (long x){
        return findSet(x);
    }
};

long N, M, U[100000], V[100000], W[100000], C[100000], respuesta[100000];
vector<long> gruposPeso[1000001];
vector<pair<long, long>> g[100000];
bool visitados[100000];
long in[100000], lo_in[100000], timer;
DisjointSet bosque;



void dfs(long v, long p){
	visitados[v] = 1;
	in[v] = lo_in[v] = timer++;
	for(pair<long, long> i : g[v]){
		long c = i.first, id = i.second;
		if(id == p) continue;
		if(visitados[c]){
			lo_in[v] = min(lo_in[v], in[c]);
			if(lo_in[c] > in[v]){
				respuesta[id] = 2;
			}
			continue;
		}
		dfs(c, id);
		lo_in[v] = min(lo_in[v], lo_in[c]);
		if(lo_in[c] > in[v]){
			respuesta[id] = 2;
		}
	}
}
void caracterizarEdges(){
    for (long i = 0; i <= 1000000; i++){

        if(!gruposPeso[i].size()){
            continue;
        }
        for (long j : gruposPeso[i]){
            long c1 = bosque.findSet(U[j]);
            long c2 = bosque.findSet(V[j]);

            if (c1 != c2){
                g[c1].push_back({c2,j});
                g[c2].push_back({c1,j});
                respuesta[j] = 1;
            }
        }
        timer = 0;
        for (long j : gruposPeso[i]){
            long c1 = bosque.findSet(U[j]);
            long c2 = bosque.findSet(V[j]);

            if(visitados[c1] || visitados[c2]) continue;

                dfs(c1,-1);
                dfs(c2,-1);
        }

        for (long j : gruposPeso[i]){
            long c1 = bosque.findSet(U[j]);
            long c2 = bosque.findSet(V[j]);

            g[c1].clear();
            g[c2].clear();
            visitados[c1] = 0;
            visitados[c2] = 0;
        }
        for (long j : gruposPeso[i]){
            bosque.unionSet(U[j],V[j]);
        }   
    }
}

    int main(){
	cin >> N >> M;
	for(long i = 0; i < M; i++){
		cin >> U[i] >> V[i] >> W[i];
		U[i]--, V[i]--;
		gruposPeso[W[i]].push_back(i);
	}
	bosque.crearSet(N);

    caracterizarEdges();

	for(long i = 0; i < M; i++){
		if(respuesta[i] == 0) cout << "none" << "\n";
		if(respuesta[i] == 1) cout << "at least one"<<"\n";
		if(respuesta[i] == 2) cout << "any"<<"\n";
	}
    return (long)0;
}
