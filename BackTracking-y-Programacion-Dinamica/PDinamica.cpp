#include <iostream>
#include <vector>

using namespace std;

// Fibonacci P. Dinamica
// Enfoque Top Down:

int fiboTP (int n , vector<int>&terminos){
    if (n == 0){
        return 0;
    }
    if (n == 1){
        return 1;
    }
    if (terminos[n] > 0){
        return terminos[n];
    }
    terminos[n] = fiboTP(n-1, terminos) + fiboTP(n-2,terminos);

    return terminos[n];
}

//Version Bottom - Up:

int fiboBU (int t){
    vector<int> terminos(t+1);

    if (t == 0){
        return 0;
    }
    if (t <=2){
        return 1;
    }
    terminos[0] = 0;
    terminos [1] =  1;
    
    for (int i = 2; i<=t ; i++){
        terminos[i] = terminos[i-1] + terminos[i-2];
    }
    return terminos [t];

}

int main(){
    int n,x;

    cout << "Termino de la sucesion a calcular"<< endl;
    cin >> n;
    vector<int> sol(n+1);

    cout << fiboTP (n, sol) << endl;
        
    cout << fiboBU (n) << endl;

    return 1;
}