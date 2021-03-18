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
 
int n;
const int MAXN = 3e5 + 7;
int arr[MAXN];
int min_pos[MAXN];
int max_pos[MAXN];
int dp[MAXN];
vector<int> enters[MAXN];
vector<int> compress;

int solve_fast(){
    for (int i = 0; i < n; i++)
        enters[i].clear(), dp[i] = 0;
    for (int i = 0; i < n; i++)
        enters[arr[i]].push_back(i);
    int ans = 0;
    for (int i = 0; i < SZ(compress); i++){
        dp[i] = SZ(enters[i]);
        int cnt = 0;
        vector<pair<int, int>> lol;
        if (i) {
            if (enters[i - 1].back() < enters[i][0])
                dp[i] = max(dp[i], dp[i - 1] + SZ(enters[i]));
            for (int x : enters[i - 1])
                if (x < enters[i][0])
                     cnt++;
            dp[i] = max(dp[i], cnt + SZ(enters[i]));
            cnt = 0;
            for (int x : enters[i])
                if (x > enters[i - 1].back())
                    cnt++;
            ans = max(ans, dp[i - 1] + cnt);
            for (int x : enters[i - 1])
                lol.emplace_back(x, 0);
        }
        for (int x : enters[i])
            lol.emplace_back(x, 1);
        sort(ALL(lol));
        int dp0 = 0, dp1 = 0;
        for (auto [a, b] : lol){
            if (b == 1)
                dp1++;
            else {
                dp0++;
                dp1 = max(dp0, dp1);
            }
        }
//        cout << dp[i] << ' ' << i << '\n';
        ans = max(ans, dp[i]);
        ans = max(ans, dp1);
    }
    return n - ans;
}

int solve() {
    if (!(cin >> n))
        return 1;
    compress.resize(n);
    for (int i = 0; i < n; i++){
        cin >> arr[i];
        compress[i] = arr[i];
    }
    sort(ALL(compress));
    compress.resize(unique(ALL(compress)) - compress.begin());
    for (int i = 0; i < n; i++)
        arr[i] = (int)(lower_bound(ALL(compress), arr[i]) - compress.begin());

    cout << solve_fast() << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
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
