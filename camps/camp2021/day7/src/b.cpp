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

struct Point {
    ll x, y;

    Point() = default;

    Point(ll x, ll y) : x(x), y(y) {}

    Point operator-(const Point &oth) const {
        return Point(x - oth.x, y - oth.y);
    }

    Point operator+(const Point &oth) const {
        return Point(x + oth.x, y + oth.y);
    }

    bool operator<(const Point &oth) const {
        return make_pair(x, y) < make_pair(oth.x, oth.y);
    }

    Point rotate90() const {
        return Point(-y, x);
    }

    Point rotate180() const {
        return Point(-x, -y);
    }
};

istream &operator>>(istream &is, Point &p) {
    is >> p.x >> p.y;
    return is;
}

ostream &operator<<(ostream &os, const Point &p) {
    os << p.x << ' ' << p.y;
    return os;
}

int n;
const int MAXN = 1e5 + 7;
Point arr[MAXN];

unordered_map<ll, vector<ll>> diagonals1, diagonals2;
unordered_map<ll, vector<ll>> verticals, horizontals;
set<Point> have;

int solve() {
    if (!(cin >> n))
        return 1;
    diagonals1.clear();
    diagonals2.clear();
    verticals.clear();
    horizontals.clear();
    have.clear();
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        diagonals1[arr[i].x - arr[i].y].push_back(arr[i].x);
        diagonals2[arr[i].x + arr[i].y].push_back(arr[i].x);
        verticals[arr[i].x].push_back(arr[i].y);
        horizontals[arr[i].y].push_back(arr[i].x);
        have.insert(arr[i]);
    }
    for (auto&[a, b] : horizontals)
        sort(ALL(b));
    for (auto&[a, b] : verticals)
        sort(ALL(b));

    for (auto&[a, b] : diagonals1)
        sort(ALL(b));
    for (auto&[a, b] : diagonals2)
        sort(ALL(b));

    auto check_diagonal1 = [&](ll x1, ll y, ll l) { // (x, y) -> (x + l, y + l)
        auto it = upper_bound(ALL(diagonals1[x1 - y]), x1);
        if (it == diagonals1[x1 - y].end())
            return false;
        return (*it) == (x1 + l);
    };
    auto check_diagonal2 = [&](ll x1, ll y, ll l) { // (x, y) -> (x + l), (y - l)
        auto it = upper_bound(ALL(diagonals2[x1 + y]), x1);
        if (it == diagonals2[x1 + y].end())
            return false;
        return (*it) == (x1 + l);
    };
    ll ans = 0;
    for (auto&[y, now] : horizontals) {
        for (int i = 0; i + 1 < SZ(now); i++) {
            ll a = now[i], b = now[i + 1];
            ll l = b - a;

            if (upper_bound(ALL(verticals[a]), y) != verticals[a].end() &&
                (*upper_bound(ALL(verticals[a]), y) - y) == l) {
                ans += check_diagonal2(a, y + l, l);
            }
            if (lower_bound(ALL(verticals[a]), y) != verticals[a].begin() &&
                (y - (*prev(lower_bound(ALL(verticals[a]), y)))) == l) {
                ans += check_diagonal1(a, y - l, l);
            }
            if (upper_bound(ALL(verticals[b]), y) != verticals[b].end() &&
                (*upper_bound(ALL(verticals[b]), y) - y) == l) {
                ans += check_diagonal1(a, y, l);
            }
            if (lower_bound(ALL(verticals[b]), y) != verticals[b].begin() &&
                (y - (*prev(lower_bound(ALL(verticals[b]), y)))) == l) {
                ans += check_diagonal2(a, y, l);
            }
            if (l % 2 == 0 && check_diagonal1(a, y, l / 2) && check_diagonal2(a + l / 2, y + l / 2, l / 2)
                && verticals.count(a + l / 2) &&
                lower_bound(ALL(verticals[a + l / 2]), y + l / 2) != verticals[a + l / 2].end() &&
                (*lower_bound(ALL(verticals[a + l / 2]), y + l / 2) == y + l / 2)) {
                ans++;
            }
            if (l % 2 == 0 && check_diagonal2(a, y, l / 2) && check_diagonal1(a + l / 2, y - l / 2, l / 2) &&
                verticals.count(a + l / 2) &&
                lower_bound(ALL(verticals[a + l / 2]), y - l / 2) != verticals[a + l / 2].end() &&
                (*lower_bound(ALL(verticals[a + l / 2]), y - l / 2) == y - l / 2)) {
                ans++;
            }
        }
    }
    for (auto&[x, now] : verticals) {
        for (int i = 0; i + 1 < SZ(now); i++) {
            ll a = now[i], b = now[i + 1];
            ll l = b - a;
            if (l % 2 == 0 && check_diagonal1(x, a, l / 2) && check_diagonal2(x, b, l / 2) &&
                horizontals.count(a + l / 2) &&
                lower_bound(ALL(horizontals[a + l / 2]), x + l / 2) != horizontals[a + l / 2].end() &&
                (*lower_bound(ALL(horizontals[a + l / 2]), x + l / 2)) == x + l / 2) {
                ans++;
            }
            if (l % 2 == 0 && check_diagonal1(x - l / 2, b - l / 2, l / 2) &&
                check_diagonal2(x - l / 2, b - l / 2, l / 2) &&
                horizontals.count(a + l / 2) &&
                lower_bound(ALL(horizontals[a + l / 2]), x - l / 2) != horizontals[a + l / 2].end() &&
                (*lower_bound(ALL(horizontals[a + l / 2]), x - l / 2)) == x - l / 2) {
                ans++;
            }
        }
    }
    cout << ans << '\n';

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
