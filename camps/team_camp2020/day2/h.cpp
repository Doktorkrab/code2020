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
using ld = long double;
int n;

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
        return sqrt(x * x + y * y);
    }

    Vector rotate90() const {
        return {-y, x};
    }

    ld angle(const Vector &a) const {
        return acos(((*this) * a) / a.len() / len());
    }
};

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

    ld dist() const {
        return abs(c / normal().len());
    }

    Vector intersect(const Line &oth) const {
        return Vector((b * oth.c - c * oth.b) / (oth.b * a - b * oth.a),
                      (c * oth.a - oth.c * a) / (oth.b * a - b * oth.a));
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

const int MAXN = 1e5 + 7;
Vector points[MAXN];
ld ans;

void solve_1() {
    int l = 0;
    for (int i = 0; i < n; i++) {
        while (i == l || ((points[i] ^ points[(l + 1) % n]) >= 0 &&
                          points[i].angle(points[l]) < points[i].angle(points[(l + 1) % n])))
            l = (l + 1) % n;
//        cerr << i << ' ' << l << ' ' << points[i].angle(points[l]) << ' ' << points[i].angle(points[(l + 1) % n])
//             << '\n';
        if (i != l) {
            ans = min(ans, Line(points[i], points[l]).dist());
//            cerr << i << ' ' << l << ' ' << Line(points[i], points[l]).dist() << '\n';
        }
    }
}

void solve_2() {
    int l = 0;
    for (int i = 0; i < n; i++) {
        while (i == l || ((points[(l - 1 + n) % n] ^ points[i]) >= 0 &&
                          points[l].angle(points[i]) < points[(l - 1 + n) % n].angle(points[i])))
            l = (l - 1 + n) % n;
        if (i != l) {
            ans = min(ans, Line(points[i], points[l]).dist());
//            cerr << i << ' ' << l << ' ' << Line(points[i], points[l]).dist() << '\n';
        }
    }
}

void solve_3() {
    set<pair<int, int>> was;
    for (int i = 0; i < n; i++) {
        pair<int, int> gg = {(int) points[i].x, (int) points[i].y};
        if (gg.first < 0) {
            gg.first *= -1;
            gg.second *= -1;
        }
        if (gg.first == 0 && gg.second < 0)
            gg.second *= -1;
        int g = gcd(abs(gg.first), abs(gg.second));
        if (g != 0) {
            gg.first /= g;
            gg.second /= g;
        }
        if (was.count(gg))
            ans = 0;
        was.insert(gg);
    }
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> points[i];
    sort(points, points + n, [&](const Vector &a, const Vector &b) { return atan2(a.y, a.x) < atan2(b.y, b.x); });
//    for (int i = 0; i < n; i++)
//        cout << points[i] << '\n';
    ans = Line(points[0], points[n - 1]).dist();
    for (int i = 0; i + 1 < n; i++) {
        ans = min(ans, Line(points[i], points[i + 1]).dist());
    }
    solve_1();
//    cerr << '\n';
    solve_2();
    solve_3();
    cout << fixed << setprecision(20);
    cout << ans << '\n';
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
