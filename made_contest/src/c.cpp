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

int n, m;
const int MAXN = 2e3 + 7;
bool arr[MAXN][MAXN];
int up[MAXN][MAXN], down[MAXN][MAXN], lft[MAXN][MAXN], rgt[MAXN][MAXN];

int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            char x;
            cin >> x;
            arr[i][j] = (x == '.');
        }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int prev = 0;
            if (j != 0)
                prev = lft[i][j - 1];
            if (arr[i][j])
                lft[i][j] = 1 + prev;
            else
                lft[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = m - 1; j >= 0; j--) {
            int prev = 0;
            if (j != m - 1)
                prev = rgt[i][j + 1];
            if (arr[i][j])
                rgt[i][j] = prev + 1;
            else
                rgt[i][j] = 0;
        }
    }

    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            int prev = 0;
            if (i != 0)
                prev = up[i - 1][j];
            if (arr[i][j])
                up[i][j] = prev + 1;
            else
                up[i][j] = 0;
        }
    }
    for (int j = 0; j < m; j++){
        for (int i = n - 1; i >= 0; i--){
            int prev = 0;
            if (i != n - 1)
                prev = down[i + 1][j];
            if (arr[i][j])
                down[i][j] = prev + 1;
            else
                down[i][j] = 0;
        }
    }
    int best = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (arr[i][j])
                best = max(best, up[i][j] + down[i][j] + lft[i][j] + rgt[i][j] - 3);
    cout << best << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
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
