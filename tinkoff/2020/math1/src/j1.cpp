#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;


#define SZ(x) (int)((x).size())
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()

#define TMAX(type) numeric_limits<type>::max()
#define TMIN(type) numeric_limits<type>::min()
#ifdef LOCAL
#define ass(X) assert(X)
#else
#define ass(X) {}
#endif

int n;
const int MAXN = 305;
bitset<MAXN> matrix[MAXN];

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j < n; j++) {
            char x;
            cin >> x;
            matrix[i][j] = (x == '1');
        }
    int cnt = 0;
    int ans_mask = -1;
    for (int mask = 0; mask < (1 << n); mask++) {
        bitset<MAXN> now;
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1)
                now ^= matrix[i];
        if (now == matrix[n]) {
            cnt++;
            ans_mask = mask;
        }
    }
    if (cnt == 0) {
        cout << "No solution\n";
    } else if (cnt > 1 || matrix[n].none()) {
        cout << "Multiple solutions\n";
    } else if (cnt == 1) {
        for (int i = 0; i < n; i++)
            if ((ans_mask >> i) & 1)
                cout << i << ' ';
        cout << '\n';
    }

    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("j.in", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
//    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}
