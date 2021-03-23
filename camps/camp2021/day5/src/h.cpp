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
const int MAXN = 2e4 + 7;
const ll INF = 1e18;
ll prefix1[MAXN];
ll prefix2[MAXN];
pair<ll, ll> have[MAXN];
ll dp[3][MAXN];

struct Line {
    ll k, b;

    Line() {}

    Line(ll k, ll b) : k(k), b(b) {}

    ll operator()(ll x) const {
        if (x == LONG_LONG_MIN)
            return LONG_LONG_MAX;
        // cerr << x << ' ' << k << " " << b << '\n';
        // cerr << k * x
        return k * x + b;
    }

    bool operator<(const Line &oth) const {
        return tie(k, b) > tie(oth.k, oth.b);
    }
};

inline ll cross(const Line &a, const Line &b) {
    return (b.b - a.b) / (a.k - b.k);
}

struct ConvexHull {
    vector<ll> pr;
    vector<Line> lines;

    ConvexHull() {}

    inline void push(const Line &l) {
        while (!lines.empty() && lines.back()(pr.back()) > l(pr.back())) {
            pr.pop_back();
            lines.pop_back();
        }
        ll coord = LONG_LONG_MIN;
        if (!lines.empty())
            coord = cross(lines.back(), l);
        pr.push_back(coord);
        lines.push_back(l);
    }

    inline ll get(ll x) {
        if (!SZ(lines))
            return TMAX(ll);
        int l = 0, r = lines.size();
        while (r - l > 1) {
            int m = (r + l) / 2;
            if (pr[m] < x)
                l = m;
            else
                r = m;
        }
        return lines[l](x);
    }
};

int solve() {
    if (!(cin >> n))
        return 1;
    ll now = 0;
    for (int i = 0; i < n; i++){
        int w, d;
        cin >> w >> d;
        have[i] = {w, now};
        now += d;
    }
    have[n] = {0, now};
    for (int i = 0; i <= n; i++){
        prefix1[i + 1] = prefix1[i] + have[i].first;
        prefix2[i + 1] = prefix2[i] + have[i].first * have[i].second;
    }
    auto get = [&](int l, int r){
        ll sumw = prefix1[r + 1] - prefix1[l];
        return sumw * have[r].second - (prefix2[r + 1] - prefix2[l]);
    };
    vector<ConvexHull> cht(3);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j <= n + 1; j++)
            dp[i][j] = INF;
    have[n] = {0, now};
    for (int i = 0; i <= n; i++){
        dp[0][i + 1] = get(0, i);
        cht[0].push(Line(-prefix1[i], dp[0][i] + prefix2[i]));
        cht[1].push(Line(-prefix1[i], dp[1][i] + prefix2[i]));
        dp[1][i + 1] = cht[0].get(have[i].second) - prefix2[i + 1] + prefix1[i + 1] * have[i].second;
        dp[2][i + 1] = cht[1].get(have[i].second) - prefix2[i + 1] + prefix1[i + 1] * have[i].second;
//        for (int j = i; j >= 0; j--)
//            dp[1][i + 1] = min(dp[1][i + 1], dp[0][j] + get(j, i));
//        for (int j = i; j >= 0; j--)
//            dp[2][i + 1] = min(dp[2][i + 1], dp[1][j] + get(j, i));
    }
    cout << min(min(dp[0][n + 1], dp[1][n + 1]), dp[2][n + 1]) << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("h.in", "r", stdin);
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
