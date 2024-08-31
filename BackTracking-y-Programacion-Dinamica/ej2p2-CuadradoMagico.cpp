#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int sumaF(vector<vector<int>>& matriz, int dimension, int i) {
    int suma = 0;
    for (int k = 0; k < dimension; k++) {
        suma += matriz[i][k];
    }
    return suma;
}

int sumaC(vector<vector<int>>& matriz, int dimension, int j) {
    int suma = 0; 
    for (int k = 0; k < dimension; k++) {
        suma += matriz[k][j];  
    }
    return suma;
}

int sumaDiagonal1(vector<vector<int>>& matriz, int dimension, int i, int j) {
    int suma = 0; 
    while (j >= 0) {
        suma += matriz[i][j];
        j -= 1;
        i += 1;
    }
    return suma;
}

int sumaDiagonal2(vector<vector<int>>& matriz, int dimension, int i, int j) {
    int suma = 0;  
    while (j < dimension) {
        suma += matriz[i][j];
        i += 1;
        j += 1;
    }
    return suma;
}

bool esMagico(vector<vector<int>>& cuadrado, int nMagico, int dimension) {

    for (int i = 0; i < dimension; i++) {
        if (sumaF(cuadrado, dimension, i) != nMagico || sumaC(cuadrado, dimension, i) != nMagico) {
            return false;
        }
    }
    
    if (sumaDiagonal1(cuadrado, dimension, 0, dimension - 1) != nMagico) return false;
    if (sumaDiagonal2(cuadrado, dimension, 0, 0) != nMagico) return false;

    return true;
}

int probarCombinaciones(vector<vector<int>>& matriz, int nMagico, int i, int j, int dimension) {
    int combinacionesValidas = 0;

    if (i == dimension) {
        if (esMagico(matriz, nMagico, dimension)) { 
            return 1;
        }
        return 0; 
    }
    if (j == dimension) {
        return probarCombinaciones(matriz, nMagico, i + 1, 0, dimension);
    }

    for (int val = 1; val <= 9; ++val) {
        matriz[i][j] = val;
        combinacionesValidas += probarCombinaciones(matriz, nMagico, i, j + 1, dimension);
        matriz[i][j] = 0; 
    }
    return combinacionesValidas;  
}
int calcularNMagico (int m){
    return m*(pow(m,2)+1)/2;
}

int main() {
    int dimension;
    cin >> dimension;
    int nMagico = calcularNMagico(dimension);
    vector<vector<int>> matriz(dimension, vector<int>(dimension, 0));

    int totalCombinaciones = probarCombinaciones(matriz, nMagico, 0, 0, dimension);
    cout << "Total de combinaciones mágicas: " << totalCombinaciones << endl;

    return 0;
}
