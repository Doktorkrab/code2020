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

int n, m, w, b, g;
const int MAXN = 4;
int fld[MAXN][MAXN];
int fld1[MAXN][MAXN];

int kek() {
    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (i > 0) {
                ans += g * (fld1[i][j] ^ fld1[i - 1][j]);
            }
            if (j > 0) {
                ans += g * (fld1[i][j] ^ fld1[i][j - 1]);
            }
        }
    return ans;
}

int solve() {
    if (!(cin >> n >> m >> w >> b >> g))
        return 1;
    assert(n <= 4 && m <= 4);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            char x;
            cin >> x;
            fld1[i][j] = fld[i][j] = (x == 'W');
        }
    int ans = TMAX(int);
    for (int mask = 0; mask < (1 << (n * m)); mask++) {
        int cur = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                fld1[i][j] = ((mask >> (i * m + j)) & 1);
                if (fld[i][j] ^ fld1[i][j])
                    cur += fld[i][j] * b + (1 - fld[i][j]) * w;
            }
        ans = min(ans, cur + kek());
    }
    cout << ans << '\n';
    return 0;
}

signed main() {
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
