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

struct Point {
    ll x, y;

    Point() : x(0), y(0) {}

    Point(int _x, int _y) : x(_x), y(_y) {}

    bool operator<(const Point &point) const {
        return tie(x, y) < tie(point.x, point.y);
    }

    ll vector_product(const Point &o) const {
        return x * o.y - y * o.x;
    }

    ll scalar_product(const Point &o) const {
        return x * o.x + y * o.y;
    }

    ll len2() const {
        return x * x + y + y;
    }

    double len() const {
        return sqrt(len2());
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

    friend ostream &operator<<(ostream &os, const Point &point) {
        os << point.x << " " << point.y;
        return os;
    }

    friend istream &operator>>(istream &is, Point &p) {
        is >> p.x >> p.y;
        return is;
    }
};

int n, m, k;
const int MAXN = 1e5 + 7;
Point polygon[MAXN];

bool is_inside(Point &point) {
    if (polygon[1].vector_product(point) < 0 || point.vector_product(polygon[n - 1]) < 0)
        return false;
    if (polygon[1].vector_product(point) == 0)
        return point.len2() <= polygon[1].len2();
    if (polygon[n - 1].vector_product(point) == 0)
        return point.len2() <= polygon[n - 1].len2();

    int l = 1, r = n - 1;
    while (r - l > 1) {
        int M = (l + r) / 2;
        if (polygon[M].vector_product(point) >= 0)
            l = M;
        else
            r = M;
    }
    Point p1 = polygon[l] + polygon[0];
    Point p2 = polygon[l + 1] + polygon[0];
    Point p12 = p2 - p1;
    Point p23 = point + polygon[0] - p1;
    return p12.vector_product(p23) >= 0;
}

int solve() {
    if (!(cin >> n >> m >> k))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> polygon[i];
    rotate(polygon, min_element(polygon, polygon + n), polygon + n);
    for (int i = 1; i < n; i++)
        polygon[i] -= polygon[0];
    int ans = 0;
    for (int i = 0; i < m; i++) {
        Point check;
        cin >> check;
        check -= polygon[0];
        if (is_inside(check))
            ans++;
    }
    if (ans >= k)
        cout << "YES\n";
    else
        cout << "NO\n";
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
