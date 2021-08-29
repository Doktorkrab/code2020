#include <bits/stdc++.h>

using namespace std;

int main() {
//    mt19937 rnd(4);
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int n = rnd() % 5 + 1;
    cout << n << '\n';
    for (int i = 0; i < n; i++)
        cout << rnd() % 2 << " \n"[i + 1 == n];
    for (int i = 1; i < n; i++)
        cout << i + 1 << ' ' << rnd() % i + 1 << '\n';
    int m = rnd() % 5 + 1;
    cout << m << '\n';
    for (int i = 0; i < m; i++)
        cout << rnd() % n + 1 << ' ' << rnd() % n + 1 << " " << rnd() % 2 << '\n';
}