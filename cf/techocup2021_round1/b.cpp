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
const int MAXN = 505;
int rows[MAXN * MAXN];
int col[MAXN * MAXN];
int ans[MAXN][MAXN];
 
int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++) {
            int x;
            cin >> x;
            col[x] = j;
        }
    }
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            int x;
            cin >> x;
            rows[x] = j;
        }
    }
    for (int i = 1; i <= n* m; i++)
        ans[rows[i]][col[i]] = i;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cout << ans[i][j] << " \n"[j + 1 == m];
    return 0;
}
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}
