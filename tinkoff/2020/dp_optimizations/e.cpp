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
const int MAXN = 2e5 + 7;
const ll INF = 1e14;

struct Segment {
    pair<ll, int> mx = {-INF, 0};
    int seg_or = 0;

    Segment(const pair<ll, int> _mx, int _seg_or) : mx(_mx), seg_or(_seg_or) {}

    Segment() = default;
};

int n, k;
int arr[MAXN];
pair<ll, int> dp[MAXN];

pair<ll, int> solve(ll fine) {
    for (int i = 0; i <= n; i++)
        dp[i] = {-INF, 0};
    dp[0] = {0, 0};
    vector<Segment> interest;  // pos, or
    for (int i = 0; i < n; i++) {
        vector<Segment> nxt = {{dp[i], arr[i]}};
        for (int j = SZ(interest) - 1; j >= 0; j--) {
            int nxt1 = (nxt.back().seg_or | interest[j].seg_or);
            if (nxt1 == nxt.back().seg_or)
                nxt.back().mx = max(nxt.back().mx, interest[j].mx);
            else
                nxt.emplace_back(interest[j].mx, nxt1);
        }
        reverse(ALL(nxt));
        swap(interest, nxt);
        for (const auto&[a, b] : interest) {
//            cout << "OR: " << b << ' ' << "MX: {" << a.first << ", " << a.second << "}\n";
//            cout << "NEW BEST: " << a.first + b + fine << ' ' << a.second + 1 << '\n';
            dp[i + 1] = max(dp[i + 1], {a.first + b + fine, a.second - 1});
        }
//        cout << '\n';
        int have = 0;
        for (int j = i; j >= 0; j--) {
            have |= arr[j];
//            cout << "OR: " << have << ' ' << "DP: {" << dp[j].first << ", " << dp[j].second << "}\n";
        }
//        cout << dp[i + 1].first << ' ' << dp[i + 1].second << '\n';
//        cout << "-------\n";
    }
    return dp[n];
}


int solve() {
    if (!(cin >> n >> k))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
//    for (int i = -10; i <= 10; i++) {
//        auto ans = solve(i);
//        cout << i << ": " << ans.first << ' ' << ans.second << ' ' << (ans.first - i * k) << '\n';
//    }
//    solve(-1);
    ll l = -INF, r = 1;
    while (r - l > 1) {
        ll mid = (l + r) / 2;
        auto check = solve(mid);
        if (-check.second <= k)
            l = mid;
        else
            r = mid;
    }
    auto ans = solve(l);
//    cout << l << '\n';
//    cout << ans.second << ' ' << ans.first << '\n';
    cout << ans.first - l * k << '\n';
//    auto sol = solve(-2);
//    cout << sol.first - 2 * sol.second << '\n';
//    sol = solve(-4);
//    cout << sol.second << '\n';
//    cout << sol.first + 2 * sol.second << '\n';
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
