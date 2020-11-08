#include <bits/stdc++.h>

using namespace std;


int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    const int MAXC = 2e5;
    const int MAXN = 2e5;
    int n = rnd() % MAXN + 1;
    int m = rnd() % MAXN + 1;
    cout << n << ' ' << m << '\n';
    for (int i = 0; i < n; i++)
        cout << rnd() % MAXC + 1 << " \n"[i + 1 == n];
    for (int i = 0; i < m; i++){
        int var = rnd() % 4;
        if (var == 3)
            cout << "t\n";
        else
            cout << "arc"[var] << ' ' << rnd() % MAXC + 1 << '\n';
    }
}