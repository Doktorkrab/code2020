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

int n;

struct Vector {
    ld x, y;

    Vector() = default;

    Vector(ld x, ld y) : x(x), y(y) {}

    ld operator*(const Vector &oth) const {
        return x * oth.x + y * oth.y;
    }

    ld operator^(const Vector &oth) const {
        return x * oth.y - oth.x * y;
    }

    Vector operator*(long double a) const {
        return Vector(x * a, y * a);
    }

    Vector operator/(long double a) const {
        return Vector(x / a, y / a);
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

    Vector rotate90() {
        return Vector(-y, x);
    }

    ld len() const {
        return sqrt(x * x + y * y);
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

const ld EPS = 1e-9;

struct Line {
    ld a, b, c;

    Line(const Vector &p1, const Vector &p2) {
        Vector normal = (p2 - p1).rotate90();
        a = normal.x;
        b = normal.y;
        c = -(a * p1.x + b * p1.y);
    }

    Line(const Vector &p1, const Vector &p2, const Vector &p3) {
        Vector normal = p2 - p1;
        a = normal.x;
        b = normal.y;
        c = -(a * p3.x + b * p3.y);
    }

    Vector normal() const {
        return Vector(a, b);
    }

    Vector intersect(const Line &oth) const {
//        assert(abs(normal() ^ oth.normal()) < EPS);
        return Vector((oth.c * b - c * oth.b) / (oth.b * a - b * oth.a),
                      (oth.a * c - a * oth.c) / (a * oth.b - oth.a * b));
    }
};

struct Circle {
    ld r;
    Vector center;

    Circle() : r(0), center(0, 0) {}

    Circle(const Vector &a, const Vector &b) {
        center = Vector((a.x + b.x) / 2., (a.y + b.y) / 2.);
        r = (a - b).len() / 2.;
    }

    Circle(const Vector &a, const Vector &b, const Vector &c) {
        Line l1 = Line(a, b, (a + b) / 2.);
        Line l2 = Line(b, c, (b + c) / 2.);
        center = l1.intersect(l2);
        r = (a - center).len();
    }

    bool contains(const Vector &c) {
        return (c - center).len() < r || abs(r - (c - center).len()) < EPS;
    }
};

Circle f(const Vector &p1, const Vector &p2, const vector<Vector> &p) {
    Circle c(p1, p2);
    for (const auto &x : p)
        if (!c.contains(x))
            c = Circle(p1, p2, x);
    return c;
}

Circle f(const Vector &p1, const vector<Vector> &p) {
    Circle c(p1, p[0]);
    vector<Vector> prefix = {p1, p[0]};
    for (int i = 1; i < SZ(p); i++) {
        if (!c.contains(p[i]))
            c = f(p1, p[i], prefix);
        prefix.push_back(p[i]);
    }
    return c;
}

Circle f(const vector<Vector> &p) {
    Circle c(p[0], p[1]);
    vector<Vector> prefix = {p[0], p[1]};
    for (int i = 2; i < SZ(p); i++) {
        if (!c.contains(p[i]))
            c = f(p[i], prefix);
        prefix.push_back(p[i]);
    }
    return c;
}

int solve() {
    if (!(cin >> n))
        return 1;
    vector<Vector> points(n);
    for (Vector &x : points)
        cin >> x;
    mt19937 rnd(239);
    shuffle(ALL(points), rnd);
    cout << setprecision(20) << fixed;
    if (n == 1) {
        cout << points[0] << '\n';
        cout << "0\n";
        return 0;
    }
    auto ans = f(points);
    cout << ans.center << '\n' << ans.r << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
#else
    freopen("circlecover.in", "r", stdin);
    freopen("circlecover.out", "w", stdout);
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
