#include <bits/stdc++.h>

using namespace std;

int main() {
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    const int MAXN = 4;
    const int MAXC = 15;
    int n = rnd() % MAXN + 1;
    int m = rnd() % MAXN + 1;
    cout << n << ' ' << m << ' ' << rnd() % MAXC + 1 << ' ' << rnd() % MAXC + 1 << ' ' << rnd() % MAXC + 1 << '\n';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << "WB"[rnd() % 2];
        cout << '\n';
    }
}