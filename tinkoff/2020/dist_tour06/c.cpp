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
#define int unsigned
int n, l;
const int INF = 1e9 + 1e4;
const int MAXN = 5e3 + 7;
unsigned dp[2][MAXN][MAXN];
int arr[MAXN];

int solve() {
    if (!(cin >> l >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    arr[n++] = 1;
    l += 2;
    sort(arr, arr + n);
    n = unique(arr, arr + n) - arr;
    for (int k = 0; k < 2; k++)
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= l; j++)
                dp[k][i][j] = INF;
    dp[0][0][2 + to_string(arr[0]).size()] = 0;
    for (int i = 1; i < n; i++) {
        int sz = SZ(to_string(arr[i]));
        for (int k = 1; k + 1 + sz <= l; k++)
            dp[0][i][k + 1 + sz] = min(dp[1][i - 1][k], dp[0][i - 1][k]);
        ll err = arr[i] - arr[i - 1] - 1;
        for (int k = 1; k + 2 + sz <= l; k++)
            dp[1][i][k + 2 + sz] = min((ll) dp[1][i][k + 2 + sz], (ll) dp[0][i - 1][k] + err);
        int cur = 9;
        for (int j = 0; j < 9; j++) {
            sz = SZ(to_string(cur));
            if (cur >= arr[i])
                break;
            err = SZ(to_string(arr[i])) - SZ(to_string(cur)) - 1;
            for (int k = 1; k + 2 + sz <= l; k++) {
//                cout << i << ' ' << k + 2 + sz << ' ' << dp[0][i - 1][k] + err << '\n';
                dp[1][i][k + 2 + sz] = min((ll) dp[1][i][k + 2 + sz], dp[0][i - 1][k] + err);
            }
            cur = cur * 10 + 9;
        }
        sz = SZ(to_string(arr[i])) - SZ(to_string(arr[i - 1]));
        for (int k = 1; k + sz <= l; k++)
            dp[1][i][k + sz] = min((ll) dp[1][i][k + sz], (ll) dp[1][i - 1][k] + err);
    }
    for (int k = 0; k < 2; k++) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j <= l; j++)
                cout << dp[k][i][j] << " \n"[j == l];
        cout << "---" << endl;
    }
    int type = 0;
    int x = 0;
    int now = n - 1;
    for (int i = 1; i < 2; i--)
        for (int j = 0; j <= l; j++)
            if (dp[i][n - 1][j] < dp[type][now][x]) {
                type = i;
                x = j;
            }
//    cerr << dp[type][n - 1][x] << '\n';
//    return 0;
    vector<string> ans = {"]"};
    if (type == 1) {
        ans.push_back(to_string(arr[n - 1]));
        ans.emplace_back("..");
    }
    while (now > 0) {
        assert(x > 0);
        if (type == 0) {
            int sz = SZ(to_string(arr[now])) + 1;
            ans.push_back(to_string(arr[now]));
            ans.emplace_back(",");
            if (dp[1][now - 1][x - sz] == dp[0][now][x]) {
                type = 1;
                ans.push_back(to_string(arr[now - 1]));
                ans.emplace_back("..");
            }
            now--;
            x -= sz;
        } else {
            int err = arr[now] - arr[now - 1] - 1;
            int sz = SZ(to_string(arr[now])) + 2;
            assert(dp[1][now][x] < INF);
            if (dp[0][now - 1][x - sz] + err == dp[1][now][x]) {
                type = 0;
                x -= sz;
                now--;
                continue;
            }
            int cur = 9;
            bool good = false;
            for (int j = 0; j < 9; j++) {
                if (cur >= arr[now])
                    break;
                sz = SZ(to_string(cur));
                err = SZ(to_string(arr[now])) - SZ(to_string(cur)) - 1;
                if (dp[0][now - 1][x - sz] + err == dp[1][now][x]) {
                    type = 0;
                    x -= sz;
                    now--;
                    ans.push_back(to_string(cur));
                    ans.emplace_back(",");
                    good = true;
                    break;
                }
                cur = cur * 10 + 9;
            }
            if (!good) {
                sz = SZ(to_string(arr[now])) - SZ(to_string(arr[now - 1]));
                x -= sz;
                now--;
            }
        }
    }
//    ans.pop_back();

//    ans.push_back(to_string(arr[0]));
    ans.emplace_back("[");
    reverse(ALL(ans));
    for (const string &y : ans)
        cout << y;
    cout << '\n';
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
