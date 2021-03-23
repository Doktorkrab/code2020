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
 
int n, q;
const int MAXN = 4e3 + 7;
const int INF = 1e9;
const int MAXK = 805;
int arr[MAXN][MAXN];
int prefix[MAXN][MAXN];
int dp[MAXK][MAXN];
int opt[MAXK][MAXN];
int get(int j, int i){
    return prefix[j][j] - prefix[j][i] - prefix[i][j] + prefix[i][i];
}

void rec(int level, int tl, int tr, int min_o, int max_o){
    if (tr < tl)
        return;
    int tm = (tl + tr) / 2;
    dp[level][tm] = INF;
    for (int x = min_o; x <= min(tm - 1, max_o); x++){
        int now = dp[level - 1][x] + get(x + 1, tm + 1);
        if (dp[level][tm] > now){
            dp[level][tm] = now;
            opt[level][tm] = x;
        }
    }
    rec(level, tl, tm - 1, min_o, opt[level][tm]);
    rec(level, tm + 1, tr, opt[level][tm], max_o);
}

int solve() {
    if (!(cin >> n >> q))
        return 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> arr[i][j];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
            prefix[i + 1][j + 1] = prefix[i + 1][j] + prefix[i][j + 1] - prefix[i][j] + arr[i][j];
    }
    for (int i = 0; i < n; i++)
        dp[1][i] = get(0, i + 1);

    for (int k = 2; k <= q; k++)
        rec(k, 0, n - 1, 0, n - 1);
    cout << dp[q][n - 1] / 2 << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("f.in", "r", stdin);
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
