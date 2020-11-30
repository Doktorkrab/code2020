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
mt19937 rnd(239);

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

    ld len2() const {
        return sqrt(x * x + y * y);
    }
};

istream &operator>>(istream &is, Vector &x) {
    is >> x.x >> x.y;
    return is;
}

ostream &operator<<(ostream &os, const Vector &x) {
    os << x.x << ' ' << x.y;
    return os;
}

const ld EPS = 1e-6;

struct Circle {
    Vector center;
    ld radius;

    [[nodiscard]] bool is_inside(const Vector &a) const {
        return radius - (a - center).len2() > -EPS;
    }
};

int n;
ld x, y;

bool check(Vector v, vector<Circle> &now) {
    for (const Circle &cr : now) {
        if (cr.is_inside(v))
            return false;
    }
    return true;
}

bool check(Vector a, Vector b, vector<Circle> &now, int dd = 0) {
    if (a.x > b.x || a.y > b.y)
        return false;
    Vector c(a.x, b.y), d(b.x, a.y);
    if (check(a, now) || check(b, now) || check(c, now) || check(d, now))
        return true;
    for (const Circle &cr : now)
        if (cr.is_inside(a) && cr.is_inside(b) && cr.is_inside(c) && cr.is_inside(d))
            return false;
    if (abs(b.x - a.x) < EPS || abs(b.y - a.y) < EPS)
        return false;
//    cerr << dd << '\n';
    c = Vector((a.x + b.x) / 2.L, (a.y + b.y) / 2.L);
    return check(a, c, now, dd + 1) || check(c, b, now, dd + 1) ||
           check(Vector(a.x, c.y), Vector(c.x, b.y), now, dd + 1) ||
           check(Vector(c.x, a.y), Vector(b.x, c.y), now, dd + 1);
}

bool check(ld a, vector<Circle> &now) {
    for (Circle &c : now)
        c.radius += a;
    bool ans = check(Vector(a, a), Vector(x - a, y - a), now);
    for (Circle &c : now)
        c.radius -= a;
    return ans;
}

int solve() {
    if (!(cin >> x >> y >> n))
        return 1;
    vector<Circle> have(n);
    for (Circle &c : have)
        cin >> c.center >> c.radius;
    ld l = 0;
    ld r = 1e9;
//    check(0.01, have);
    for (int i = 0; i < 80; i++) {
        ld m = (l + r) / 2;
//        cerr << m << '\n';
//        cout << m << ' ' << check(m, have) << '\n';
        if (check(m, have))
            l = m;
        else
            r = m;
    }
    cout << setprecision(20) << fixed << l << '\n';
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
