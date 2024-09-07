
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> secuencia;
int N;
int acumulado = 0;
vector<vector<vector<int>>> M;
const int INF = 1e9;

bool esBlanco(int i,int blanco){
    return blanco == N ||secuencia[i] < secuencia[blanco];
}
bool esNegro(int i, int negro){
    return negro == N || secuencia[i] > secuencia[negro];
}
int optimizarBlackWhite(int i, int ultNegro, int ultBlanco){

    if (i == N) return 0;

    if (ultNegro == -1) ultNegro = N;
    if (ultBlanco == -1) ultBlanco = N;

    if(M[i][ultNegro][ultBlanco] != -1) return M[i][ultNegro][ultBlanco];

    int sol1 = INF;
    int sol2 = INF;
    int sol3 = INF;
    
    if(esBlanco(i,ultBlanco)){
        sol1 = optimizarBlackWhite(i+1,ultNegro,i);
    }
    if (esNegro(i,ultNegro)){
        sol2 = optimizarBlackWhite(i+1,i,ultBlanco);
    }
        sol3 = optimizarBlackWhite(i+1,ultNegro,ultBlanco)+1;

        M[i][ultNegro][ultBlanco] = min(sol1,min(sol2,sol3));

    return M[i][ultNegro][ultBlanco];
}   



int main(){

    while (true){
        if (cin >> N){
            if (N == -1) break;
        M =  vector<vector<vector<int>>>(N, vector<vector<int>>(N + 1, vector<int>(N + 1, -1)));
        secuencia = vector<int>(N);
        int i  = 0;
            
        while (i < N){
            cin >> secuencia[i];
            i ++;
        }
            
        cout << optimizarBlackWhite(0,-1,-1) << endl;
        }

    }
    return 0;
}