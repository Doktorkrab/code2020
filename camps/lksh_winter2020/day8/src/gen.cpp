#include <bits/stdc++.h>

using namespace std;


int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int MAXN = 5;
    int n = rnd() % MAXN + 1;
    int m = rnd() % 5 + 1;
    cout << n << ' ' << m << '\n';
    for (int i = 0; i < n; i++)
        cout << rnd() % m + 1 << " \n"[i + 1 == n];
}