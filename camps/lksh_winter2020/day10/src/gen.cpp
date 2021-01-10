#include <bits/stdc++.h>

using namespace std;

int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int n = rnd() % 499 + 2;
    int m = rnd() % 10000 + 1;
    cout << n << ' ' << m << '\n';
    for (int i = 0; i < m; i++)
        cout << rnd() % n + 1 << ' ' << rnd() % n + 1 << ' ' << rnd() % 10 << '\n';
}