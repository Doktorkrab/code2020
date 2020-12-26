#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5;
const int MAXQ = 5;
int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int h = rnd() % MAXN + 1;
    int w = rnd() % MAXN + 1;
    int n = rnd() % MAXQ + 1;
    cout << h << ' ' << w << ' ' << n << '\n';
    for (int i = 0; i < n; i++)
        cout << "crf"[rnd() % 3];
    cout << '\n';
    for (int iter = 0; iter < 2; iter++) {
        cout << n << ' ';
        for (int i = 0; i < n; i++)
            cout << rnd() % h << " \n"[i + 1 == n];
        cout << n << ' ';
        for (int i = 0; i < n; i++)
            cout << rnd() % w << " \n"[i + 1 == n];
    }
}