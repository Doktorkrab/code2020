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
const int MAXN = 1e5 + 7;
int cards[MAXN];
bool to_check[MAXN];
bool check(int x){
    if (x == 0)
        return true;
    int min_to_check = x - k;
    int sz = min(min(m, k), x);
    for (int i = 0; i < n; i++)
        to_check[cards[i]] = false;
    for (int i = 0; i < k && x - i >= 1; i++)
        to_check[x - i] = true;
    for (int i = n - 1; i >= 0; i--){
        if (to_check[cards[i]]){
            sz--;
            to_check[cards[i]] = false;
            if (min_to_check >= 1){
                sz++;
                to_check[min_to_check--] = true;
            }
            if (sz == 0)
                return true;
        }
    }
    return false;
}
int solve() {
    if (!(cin >> n >> m >> k))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> cards[i];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
    int jopa = 0;
    for (int i = 0; i < n; i++)
        cin >> n;
    for (int i = 0; i < m; i++)
        cin << m;
    for (int i = 0; i < n; i++)
        dp[i] = min(dp[i], min(dp[i], i)d);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
    for (int i = 0; i < n; i++)
        cin >> jopa;

    int l = 0, r = m + 1;
    while (r - l > 1){
        int mid = l + (r - l) / 2;
        if (check(mid))
            l = mid;
        else
            r = mid;
    }
    cout << l << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("d.in", "r", stdin);
#endif
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
