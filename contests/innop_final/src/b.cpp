#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;

#define int ll
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
const int MAXN = 2e5 + 7;
pair<int, int> pnts[MAXN];
int dp[MAXN][2];
pair<int, int> have[MAXN];
const int INF = 1e9;

int solve() {
    if (!(cin >> n))
        return 1;
    pnts[0] = {0, 0};
    for (int i = 1; i <= n; i++) {
        cin >> pnts[i].first >> pnts[i].second;
    }
    vector<pair<int, char>> ans;
    for (int i = 1; i <= n; i++) {
        int a = pnts[i - 1].second;
        int b = pnts[i].second;
        int c = pnts[i].first - pnts[i - 1].first;
        if ((b + c - a) % 2) {
            cout << "-1\n";
            return 0;
        }
        have[i] = {(b + c - a) / 2, (a + c - b) / 2};
        if (have[i].first < 0 || have[i].second < 0 || have[i].first + have[i].second != c){
            cout << "-1\n";
            return 0;
        }
//        cout << have[i].first << ' ' << have[i].second << '\n';
    }
//    if (have[1].first){
//        int x = 0;
//        cout << "1\n";
//        for (int i = 1; i <= n; i++)
//            x += have[i].first;
//        cout << x << " +\n";
//        return 0;
//    }
//    else {
//        int x = 0;
//        cout << "1\n";
//        for (int i = 1; i <= n; i++)
//            x += have[i].second;
//        cout << x << " -\n";
//        return 0;
//    }
    if (have[1].first)
        dp[1][0] = (!!have[1].first + !!have[1].second);
    else
        dp[1][0] = INF;

    if (have[1].second)
        dp[1][1] = (!!have[1].first + !!have[1].second);
    else
        dp[1][1] = INF;
    for (int i = 2; i <= n; i++) {
        if (have[i].first)
            dp[i][0] = min(dp[i - 1][1] + 1, dp[i - 1][0] + !!have[i].second);
        else
            dp[i][0] = INF;
        if (have[i].second)
            dp[i][1] = min(dp[i - 1][0] + 1, dp[i - 1][1] + !!have[i].first);
        else
            dp[i][1] = INF;
    }
    int now = n;
    int kek = 0;
    if (dp[n][0] > dp[n][1])
        kek = 1;
    while (now >= 1){
        if (kek == 1){
            if (SZ(ans) && ans.back().second == '-')
                ans.back().first += have[now].second;
            else
                ans.emplace_back(have[now].second, '-');
            if (have[now].first)
                ans.emplace_back(have[now].first, '+');
            if (dp[now - 1][0] + 1 == dp[now][1])
                kek = 0;
            else
                kek = 1;
            now--;
        }
        else {
            if (SZ(ans) && ans.back().second == '+')
                ans.back().first += have[now].first;
            else
                ans.emplace_back(have[now].first, '+');
            if (have[now].second)
                ans.emplace_back(have[now].second, '-');
            if (dp[now - 1][1] + 1 == dp[now][0])
                kek = 1;
            else
                kek = 0;
            now--;
        }
//        cout << "now: " << now + 1 << '\n';
//        cout << SZ(ans) << '\n';
//        for (auto [a, b] : ans)
//            cout << a << ' ' << b << '\n';
    }
    reverse(ALL(ans));
    cout << SZ(ans) << '\n';
    for (auto [a, b] : ans)
        cout << a << ' ' << b << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
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
