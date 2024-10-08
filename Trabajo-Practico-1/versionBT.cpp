
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> secuencia;
int N;
int acumulado = 0;
vector<vector<vector<int>>> M;
const int INF = 1e9;

bool esBlanqueable(int i,int blanco){
    return blanco == -1 ||secuencia[i] < secuencia[blanco];
}
bool esBlaqueable(int i, int negro){
    return negro == -1 || secuencia[i] > secuencia[negro];
}
int optimizarBlackWhite(int i, int ultNegro, int ultBlanco){
    cout<< i <<","<< ultNegro << ","<<ultBlanco<<endl;
    if (i == N) return 0;

    int sol1 = INF;
    int sol2 = INF;
    int sol3 = INF;
    
    if(esBlanqueable(i,ultBlanco)){
        sol1= optimizarBlackWhite(i+1,ultNegro,i);
    }
    if (esBlaqueable(i,ultNegro)){
        sol2 = optimizarBlackWhite(i+1,i,ultBlanco);

    } else{
        sol3 = optimizarBlackWhite(i+1,ultNegro,ultBlanco)+1;
    }
    
    acumulado = min(sol1,min(sol2,sol3));
    return acumulado;
}   



int main(){
    cin >> N;
    M =  vector<vector<vector<int>>>(N, vector<vector<int>>(N + 1, vector<int>(N + 1, -1)));
    secuencia = vector<int>(N);
    int i  = 0;

    while (i < N){
        cin >> secuencia[i];
        i ++;
    }
    cout << optimizarBlackWhite(0,-1,-1) << endl;
    return 0;
}