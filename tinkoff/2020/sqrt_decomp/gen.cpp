#include <bits/stdc++.h>

using namespace std;

int main() {
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    const int MAXN = 2e5;
    const int MAXC = 1e9;
    int n = rnd() % MAXN + 1;
    cout << n << '\n';
    for (int i = 0; i < n; i++)
        cout << rnd() % MAXC + 1 << " \n"[i + 1 == n];
    int q = rnd() % MAXN + 1;
    cout << q << '\n';
    for (int i = 0; i < q; i++) {
        int type = rnd() % 2 + 1;
        cout << type << ' ';
        if (type == 2) {
            int l = rnd() % n + 1;
            int r = rnd() % n + 1;
            if (l > r)
                swap(l, r);
            cout << rnd() % MAXC + 1 << ' ' << l << ' ' << r << '\n';
        } else
            cout << rnd() % n + 1 << ' ' << rnd() % MAXC + 1 << '\n';
    }
}
