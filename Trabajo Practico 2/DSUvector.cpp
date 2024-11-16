#include <vector>

using namespace std;


class DisjointSet {

    public:

    vector <int> padres;
    vector <int> rangos;



    void crearSet(int n){
        padres.resize(n+1);
        rangos.resize(n+1,0);

        for (int i =1 ;  i<= n; i++ ){
            
            padres[i] = i; // cada elemento en primera instancia es su propia componentes conexa y por lo tanto referencia a si mismo
        }
    }

    int findSet (int elemento){

        if (padres[elemento] != elemento){
            padres[elemento] = findSet(padres[elemento]);
        }

        return padres[elemento];
    }

    void unionSet(int x, int y) {
            int raizX = findSet(x);
            int raizY = findSet(y);

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

    int getRango(int x){
        return rangos[findSet(x)];
    }

    int getRepresentante (int x){
        return findSet(x);
    }
};