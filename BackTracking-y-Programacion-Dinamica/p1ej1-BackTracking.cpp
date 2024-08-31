#include <iostream>
#include <vector>

using namespace std;



bool res = false;
vector<vector<int>> subConjuntos;
vector<int> indices;

void subSetSum(vector<int>&conj,int cardinal,int sumatoria){

    if (sumatoria < 0){  //Esta condicion evalua la factibilidad de la solucion parcial a considerar. Si la suma de los elementos ya exede la sumatoria se 
                        // Se corta la rama de la recusion.
        cout <<"no cumple"<< endl;
        return;
    }
    if (cardinal == 0 && sumatoria == 0){
        subConjuntos.push_back(indices);
        res = true;
        return;
    }
    else if (cardinal == 0 && sumatoria > 0){
        return;
    }
    indices[cardinal-1]=0; // en esta recursion se explora la rama que no resta el iesimo elemento de s
    subSetSum(conj,cardinal-1,sumatoria);
    indices[cardinal-1] = 1;
    subSetSum(conj,cardinal-1,sumatoria-conj[cardinal-1]); //en esta recursion se explora la rama que si resta el iesimo elemento de s;


    return;
}

int main(){
    int n, k;
    cout << "Ingresa la cantidad de elementos del conjunto: ";
    cin>>n;
    cout << "Ingresa k: ";
    cin >>k;
    vector<int>s(n);
    indices = vector<int>(n);
    
    for (int i = 0; i < n; i++){
        cout << "Ingrese el siguiente numero del conjunto"<< endl;
        cin >> s[i];
    }
    subSetSum(s,n,k);
    if (res == true){
        cout << "Los datos de entrada cumplen con la condicion del problema"<<endl;
        cout << "Los subConjuntos que cumplen son los siguientes: ";
    }else{
        cout << "No se cumplen las condiciones aclaradas por el problema";
        
    }
    for (int i = 0; i < subConjuntos.size(); i++) {
    cout << '{';
    for (int j = 0; j < subConjuntos[i].size(); j++) {
        cout << subConjuntos[i][j] * s[j];
        if (j < subConjuntos[i].size() - 1) {
            cout << ", ";
        }
    }
    cout << '}' << endl;
    }
    return 0;
}