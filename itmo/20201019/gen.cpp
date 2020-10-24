#include <bits/stdc++.h>

using namespace std;


int main() {
    const int MAXN = 4;
    const int MAXC = 5;
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int n = rnd() % MAXN + 2, m = rnd() % MAXN + 1;
    cout << n << ' ' << m << ' ' << '\n';
    for (int i = 0; i < n; i++)
        cout << rnd() % MAXC + 1 << " \n"[i + 1 == n];
    for (int i = 0; i < m; i++) {
        int type = rnd() % 2 + 1;
        cout << type << " ";
        if (type == 1) {
            int l = rnd() % n;
            int r = rnd() % n;
            while (l == r)
                r = rnd() % n;
            cout << l + 1 << ' ' << r + 1 << '\n';
        } else {
            int l = rnd() % n;
            int r = rnd() % n;
            if (l > r)
                swap(l, r);
            cout << l + 1 << ' ' << r + 1 << ' ' << ((int) rnd() % (2 * MAXC)) - MAXC << '\n';
        }
    }
}