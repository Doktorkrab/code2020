#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;

#define int ll

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
    int x, y;

    Point() = default;

    Point(int x, int y) : x(x), y(y) {}

    bool operator<(const Point &oth) const {
        return tie(x, y) < tie(oth.x, oth.y);
    }

    bool operator==(const Point &oth) const {
        return !((*this) < oth || oth < (*this));
    }

    Point operator+(const Point &oth) const {
        return Point(x + oth.x, y + oth.y);
    }

    Point operator-(const Point &oth) const {
        return Point(x - oth.x, y - oth.y);
    }
};

istream &operator>>(istream &is, Point &x) {
    is >> x.x >> x.y;
    return is;
}

ostream &operator<<(ostream &os, const Point &x) {
    os << x.x << ' ' << x.y;
    return os;
}

int cross_product(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

int dot_product(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}

inline int cmp(const Point &a, const Point &b, const Point &c) {
    int t = cross_product(b - a, c - b);
    if (t < 0)
        return -1;
    if (t == 0)
        return 0;
    return 1;
}

int n;
const int MAXN = 5e5 + 7;
Point points[MAXN];

vector<Point> build() {
    if (n <= 2) {
        return vector<Point>(points, points + n);
    }
    sort(points, points + n);
    vector<Point> lower{points, points + 2};
    for (int i = 2; i < n; i++) {
        while (SZ(lower) >= 2 && cmp(lower[SZ(lower) - 2], lower.back(), points[i]) < 0)
            lower.pop_back();
        lower.push_back(points[i]);
    }
    lower.pop_back();
    reverse(points, points + n);
    vector<Point> upper{points, points + 2};
    for (int i = 2; i < n; i++) {
        while (SZ(upper) >= 2 && cmp(upper[SZ(upper) - 2], upper.back(), points[i]) < 0)
            upper.pop_back();
        upper.push_back(points[i]);
    }
    upper.pop_back();
    for (auto& i : upper)
        lower.push_back(i);
    return lower;
}

int solve() {
    if (!(cin >> n))
        return 1;
    Point ivan{};
    cin >> ivan;
    for (int i = 0; i < n; i++)
        cin >> points[i];
    points[n++] = ivan;
    auto ans = build();
    bool good = 0;
    for (auto p : ans)
        good |= (p == ivan);
    if (good)
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
