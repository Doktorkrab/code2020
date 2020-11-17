#include <bits/stdc++.h>

using namespace std;


int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    const int MAXC = 1e9;
    const int MAXN = 5e4;
    const int MAXD = 50;
    int n = 5e4;
    int d = rnd() % MAXD + 1;
    cout << n << ' ' << d << '\n';
    for (int i = 0; i < n; i++)
        for (int j = 0; j < 3; j++)
            cout << rnd() % MAXC + 1 << " \n"[j == 2];
    int m = 1;
    cout << m << '\n';
    for (int i = 0; i < m; i++){
        int l = rnd() % n + 1;
        int r = rnd() % n + 1;
        if (l >= r)
            swap(l, r);
        cout << l << ' ' << r << '\n';
    }
}