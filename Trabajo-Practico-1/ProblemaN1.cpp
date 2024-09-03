#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<vector<vector<int>>> M;
vector<int>secuencia;
int N;

int coloreoRecursivo(int i, int uNegro, int uBlanco){
    int espacios_vacios = 0;

    if ((uNegro != -1 && uBlanco != -1) && M[i][uNegro][uBlanco] != -1){
        return M[i][uNegro][uBlanco];
    }
    if (i == N){
        return 0;
    }
    if(uNegro == -1 && uBlanco == -1 && M[i][N][N] != -1){
        espacios_vacios = min(coloreoRecursivo(i+1, i, uBlanco), coloreoRecursivo(i+1, uNegro, uBlanco)+1);
        M[i][N][N] = espacios_vacios;
    }
    //Tendria que hacer una correcion de indices?
    if (secuencia[i] < secuencia[uNegro]){
        espacios_vacios = min(coloreoRecursivo(i+1, i, uBlanco), coloreoRecursivo(i+1, uNegro, uBlanco)+1);
        M[i][uNegro][uBlanco] = espacios_vacios;
    }
    if ( secuencia[i] > secuencia[uNegro]){
        espacios_vacios = min(coloreoRecursivo(i+1, uNegro, i), coloreoRecursivo(i+1, uNegro, uBlanco)+1);
        M[i][uNegro][uBlanco] = espacios_vacios;
    }
    else{
        espacios_vacios = coloreoRecursivo(i+1, uNegro, uBlanco) +1;
        M[i][uNegro][uBlanco] = espacios_vacios;
    }
    

    return espacios_vacios;
}


int main(){

    cin >> N;
    M = vector<vector<vector<int>>>(N+1,vector<vector<int>>(N+1, vector<int>(N+1, -1)));
    secuencia = vector<int>(N);
    for (int i = 0; i < N; i++){
        cin >> secuencia[i];
    }

    cout << coloreoRecursivo(0,-1,-1)<< endl;

    return 0;
}