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

const int MAXN = 505;
int n, m, s;
bool can[MAXN][MAXN];
 
int solve() {
    if (!(cin >> n >> m >> s))
        return 1;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            char x;
            cin >> x;
            can[i][j] = (x == '#');
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            int have = -3 * (1 + can[i][j]);
            for (int l = j; l >= 0; l--){
                have += can[i][l] + 1;
                int have1 = 0;
                for (int r = j; r < m; r++){
                    have1 += can[i][r] + 1;
                    int have2 = 0;
                    for (int u = i; u >= 0; u--){
                        have2 += can[u][j] + 1;
                        int have3 = 0;
                        for (int d = i; d < n; d++){
                            have3 += can[d][j] + 1;
                            if (have + have1 + have2 + have3 <= s)
                                ans++;
                        }
                    }
                }
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
