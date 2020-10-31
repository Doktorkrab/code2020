#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <ctime>
#include <bitset>
#include <complex>
#include <climits>

using namespace std;
using ll = long long;
int n, m, N;
const int MAXN = 2e5 + 7;
const ll INF = 1e18;
ll p[MAXN], s[MAXN];

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

ConvexHull st[4 * MAXN];

ll get(int v, int l, int r, int L, int R, ll coord) {
    if (R <= l || r <= L)
        return LONG_LONG_MAX;
    if (L <= l && r <= R) {
        // cerr << '\t' << l << ' ' << r << '\n';
        return st[v].get(coord);
    }
    int m = (l + r) / 2;
    return min(get(v * 2, l, m, L, R, coord), get(v * 2 + 1, m, r, L, R, coord));
}

ConvexHull merge(const ConvexHull &a, const ConvexHull &b) {
    vector<Line> lines;
    for (auto &x : a.lines)
        lines.push_back(x);
    for (auto &x : b.lines)
        lines.push_back(x);
    sort(lines.begin(), lines.end());
    ConvexHull res;
    for (auto &x : lines)
        res.push(x);
    return res;
}

void build() {
    N = 1;
    while (N < n) N *= 2;
    for (int i = 0; i < n; i++) {
        st[i + N] = ConvexHull();
        // cerr << -2 * s[i] << '\n';
        st[i + N].push(Line(-2 * s[i], p[i] + s[i] * s[i]));
    }
    for (int i = N - 1; i >= 1; i--)
        st[i] = merge(st[2 * i], st[2 * i + 1]);
}

inline void solve() {
    for (int i = 0; i < n; i++)
        cin >> s[i] >> p[i];
    build();
    // cerr << "here\n";
    for (int i = 0; i < m; i++) {
        int lst = 0;
        int cnt;
        ll coord;
        cin >> coord >> cnt;
        // cerr << coord << ' ' << cnt << '\n';
        // cerr << "\t" << i + 1 << '\n';
        ll ans = LONG_LONG_MAX;
        vector<int> dont(cnt);
        for (int j = 0; j < cnt; j++) {
            cin >> dont[j];
            dont[j]--;
        }
        sort(dont.begin(), dont.end());
        for (int j = 0; j < cnt; j++) {
            // cin >> dont[];
            int now = dont[j];
            // now--;
            // cerr << lst << ' ' << now << '\n';
            ans = min(ans, get(1, 0, N, lst, now, coord));
            lst = now + 1;
        }
        // cerr << lst << ' ' << n << '\n';
        ans = min(ans, get(1, 0, N, lst, n, coord)) + coord * coord;
        cout << ans << '\n';
    }
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    while (cin >> n >> m)
        solve();
}
