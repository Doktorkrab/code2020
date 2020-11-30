#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;
using ld = long double;
#ifdef LOCAL
#define ass(X) assert(X)
#else
#define ass(X) {}
#endif
const ld EPS = 1e-8;

struct Vector {
    ld x, y;

    Vector() = default;

    Vector(ld x, ld y) : x(x), y(y) {}

    Vector(const Vector &a, const Vector &b) : x(b.x - a.x), y(b.y - a.y) {}

    Vector operator+(const Vector &oth) const {
        return {x + oth.x, y + oth.y};
    }

    Vector operator-(const Vector &oth) const {
        return Vector(x - oth.x, y - oth.y);
    }

    ld len() const {
        return sqrtl(x * x + y * y);
    }

    Vector rotate90() const {
        return Vector(-y, x);
    }
};

ld cross_product(const Vector &a, const Vector &b) {
    return a.x * b.y - a.y * b.x;
}

ld dot_product(const Vector &a, const Vector &b) {
    return a.x * b.x + a.y * b.y;
}

istream &operator>>(istream &is, Vector &v) {
    is >> v.x >> v.y;
    return is;
}

ostream &operator<<(ostream &os, const Vector &v) {
    os << v.x << ' ' << v.y;
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

    Vector normal() const {
        return Vector(a, b);
    }

    int operator()(const Vector &x) const {
        return a * x.x + b * x.y + c;
    }

    Vector intersect(const Line &oth) const {
        return Vector((b * oth.c - c * oth.b) / (oth.b * a - b * oth.a),
                      (c * oth.a - oth.c * a) / (oth.b * a - b * oth.a));
    }
};

struct Segment {
    Vector a, b;

    Segment(Vector a, Vector b) : a(a), b(b) {}

    Line line() const {
        return Line(a, b);
    }

    Vector vector() const {
        return Vector(a, b);
    }
};

struct Ray {
    Vector a, b;

    Ray(Vector a, Vector b) : a(a), b(b) {}

    Vector vector() const {
        return Vector(a, b);
    }

    Line line() const {
        return Line(a, b);
    }
};

Vector a, b, c, d;

bool is_intersect(const Vector &a, const Segment &s) {
    return abs(cross_product(s.vector(), a - s.a)) < EPS && dot_product(s.a - a, s.b - a) < EPS;
}
bool is_intersect(const Vector &a, const Ray &r) {
    return abs(cross_product(r.vector(), a - r.a)) < EPS && dot_product(r.vector(), a - r.a) > -EPS;
}
bool is_intersect(const Vector &a, const Line &l1) {
    return abs(l1(a)) < EPS;
}
bool is_intersect(const Segment &s, const Vector &a) {
    return is_intersect(a, s);
}
bool is_intersect(const Segment &s1, const Segment &s2) {
    if (is_intersect(s1.a, s2) || is_intersect(s1.b, s2))
        return true;
    if (is_intersect(s2.a, s1) || is_intersect(s2.b, s1))
        return true;
    if (cross_product(s1.vector(), (s2.a - s1.a)) * cross_product(s1.vector(), (s2.b - s1.a)) < 0 &&
        cross_product(s2.vector(), (s1.a - s2.a)) * cross_product(s2.vector(), (s1.b - s2.a)) < 0)
        return true;
    return false;
}
bool is_intersect(const Segment &s1, const Ray &r1) {
    if (cross_product(r1.vector(), s1.a - r1.a) * cross_product(r1.vector(), s1.b - r1.a) < 0) {
        if (cross_product(r1.vector(), s1.a - r1.a) > 0) {
            return cross_product(s1.vector(), r1.a - s1.a) < 0;
        }
        return cross_product(s1.vector(), r1.a - s1.a) > 0;
    }
    return is_intersect(s1.a, r1) || is_intersect(s1.b, r1);
}
bool is_intersect(const Segment &s1, const Line &l1) {
    Vector napr = l1.normal().rotate90();
    Vector p1 = l1.random_point;
    return (cross_product(napr, s1.a - p1) * cross_product(napr, s1.b - p1) < EPS);
}
bool is_intersect(const Line &l1, const Vector &v) {
    return abs(l1(v)) < EPS;
}
bool is_intersect(const Line &l1, const Line &l2) {
    return (abs(cross_product(l1.normal(), l2.normal())) > EPS) || is_intersect(l1, l2.random_point);
}
bool is_intersect(const Line &l1, const Segment &s1) {
    return is_intersect(s1, l1);
}
bool is_intersect(const Line &l1, const Ray &r1) {
    if (!is_intersect(l1, r1.line()))
        return false;
    return is_intersect(l1.intersect(r1.line()), r1);
}
bool is_intersect(const Ray &r, const Vector &a) {
    return is_intersect(a, r);
}
bool is_intersect(const Ray &r1, const Segment &s1) {
    return is_intersect(s1, r1);
}
bool is_intersect(const Ray &r1, const Line &l1) {
    return is_intersect(l1, r1);
}
bool is_intersect(const Ray &r1, const Ray &r2) {
    if (abs(cross_product(r1.vector(), r2.vector())) < EPS)
        return is_intersect(r1, r2.a) || is_intersect(r2, r1.a);
    return is_intersect(r1, r2.line()) && is_intersect(r2, r1.line());
}

ld distance(const Vector &a, const Vector &b) {
    return (b - a).len();
}
ld distance(const Vector &p, const Line &l) {
    return abs(1.L * (l.a * p.x + l.b * p.y + l.c) / l.normal().len());
}
ld distance(const Vector &b, const Segment &s) {
    if (dot_product(b - s.a, s.b - s.a) < 0 || dot_product(b - s.b, s.a - s.b) < 0)
        return min(distance(b, s.a), distance(b, s.b));
    return distance(b, s.line());
}
ld distance(const Vector &p, const Ray &r) {
    if (dot_product(p - r.a, r.vector()) < 0)
        return distance(p, r.a);
    return distance(p, r.line());
}
ld distance(const Segment &s, const Vector &p) {
    return distance(p, s);
}
ld distance(const Segment &s1, const Segment &s2) {
    if (is_intersect(s1, s2))
        return 0;
    return min(min(distance(s1.a, s2), distance(s1.b, s2)), min(distance(s2.a, s1), distance(s2.b, s1)));
}
ld distance(const Segment &s1, const Ray &r1) {
    if (is_intersect(s1, r1))
        return 0;
    return min(min(distance(s1.a, r1), distance(s1.b, r1)), distance(r1.a, s1));
}
ld distance(const Segment &s1, const Line &l1) {
    if (is_intersect(s1, l1))
        return 0;
    return min(distance(s1.a, l1), distance(s1.b, l1));
}
ld distance(const Ray &r1, const Vector &a) {
    return distance(a, r1);
}
ld distance(const Ray &r1, const Segment &s1) {
    return distance(s1, r1);
}
ld distance(const Ray &r1, const Ray &r2) {
    if (is_intersect(r1, r2))
        return 0;
    return min(distance(r1.a, r2), distance(r2.a, r1));
}
ld distance(const Ray &r1, const Line &l1) {
    if (is_intersect(r1, l1))
        return 0;
    return distance(r1.a, l1);
}
ld distance(const Line &l1, const Vector &p1) {
    return distance(p1, l1);
}
ld distance(const Line &l1, const Segment &s1) {
    return distance(s1, l1);
}
ld distance(const Line &l1, const Ray &r1) {
    return distance(r1, l1);
}
ld distance(const Line &l1, const Line &l2) {
    if (is_intersect(l1, l2))
        return 0;
    return distance(l1.random_point, l2);
}

int solve() {
    if (!(cin >> a >> b >> c >> d))
        return 1;
    cout << setprecision(20) << fixed;
    Segment ab_s(a, b), cd_s(c, d);
    Ray ab_r(a, b), cd_r(c, d);
    Line ab_l(a, b), cd_l(c, d);
    cout << distance(a, c) << '\n';
    cout << distance(a, cd_s) << '\n';
    cout << distance(a, cd_r) << '\n';
    cout << distance(a, cd_l) << '\n';
    cout << distance(ab_s, c) << '\n';
    cout << distance(ab_s, cd_s) << '\n';
    cout << distance(ab_s, cd_r) << '\n';
    cout << distance(ab_s, cd_l) << '\n';
    cout << distance(ab_r, c) << '\n';
    cout << distance(ab_r, cd_s) << '\n';
    cout << "\n";
    cout << distance(ab_r, cd_r) << '\n';
    cout << distance(ab_r, cd_l) << '\n';
    cout << distance(ab_l, c) << '\n';
    cout << distance(ab_l, cd_s) << '\n';
    cout << distance(ab_l, cd_r) << '\n';
    cout << distance(ab_l, cd_l) << '\n';

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
