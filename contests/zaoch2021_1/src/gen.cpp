#include <bits/stdc++.h>

using namespace std;


int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    const int n = 500;
    const int m = 500;
    const int MAXC = 1e6;
    cout << n << ' ' << m << '\n';
    for (int i = 0; i < n; i++)
        cout << rnd() % MAXC + 1 << ' ' << rnd() % MAXC + 1 << '\n';
    for (int i = 0; i < m; i++)
        cout << rnd() % MAXC + 1 << ' ' << rnd() % MAXC + 1 << " " << n << '\n';
}