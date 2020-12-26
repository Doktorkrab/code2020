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
        return asin(((*this) ^ a) / a.len() / len());
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
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> points[i];
    Vector O(0, 0);
    ld ans = Line(points[0], points[1]).dist();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            ans = min(ans, Line(points[i], points[j]).dist());
    cout << setprecision(20) << fixed << ans << '\n';
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
