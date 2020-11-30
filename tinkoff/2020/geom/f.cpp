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
#define sqr(x) (x)*(x)
#ifdef LOCAL
#define ass(X) assert(X)
#else
#define ass(X) {}
#endif

struct Point {
    ld x = 0, y = 0;

    Point() : x(0), y(0) {}

    Point(ld _x, ld _y) : x(_x), y(_y) {}

    bool operator<(const Point &point) const {
        return tie(x, y) < tie(point.x, point.y);
    }

    ld vector_product(const Point &o) const {
        return x * o.y - y * o.x;
    }

    ld scalar_product(const Point &o) const {
        return x * o.x + y * o.y;
    }

    ld len2() const {
        return x * x + y * y;
    }

    ld len() const {
        return sqrtl(len2());
    }

    Point operator-(const Point &o) const {
        return Point(x - o.x, y - o.y);
    }

    Point operator+(const Point &o) const {
        return Point(x + o.x, y + o.y);
    }

    Point &operator+=(const Point &o) {
        return (*this) = (*this) + o;
    }

    Point &operator-=(const Point &o) {
        return (*this) = (*this) - o;
    }

    Point operator/(ld a) const {
        return Point(x / a, y / a);
    }

    Point operator*(ld a) const {
        return Point(x * a, y * a);
    }

    Point &operator*=(ld o) {
        return (*this) = (*this) * o;
    }

    Point &operator/=(ld o) {
        return (*this) = (*this) / o;
    }

    friend ostream &operator<<(ostream &os, const Point &point) {
        os << point.x << " " << point.y;
        return os;
    }

    friend istream &operator>>(istream &is, Point &p) {
        is >> p.x >> p.y;
        return is;
    }
};

int n;
const int MAXN = 1e5 + 7;
const ld EPS = 1e-8;

struct Line {
    ld a = 0, b = 0, c = 0;

    Line() {}

    Line(const Point &v, const Point &p) {
        a = v.x;
        b = v.y;
        c = -(a * p.x + b * p.y);
    }

    Point intersect(const Line l) {
        Point res;
        res.y = (c * l.a - l.c * a) / (l.b * a - b * l.a);
        res.x = -(b * res.y + c) / a;
        return res;
    }
};

struct Circle {
    ld r;
    Point center;

    Circle() : r(0), center(0, 0) {}

    Circle(const Point &a, const Point &b) {
        center = Point((a.x + b.x) / 2., (a.y + b.y) / 2.);
//        cerr << a - b << '\n';
        r = (a - b).len() / 2.;
    }

    Circle(const Point &a, const Point &b, const Point &c) {
        center.x = -1.0 / 2 *
                   ((a.y * (sqr(b.x) + sqr(b.y) - sqr(c.x) - sqr(c.y))) +
                    b.y * (sqr(c.x) + sqr(c.y) - sqr(a.x) - sqr(a.y)) +
                    c.y * (sqr(a.x) + sqr(a.y) - sqr(b.x) - sqr(b.y))) /
                   (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
        center.y = 1.0 / 2 *
                   ((a.x * (sqr(b.x) + sqr(b.y) - sqr(c.x) - sqr(c.y))) +
                    b.x * (sqr(c.x) + sqr(c.y) - sqr(a.x) - sqr(a.y)) +
                    c.x * (sqr(a.x) + sqr(a.y) - sqr(b.x) - sqr(b.y))) /
                   (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
        r = (a - center).len();
    }

    bool contains(const Point &c) {
        return (c - center).len() < r || abs(r - (c - center).len()) < EPS;
    }
};

Circle f(vector<Point> &p, const Point &pp, const Point &ppp) {
    Circle c(ppp, pp);
    for (int i = 0; i < SZ(p); i++)
        if (!c.contains(p[i]))
            c = Circle(pp, ppp, p[i]);
    return c;
}

Circle f(vector<Point> &p, const Point &pp) {
    Circle c(pp, p[0]);
    vector<Point> t = {pp, p[0]};
    for (int i = 1; i < SZ(p); i++) {
        if (c.contains(p[i])) {
            t.push_back(p[i]);
            continue;
        }
        c = f(t, pp, p[i]);
        t.push_back(p[i]);
    }
    return c;
}

Circle f(vector<Point> &p) {
    Circle c(p[0], p[1]);
    vector<Point> t = {p[0], p[1]};
    for (int i = 2; i < SZ(p); i++) {
        if (c.contains(p[i])) {
            t.push_back(p[i]);
            continue;
        }
        c = f(t, p[i]);
        t.push_back(p[i]);
    }
    return c;
}

bool check(vector<Point> &a, Circle &b) {
    for (Point &c : a)
        if (!b.contains(c)) {
            cerr << c << '\n';
            cerr << (c - b.center).len() << '\n';
            return false;
        }
    return true;
}

int solve() {
    if (!(cin >> n))
        return 1;
    vector<Point> a(n);
    for (Point &p : a)
        cin >> p;
//    mt19937 rnd(chrono::steady_clock::now().time_since_epoch());
    mt19937 rnd(227);
    shuffle(ALL(a), rnd);
//    while (1) {
//        n = rnd() % 5 + 3;
//        a = vector<Point>(n);
//        for (int i = 0; i < n; i++) {
//            a[i].x = rnd() % ((int) (2 * 1e1)) - 1e1;
//            a[i].y = rnd() % ((int) (2 * 1e1)) - 1e1;
//        }
//        auto res = f(a);
//        if(!check(a, res)){
//            cout << n << '\n';
//            for (Point p : a)
//                cout << p << '\n';
//            exit(0);
//        }
//        cout << ".";
//    }
    auto res = f(a);
    assert(check(a, res));
    cout << fixed << setprecision(20) << res.center << '\n' << res.r << '\n';
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
