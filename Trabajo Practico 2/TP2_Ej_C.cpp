#include <vector>
#include <queue>
#include <iostream>
#include <climits>

using namespace std;

void BFS_Adaptado(vector<int>& costoMin, const vector<int>& atajos) {
    int n = atajos.size() - 1;
    int aula = 1;
    queue<int> q;
    q.push(aula); 
    costoMin[aula] = 0;


    while (!q.empty()) {
        aula = q.front();
        q.pop();


        if (aula - 1 >= 1 && costoMin[aula - 1] > costoMin[aula] + 1) {
            costoMin[aula - 1] = costoMin[aula] + 1;
            q.push(aula - 1);
        }


        if (aula + 1 <= n && costoMin[aula + 1] > costoMin[aula] + 1) {
            costoMin[aula + 1] = costoMin[aula] + 1;
            q.push(aula + 1);
        }


        if (atajos[aula] != aula && costoMin[atajos[aula]] > costoMin[aula] + 1) {
            costoMin[atajos[aula]] = costoMin[aula] + 1;
            q.push(atajos[aula]);
        }
    }
}

int main() {
    int n,i;
    cin >> n;

    vector<int> atajos(n + 1); 
    vector<int> costoMin(n + 1, INT_MAX);  

    i = 1;
    while (i <= n){
        cin >> atajos[i];
        i ++;
    }
    BFS_Adaptado(costoMin, atajos);
    i = 1;
    while (i <= n){
        cout << costoMin[i] << " ";
        i ++;

    }
    cout << endl;

    return 0;
}
