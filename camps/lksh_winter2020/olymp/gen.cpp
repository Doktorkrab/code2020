#include <bits/stdc++.h>

using namespace std;


int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int MAXT = 1;
    int t = rnd() % MAXT + 1;
    cout << t << '\n';
    for (int i = 0; i < t; i++) {
        cout << '\n';
        const int MAXN = 4;
        const int MAXM = 7;
        int n = rnd() % MAXN + 2;
        int m = rnd() % MAXM;
        cout << n << ' ' << m << '\n';
        for (int i = 0; i < m; i++)
            cout << rnd() % n + 1 << ' ' << rnd() % n + 1 << '\n';
    }
}