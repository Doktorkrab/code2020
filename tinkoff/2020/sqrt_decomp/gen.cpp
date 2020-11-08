#include <bits/stdc++.h>

using namespace std;

int main() {
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    const int MAXN = 7;
    const int MAXC = 1e9;
    int t = rnd() % 5 + 1;
    cout << t << '\n';
    while (t--) {
        int n = rnd() % MAXN + 1;
        int m = rnd() % MAXN + 1;

        cout << n << ' ' << m << '\n';
        for (int i = 0; i < n; i++) {
            vector<int> perm(m);
            iota(perm.begin(), perm.end(), 1);
            shuffle(perm.begin(), perm.end(), rnd);
            for (int j = 0; j < m; j++)
                cout << perm[j] << " \n"[j + 1 == m];
        }
        int q = rnd() % MAXN + 1;
        cout << q << '\n';
        for (int i = 0; i < q; i++) {
            int l = rnd() % n + 1;
            int r = rnd() % n + 1;
            if (l > r)
                swap(l, r);
            cout << l << ' ' << r << '\n';
        }
    }
}
