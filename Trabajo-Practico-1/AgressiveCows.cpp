#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


bool entran_cada_x(int vacas,int distMin,vector<int>&posiciones){
    int i = 1;
    int cantVacas = 1;
    int ultPosicion = posiciones[0];

    while (i < posiciones.size()){
        if(posiciones[i] - ultPosicion >= distMin){
            cantVacas ++;
            ultPosicion = posiciones[i];
        }
        if (cantVacas == vacas){
            return true;
        }
        i++;
    }   
    return cantVacas >= vacas;
}

int espacio_minimo_maximo(int c,vector<int>&posiciones){
    int low = 1;
    int high = posiciones.back() - posiciones[0];
    int solParcial = 0;

    while (low <= high){
        int mid =low + (high - low )/ 2;
        
        if (entran_cada_x(c,mid,posiciones)){
            solParcial = mid;
            low = mid + 1;

        }else{
            high = mid - 1;
        }
    }
    return solParcial;
}

int main() {
    int casos, vacas, espacio;
    
    if (cin >> casos){
            
    for (int i = 0; i < casos; i++) {
        cin >> espacio >> vacas;
        vector<int> posiciones(espacio);

        for (int j = 0; j < espacio; j++) {
            cin >> posiciones[j];
        }

        sort(posiciones.begin(), posiciones.end());

        cout << espacio_minimo_maximo(vacas, posiciones) << endl;
    }

    }

    return 0;
}