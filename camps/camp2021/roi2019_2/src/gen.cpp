#include <bits/stdc++.h>


using namespace std;

int main() {
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int n = rnd() % 100 + 1;
    int m = rnd() % 100 + 1;
    for (int i = 0; i < n; i++)
        cout << "ab"[rnd() % 2];
    cout << '\n';
    cout << "1 ";
    int l = rnd() % 100 + 1;
    for (int i = 0; i < l; i++)
        cout << "ab"[rnd() % 2];
    cout << '\n';
    for (int i = 1; i < m; i++)
        cout << "2 1 " << (rnd() % 100 + 1) * l << '\n';

}