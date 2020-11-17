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

int n, l;
const int INF = 1e9;
const int MAXN = 5e3 + 7;
int dp[MAXN][MAXN];
int arr[MAXN];
inline int get_len(int l, int r){
    if (l == r)
        return SZ(to_string(l));
    if (l + 1 == r)
        return SZ(to_string(l) + "," + to_string(r));
    return SZ(to_string(l) + ".." + to_string(r));
}
int solve() {
    if (!(cin >> l >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    sort(arr, arr + n);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= l; j++)
            dp[i][j] = INF;
    dp[0][1] = 0;
    for (int i = 0; i < n; i++){
        int sm = 0;
        for (int j = i; j >= 0; j--){
            if (j + 1 <= i)
                sm += max(0, arr[j + 1] - arr[j] - 1);
//            cout << j << ' ' << i << ' ' << sm << '\n';
            int len = get_len(arr[j], arr[i]) + 1;
            for (int k = 1; k + len <= l; k++){
                dp[i + 1][k + len] = min(dp[i + 1][k + len], dp[j][k] + sm);
            }
        }
    }
//    for (int i = 0; i <= n; i++)
//        for (int j = 0; j <= l; j++)
//            cout << dp[i][j] << " \n"[j == l];
    int now = n;
    int x = 0;
    for (int i = 1; i <= l; i++)
        if (dp[n][x] > dp[n][i])
            x = i;
//    cout << x << ' ' << dp[n][x] << '\n';
    vector<string> ans = {"]"};
    cout << dp[now][x] << endl;
    return 0;
    while (now > 0){
        cout << now << '\n';
        int sm = 0;
        for (int j = now - 1; j >= 0; j--){
            if (j + 1 < now)
                sm += max(0, arr[j + 1] - arr[j] - 1);
            int len = get_len(arr[now - 1], arr[j]) + 1;
            if (x - len >= 0 && dp[now][x] == dp[j][x - len] + sm){
                ans.push_back(to_string(arr[now - 1]));
                if (arr[now - 1] == arr[j]) {}
                else if (arr[now - 1] == arr[j] + 1) {
                    ans.emplace_back(",");
                    ans.push_back(to_string(arr[j]));
                }
                else {
                    ans.emplace_back("..");
                    ans.push_back(to_string(arr[j]));
                }
                ans.push_back(",");
                x -= len;
                now = j;
            }
        }
    }
    reverse(ALL(ans));
    ans[0] = "[";
    for (string y : ans)
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
