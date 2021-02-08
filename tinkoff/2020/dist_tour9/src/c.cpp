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
const int MAXN = 1e3 + 7;
string s, t;
int dp[MAXN];
int p[105][MAXN];
int solve() {
    if (!(cin >> s >> t))
        return 1;
    n = SZ(s);
    m = SZ(t);
    sort(ALL(t));
    for (int i = m - 1; i >= 0; i--){
        int cur_max = 0;
        int where = -1;
        for (int j = n - 1; j >= 0; j--){
            int tt = dp[j];
            if (t[i] == s[j]) {
                cout << t[i] << ' ' << j << ' ' << where << ' ' << cur_max + 1 << '\n';
                dp[j] = max(cur_max + 1, dp[j]);
                p[i][j] = where;
            }
            if (tt == cur_max && cur_max != 0 && s[where] > s[j])
                where = j;
            if (tt > cur_max){
                where = j;
                cur_max = tt;
            }
        }
        cout << '\n';
    }
    int x = -1;
    for (int i = 0; i < n; i++){
        if (dp[i] == m && (x == -1 || s[x] > s[i]))
            x = i;
    }
    if (x == -1){
        cout << "impossible\n";
        return 0;
    }
    string ans;
    int j = 0;
    while (j < m){
        cerr << x << ' ' << j << '\n';
        ans += s[x];
        x = p[j++][x];
    }
//    reverse(ALL(ans));
    cout << ans << '\n';
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
