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

    Vector() = default;

    Vector(ld x, ld y) : x(x), y(y) {}

    Vector operator+(const Vector &oth) const {
        return Vector(x + oth.x, y + oth.y);
    }

    Vector operator-(const Vector &oth) const {
        return Vector(x - oth.x, y - oth.y);
    }

    Vector operator*(ld k) const {
        return Vector(x * k, y * k);
    }

    Vector operator/(ld k) const {
        return Vector(x / k, y / k);
    }

    Vector &operator*=(ld k) {
        return (*this) = (*this) * k;
    }

    Vector &operator/=(ld k) {
        return (*this) = (*this) / k;
    }

    Vector &operator+=(const Vector &oth) {
        return (*this) = (*this) + oth;
    }

    Vector &operator-=(const Vector &oth) {
        return (*this) = (*this) - oth;
    }

    ld len() const {
//        assert(x * x + y * y < 9e18);
//        return abs(x) + abs(y);
        return sqrt(x * x + y * y);
    }
};

istream &operator>>(istream &is, Vector &v) {
    is >> v.x >> v.y;
    return is;
}

ostream &operator<<(ostream &os, const Vector &v) {
    os << v.x << ' ' << v.y;
    return os;
}

int n;
ld l;
int k;
const int MAXN = 2e5 + 7;
Vector polygon[2 * MAXN];
bool hole[2 * MAXN];
ld took[2 * MAXN];

ld dist(Vector a, Vector b) {
    Vector c = b - a;
    if (abs(c.x) < 1e9 && abs(c.y) < 1e9)
        return c.len();
    ld kek = c.x;
    if (abs(c.x) < 1e-12 || abs(c.x) < abs(c.y))
        kek = c.y;
    c /= kek;
    ld not_dist = c.len();
    c /= not_dist;
    return abs((b.y - a.y) / c.y);
}

int solve() {
    if (!(cin >> n >> l >> k))
        return 1;
    fill(hole, hole + 2 * n, false);
    ld have = 0;
    for (int i = 0; i < k; i++) {
        int x;
        cin >> x;
        hole[x - 1] = hole[x - 1 + n] = true;
    }
    for (int i = 0; i < n; i++) {
        cin >> polygon[i];
        polygon[i + n] = polygon[i];
    }
    polygon[2 * n] = polygon[n];
    for (int i = 0; i < n; i++)
        if (hole[i])
            have += dist(polygon[i + 1], polygon[i]);
    ld best = have;
    int r = 0;
    ld now = 0;
    ld now_hole = 0;
    auto get = [&](int i) {
        if (!hole[i])
            return 0.L;
        return dist(polygon[i + 1], polygon[i]);
    };
    for (int i = 0; i < n; i++) {
        while (r < i)
            r++;
        while (r - i < n && r < 2 * n && l - now > 0) {
            took[r] = min(l - now, dist(polygon[r], polygon[r + 1]));
//            cerr << polygon[i] << ' ' << p
//            cerr << r << ' ' << l - now << " " << dist(polygon[i], polygon[i + 1]) << "?\n";
            now += took[r];
            if (hole[r])
                now_hole += took[r];
            r++;
        }
        best = min(best, have - now_hole);
        if (i != r && took[r - 1] < dist(polygon[r - 1], polygon[r])) {
            --r;
            now -= took[r];
            if (hole[r])
                now_hole -= took[r];
        }
        if (i < r) {
            now -= took[i];
            if (hole[i])
                now_hole -= took[i];
        }
    }
    cout << fixed << setprecision(20) << best << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
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
