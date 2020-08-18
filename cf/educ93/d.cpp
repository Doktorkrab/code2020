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
 
// int nr, ng, nb;
const int MAXN = 205;
int n[3];
int arr[3][MAXN];
int dp[MAXN][MAXN][MAXN];
void relax(int& x, int y){
    x = max(x, y);
}
int solve() {
    if (!(cin >> n[0] >> n[1] >> n[2]))
        return 1;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < n[i]; j++){
            cin >> arr[i][j]; 
        }
        sort(arr[i], arr[i] + n[i]);
        reverse(arr[i], arr[i] + n[i]);
    }
    int *r = arr[0], *g = arr[1], *b = arr[2];
    // dp[0][0][0] = 0;

    for (int i = 0; i <= n[0]; i++){
        for (int j = 0; j <= n[1]; j++){
            for (int k = 0; k <= n[2]; k++){
                dp[i][j][k] = 0;
                int& d = dp[i][j][k];
                if (i)
                    relax(d, dp[i - 1][j][k]);
                if (j)
                    relax(d, dp[i][j - 1][k]);
                if (k)
                    relax(d, dp[i][j][k - 1]);
                if (i && j)
                    relax(d, dp[i - 1][j - 1][k] + r[i - 1] * g[j - 1]);
                if (i && k)
                    relax(d, dp[i - 1][j][k - 1] + r[i - 1] * b[k - 1]);
                if (j && k)
                    relax(d, dp[i][j - 1][k - 1] + g[j - 1] * b[k - 1]);
            }
        }
    }
    cout << dp[n[0]][n[1]][n[2]] << '\n';
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