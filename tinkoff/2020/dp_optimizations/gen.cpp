#include <bits/stdc++.h>

using namespace std;

int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    const int MAXN = 3;
    const int MAXC = 20;
    int n = rnd() % MAXN + 1;
    int k = rnd() % n + 1;
    cout << n << ' ' << k << '\n';
    for (int i = 0; i < n; i++)
        cout << rnd() % MAXC << " \n"[i + 1 == n];
}