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

struct Vector {
    ll x, y;

    ll operator*(const Vector &oth) const {
        return x * oth.x + y * oth.y;
    }

    ll operator^(const Vector &oth) const {
        return x * oth.y - oth.x * y;
    }

    Vector operator-(const Vector &oth) const {
        return {x - oth.x, y - oth.y};
    }

    Vector operator+(const Vector &oth) const {
        return {x + oth.x, y + oth.y};
    }

    bool operator<(const Vector &oth) const {
        return tie(x, y) < tie(oth.x, oth.y);
    }

    bool operator==(const Vector &oth) const {
        return tie(x, y) == tie(oth.x, oth.y);
    }
};

istream &operator>>(istream &is, Vector &v) {
    is >> v.x >> v.y;
    return is;
}

ostream &operator<<(ostream &os, Vector &v) {
    os << v.x << ' ' << v.y;
    return os;
}

inline int cmp(const Vector &a, const Vector &b, const Vector &c) {
    ll t = (b - a) ^(c - b);
    if (t < 0)
        return -1;
    if (t > 0)
        return 1;
    return 0;
}

vector<Vector> convex_hull(vector<Vector> points) {
    int n = SZ(points);
    sort(ALL(points));
    points.resize(unique(ALL(points)) - points.begin());
    n = SZ(points);
    if (n <= 2)
        return points;
    vector<Vector> lower{points.begin(), points.begin() + 2};
    for (int i = 2; i < n; i++) {
        while (SZ(lower) >= 2 && cmp(lower[SZ(lower) - 2], lower.back(), points[i]) <= 0)
            lower.pop_back();
        lower.push_back(points[i]);
    }
    lower.pop_back();
    reverse(ALL(points));
    vector<Vector> upper{points.begin(), points.begin() + 2};
    for (int i = 2; i < n; i++) {
        while (SZ(upper) >= 2 && cmp(upper[SZ(upper) - 2], upper.back(), points[i]) <= 0)
            upper.pop_back();
        upper.push_back(points[i]);
    }
    upper.pop_back();
    for (auto x : upper)
        lower.push_back(x);
    reverse(ALL(lower));
    if (lower[0] == lower.back())
        lower.pop_back();
    set<Vector> kek{ALL(lower)};
    assert(SZ(lower) == SZ(kek));
    return lower;
}

ll trap_square(Vector a, Vector b) {
    return (a.y + b.y) * (b.x - a.x);
}

ll find_square(const vector<Vector> &points) {
    ll ans = 0;
    int n = SZ(points);
    for (int i = 0; i < n; i++) {
        int nxt = (i + 1) % n;
        ans += trap_square(points[i], points[nxt]);
    }
    return abs(ans);
}

int n;


int solve() {
    if (!(cin >> n))
        return 1;
    vector<Vector> points(n);
    for (Vector &x : points)
        cin >> x;
    auto convex = convex_hull(points);
    cout << SZ(convex) << '\n';
    for (Vector &x : convex)
        cout << x << '\n';
    ll ans = find_square(convex);
    cout << ans / 2;
    if (ans % 2)
        cout << ".5";
    else
        cout << ".0";
    cout << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#else
    freopen("hull.in", "r", stdin);
    freopen("hull.out", "w", stdout);
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