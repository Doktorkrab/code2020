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

int n, m, k;
const int MAXN = 1e3 + 5;
const int MOD = 1e9 + 7;
int arr[MAXN][MAXN];

int solve() {
    if (!(cin >> n >> m >> k))
        return 1;
    int now = 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            arr[i][j] = now++;
    for (int i = 0; i < k; i++) {
        char x;
        int a, b;
        cin >> x >> a >> b;
        if (x == 'R') {
            for (int j = 0; j < m; j++)
                arr[a - 1][j] = (1LL * arr[a - 1][j] * b) % MOD;
        } else {
            for (int j = 0; j < n; j++)
                arr[j][a - 1] = (1LL * arr[j][a - 1] * b) % MOD;
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            ans = (ans + arr[i][j]) % MOD;
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
