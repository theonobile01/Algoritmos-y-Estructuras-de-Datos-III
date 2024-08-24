#include <iostream>
#include <vector>

using namespace std;
//Dado un multiconjunto C = {c1 , . . . , cn } de números naturales y un natural k , queremos
//determinar si existe un subconjunto de C cuya sumatoria sea k . Vamos a suponer fuertemente
//que C está ordenado de alguna forma arbitraria pero conocida (i.e., C está implementado como
//la secuencia c1 ,

bool res = false;
vector<vector<int>> subConjuntos;
vector<int> indices;

void subSetSum(vector<int>&conj,int cardinal,int sumatoria){
    if (cardinal == 0 && sumatoria == 0){
        subConjuntos.push_back(indices);
        res = true;
        return;
    }
    else if (cardinal == 0 && sumatoria != 0){
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

// OUTPUT: Dada un INPUT de la forma subSetSum({1,2,3};3) ---subSetSum----> true: y los subconjuntos que lo cumplen; {1,2,0} , {0,0,3}; 

//COMPLEJIDAD: Cada aplicacion del metodo size tendra una complejidad de O(#S) = O(#S)
            // Los for loops cumplen con la misma cota superior #S
            // Por ultimo la funcion recursiva explora todo el espacio combinatorio de S. lo cual es igual a (2^#S+1)
//Lo cual llega a una complejidad en terminos asintoticos de O(2^n)