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
 
int n, C;
const int MAXN = 1005;
bool dp[25][MAXN][MAXN];
char par[25][MAXN][MAXN];
int kek[MAXN];
int solve() {
    if (!(cin >> n >> C))
        return 1;
    for (int i = 0; i <= 0; i++){
        for (int j = 0; j <= 0; j++)
            dp[0][i][j] = true;
    }
    for (int i = 0; i < n - 2; i++){
        int x;
        cin >> x;
        kek[i] = x;
        for (int a = 0; a <= 1000; a++){
            for (int b = a; b <= a + x; b++){
                int c = a + x;
                if (a + x >= MAXN)
                    continue;
                bool was = false;
                if (dp[i][a][b]) {
                    dp[i + 1][b][c] = true;
                    par[i + 1][b][c] = a;
                    was = true;
                }

                if (dp[i][b][a]) {
                    dp[i + 1][a][c] = true;
                    par[i + 1][a][c] = b;
                    was = true;
                }

                if (dp[i][c][b]) {
                    dp[i + 1][b][a] = true;
                    par[i + 1][b][a] = c;
                    was = true;
                }

                if (dp[i][b][c]) {
                    dp[i + 1][c][a] = true;
                    par[i + 1][c][a] = b;
                    was = true;
                }

                if (dp[i][a][c]) {
                    dp[i + 1][c][b] = true;
                    par[i + 1][c][b] = a;
                    was = true;
                }

                if (dp[i][c][a]) {
                    dp[i + 1][a][b] = true;
                    par[i + 1][a][b] = c;
                    was = true;
                }
                if (was){
//                    cout << i + 1 << ' ' << a << ' ' << b << ' ' << c << '\n';
                }
            }
        }
    }
    int a, b;
    for (a = 0; a <= 1000; a++) {
        for (b = 0; b <= 1000; b++) {
//            cout << a << ' ' << b << ' ' << dp[n - 2][a][b] << '\n';
            if (dp[n - 2][a][b]) {
                break;
            }
        }
        if (dp[n - 2][a][b])
            break;
    }
    if (!dp[n - 2][a][b]){
        cout << "No\n";
        return 0;
    }
    cout << "Yes\n";
    int pos = n - 2;
    vector<int> ans;
    while (pos > 0){
        ans.push_back(b);
//        cout << (int)par[pos][a][b] << a << ' ' << b << '\n';
//        cout << dp[pos][a][b] << '\n';
        int c = a;
        a = par[pos][a][b];
        b = c;
        --pos;
    }
    ans.push_back(b);
    ans.push_back(a);
    reverse(ALL(ans));

    for (int i = 0; i + 2 < n; i++){
        int lol = max(ans[i], max(ans[i + 1], ans[i + 2]));
        int keke = min(ans[i], min(ans[i + 1], ans[i + 2]));
        if (lol - keke != kek[i])
            assert(0);
    }
    for (int x : ans)
        cout << x << ' ';
    cout << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("otvinta.in", "r", stdin);
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
