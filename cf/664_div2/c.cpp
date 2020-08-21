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
const int MAXC = (2 << 9);
const int MAXN = 205;
bool dp[MAXN][MAXC];
int a[MAXN], b[MAXN];

int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int j = 0; j < m; j++)
        cin >> b[j];
    for (int i = 0; i <= n; i++)
        for (int j = 0; j < MAXC; j++)
            dp[i][j] = false;
    dp[0][0] = true;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++)
            for (int k = 0; k < MAXC; k++)
                dp[i + 1][k | (a[i] & b[j])] |= dp[i][k];
    }
    for (int i = 0; i < MAXC; i++)
        if (dp[n][i]){
            cout << i << '\n';
            return 0;
        }
    assert(0);
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
