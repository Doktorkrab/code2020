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

int n, m, s;
const int MAXN = 505;
bool tree[MAXN][MAXN];
int rows[MAXN][2 * MAXN];
int col[2 * MAXN];

int solve() {
    if (!(cin >> n >> m >> s))
        return 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            char x;
            cin >> x;
            tree[i][j] = (x == '#');
        }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int tmp = 0;
            for (int k = i; k < n; k++) {
                tmp += 1 + tree[k][j];
//                cout << "vert " << k << ' ' << j << ' ' << tmp << '\n';
                rows[j][tmp]++;
            }

            tmp = 0;
            for (int k = j; k < m; k++) {
                tmp += 1 + tree[i][k];
//                cout << "hori " << i << ' ' << k << ' ' << tmp << '\n';
                col[tmp]++;
            }
            int sum = 0;
            int pnt = 2 * n;
            for (int k = 0; k <= 2 * n; k++)
                sum += rows[j][k];
            for (int k = 1; k <= 2 * m; k++){
                while (pnt > 0 && pnt - (1 + tree[i][j]) + k > s){
                    sum -= rows[j][pnt];
                    pnt--;
                }
//                cout << i << ' ' << j << ' ' << k << ' ' << pnt << ' ' << col[k] << ' ' << sum << '\n';
                ans += col[k] * sum;
            }
            tmp = 0;
            for (int k = i; k >= 0; k--) {
                tmp += 1 + tree[k][j];
                rows[j][tmp]--;
            }
            tmp = 0;
            for (int k = j; k >= 0; k--){
                tmp += 1 + tree[i][k];
                col[tmp]--;
            }
        }
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
