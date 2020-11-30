#include <bits/stdc++.h>
#include <ostream>

using namespace std;

using ll = long long;
using ld = long double;

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
    ld x, y;

    Vector() : x(0), y(0) {}

    Vector(ld a, ld b) : x(a), y(b) {}

    ld operator^(const Vector &oth) const {
        return x * oth.y - oth.x * y;
    }

    ld operator*(const Vector &oth) const {
        return x * oth.x + y * oth.y;
    }

    bool operator<(const Vector &oth) const {
        return tie(y, x) < tie(oth.y, oth.x);
    }

    Vector operator+(const Vector &oth) const {
        return {x + oth.x, y + oth.y};
    }

    Vector operator-(const Vector &oth) const {
        return {x - oth.x, y - oth.y};
    }

    Vector operator/(const ld a) const {
        return {x / a, y / a};
    }

    ld len() const {
        return (x * x + y * y);
    }

    Vector rotate90() const {
        return {-y, x};
    }
};

const ld EPS = 1e-9;

istream &operator>>(istream &is, Vector &x) {
    is >> x.x >> x.y;
    return is;
}

ostream &operator<<(ostream &os, const Vector &x) {
    os << x.x << ' ' << x.y;
    return os;
}

struct Line {
    ld a, b, c;
    Vector random_point;

    Line(const Vector &p1, const Vector &p2) {
        Vector normal = (p2 - p1).rotate90();
        a = normal.x;
        b = normal.y;
        c = -(a * p1.x + b * p1.y);
        random_point = p1;
    }

    Line(const Vector &p1, const Vector &p2, const Vector &p3) {
        Vector normal = (p2 - p1);
        a = normal.x;
        b = normal.y;
        c = -(a * p3.x + b * p3.y);
        random_point = p3;
    }

    Vector normal() const {
        return Vector(a, b);
    }

    ld operator()(const Vector &x) const {
        return a * x.x + b * x.y + c;
    }

    Vector intersect(const Line &oth) const {
        return Vector((b * oth.c - c * oth.b) / (oth.b * a - b * oth.a),
                      (c * oth.a - oth.c * a) / (oth.b * a - b * oth.a));
    }
};

struct Circle {
    ld r;
    Vector center;

    Circle() : r(0), center(0, 0) {}


    Circle(const Vector &a, const Vector &b, const Vector &c) {
        Line l1(a, b, (a + b) / 2), l2(a, c, (a + c) / 2);
        center = l1.intersect(l2);
        r = (a - center).len();
    }

    bool contains(const Vector &c) {
        return r - (c - center).len() > EPS;
    }
};

int n, m;
const int MAXN = 3e5 + 7;
Vector polygon[MAXN];
map<pair<int, int>, vector<int>> have;

int solve() {
    if (!(cin >> n >> m))
        return 1;
    have.clear();
    for (int i = 0; i < n; i++)
        cin >> polygon[i];
    for (int i = 0; i < m; i++) {
        vector<int> now(3);
        for (int j = 0; j < 3; j++) {
            cin >> now[j];
            now[j]--;
        }
        for (int j = 0; j < 3; j++) {
            int nxt = now[(j + 1) % 3];
            int nnxt = now[(j + 2) % 3];
            if (nxt > nnxt)
                swap(nxt, nnxt);
            have[{nxt, nnxt}].push_back(now[j]);
        }
    }
    for (const auto&[par, v] : have) {
        if (SZ(v) == 1)
            continue;
        auto[a_i, b_i] = par;
        assert(SZ(v) == 2);
        Vector a = polygon[a_i], b = polygon[b_i];
        Vector c = polygon[v[0]], d = polygon[v[1]];
        if (Circle(a, b, c).contains(d) || Circle(a, b, d).contains(c)) {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
    return 0;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}
