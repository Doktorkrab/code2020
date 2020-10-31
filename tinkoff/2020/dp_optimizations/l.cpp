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

struct Line {
    ll k = 0, b = 1e17;

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
    int pos = 0;

    ConvexHull() {}

    inline void push(const Line &l) {
        while (!lines.empty() && lines.back()(pr.back()) > l(pr.back())) {
            pr.pop_back();
            lines.pop_back();
        }
        ll coord = -1e9;
        if (!lines.empty())
            coord = cross(lines.back(), l);
        pr.push_back(coord);
        lines.push_back(l);
    }

    inline ll get(ll x) {
        pos = min(pos, (int) lines.size() - 1);
        while (pos + 1 < SZ(lines) && pr[pos + 1] <= x)
            pos++;
        return lines[pos](x);
    }
};

int n, m, p;
const int MAXN = 1e5 + 7;
ll hills[MAXN];
ll cats[MAXN];
ll s[MAXN];
ll dp[205][MAXN];
ConvexHull have[205];

int solve() {
    if (!(cin >> n >> m >> p))
        return 1;
    hills[0] = 0;
    for (int i = 1; i < n; i++) {
        cin >> hills[i];
        hills[i] += hills[i - 1];
    }
    for (int i = 0; i < m; i++) {
        ll h, t;
        cin >> h >> t;
        cats[i] = t - hills[h - 1];
    }
    sort(cats, cats + m);
    for (int i = 0; i < m; i++)
        s[i] = cats[i] + (i > 0 ? s[i - 1] : 0);

    for (int i = 0; i < m; i++) {
        dp[0][i] = 1LL * cats[i] * (i + 1) - s[i];
        have[0].push(Line(-i - 1, s[i] + dp[0][i]));
        for (int j = 1; j < p; j++) {
            dp[j][i] = have[j - 1].get(cats[i]) + cats[i] * (i + 1) - s[i];
            have[j].push(Line(-i - 1, s[i] + dp[j][i]));
        }
    }
    cout << dp[p - 1][m - 1] << '\n';
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
