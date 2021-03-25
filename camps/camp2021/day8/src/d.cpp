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

    Vector operator+(const Vector &oth) const {
        return Vector(x + oth.x, y + oth.y);
    }

    Vector operator-(const Vector &oth) const {
        return Vector(x - oth.x, y - oth.y);
    }

    ld len2() const {
        return x * x + y * y;
    }

    ld len() const {
        return sqrtl(len2());
    }

    ld cross(const Vector &oth) const {
        return x * oth.y - oth.x * y;
    }

    ld dot(const Vector &oth) const {
        return x * oth.x + y * oth.y;
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
const ld eps = 1e-15;
const ld INF = 1e18;
bool le(ld a, ld b){
    return a < b || abs(a - b) < eps;
}
ld dist_to_segment(Vector a, Vector b, const Vector &c) {
    if (a.y > b.y)
        swap(a, b);
    if (!(le(a.y, c.y) && le(c.y, b.y)))
        return INF;
    Vector seg = b - a;
    if (abs(seg.y) < eps){
        if (a.x > b.x)
            return (a - c).len();
        return (b - c).len();
    }
    ld k = (c.y - a.y) * 1.L / seg.y;
    Vector d(a.x + seg.x * k, a.y + seg.y * k);
    return abs(a.x + seg.x * k - c.x);
}

const int MAXN = 1e5 + 7;
vector<Vector> arr[MAXN];

ld get_dist(int a, int b) {
    ld max_x = 0;
    for (const Vector &v : arr[a])
        max_x = max(max_x, v.x);
    for (Vector &v : arr[b])
        v.x += max_x;
    ld ans = INF;
    for (int i = 0; i < SZ(arr[a]); i++) {
        for (int j = 0; j < SZ(arr[b]); j++) {
//            cout << i << ' ' << j << ' ' << dist_to_segment(arr[a][i], arr[a][(i + 1) % SZ(arr[a])], arr[b][j]) << ' '
//                 << dist_to_segment(arr[a][i], arr[a][(i + 1) % SZ(arr[a])], arr[b][j]) << '\n';
            ans = min(ans, dist_to_segment(arr[a][i], arr[a][(i + 1) % SZ(arr[a])], arr[b][j]));
            ans = min(ans, dist_to_segment(arr[b][j], arr[b][(j + 1) % SZ(arr[b])], arr[a][i]));
        }
    }

    ld max_x1 = 0;
    for (Vector& v : arr[b]) {
        v.x -= max_x;
        max_x1 = max(v.x, max_x1);
    }
//    cout << "Polygon\n";
//        for (auto x : arr[a])
//            cout << x << '\n';
//        cout << "...\nPolygon\n";
//        for (auto x : arr[b])
//            cout << x + Vector(max_x - ans, 0) << '\n';
//    cout << "...\n";
    return max(max_x + max_x1 - ans, max(max_x, max_x1));
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        arr[i].resize(k);
        for (Vector &v : arr[i])
            cin >> v;
        ld min_x = TMAX(ld);
        for (const Vector &v : arr[i])
            min_x = min(min_x, v.x);
        for (Vector &v :arr[i])
            v.x -= min_x;
    }
    cout << fixed << setprecision(20);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        --a, --b;
//        for (auto x : arr[a])
//            cout << x << '\n';
//        cout << "...\nPolygon\n";
//        for (auto x : arr[b])
//            cout << x << '\n';
//        get_dist(a, b);
//        cout << get_dist(a, b) << '\n';
        cout << min(get_dist(a, b), get_dist(b, a)) << '\n';
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("d.in", "r", stdin);
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
