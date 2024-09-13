#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int t, n;

    if (cin >> t) {
        for (int i = 1; i <= t; i++) {
            cin >> n;
            vector<pair<int, int>> intervalos(n);

            for (int k = 0; k < n; k++) {
                cin >> intervalos[k].first >> intervalos[k].second;
            }

            sort(intervalos.begin(), intervalos.begin() + n, [](pair<int, int> a, pair<int, int> b) {
                return a.second <  b.second;
            });

            int c = 0;
            int extremoSuperior = -1;

            for (int j = 0; j < n; j++) {

                if (intervalos[j].first >= extremoSuperior) {
                    extremoSuperior = intervalos[j].second;
                    intervalos[j] = {-1,-1};
                    c++;

                }else{
                    intervalos[j] = {-1,-1};
                }
            }
            cout << c << endl;
        }
    }

    return 0;
}
