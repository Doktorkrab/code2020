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

    Point() = default;

    Point(ll x, ll y) : x(x), y(y) {}

    Point operator-(const Point &oth) const {
        return Point(x - oth.x, y - oth.y);
    }

    Point operator+(const Point &oth) const {
        return Point(x + oth.x, y + oth.y);
    }

    bool operator<(const Point &oth) const {
        return make_pair(x, y) < make_pair(oth.x, oth.y);
    }

    Point rotate90() const {
        return Point(-y, x);
    }

    Point rotate180() const {
        return Point(-x, -y);
    }

    ll len2() const {
        return x * x + y * y;
    }

    ll dot(const Point &oth) const {
        return x * oth.x + y * oth.y;
    }

    ll cross(const Point &oth) const {
        return x * oth.y - y * oth.x;
    }
};

istream &operator>>(istream &is, Point &p) {
    is >> p.x >> p.y;
    return is;
}

ostream &operator<<(ostream &os, const Point &p) {
    os << p.x << ' ' << p.y;
    return os;
}

int n;
const int MAXN = 1e5 + 7;
Point arr[MAXN];

bool check(int a, int b, int c) {
    Point ab = arr[a] - arr[b];
    Point cb = arr[c] - arr[b];
    if (ab.len2() != cb.len2())
        return false;
    if (ab.dot(cb) != 0)
        return false;
    auto on_seg = [&](const Point &a, const Point &b, const Point &c) {
        return (c - a).dot(b - a) < 0 && (c - a).cross(b - a) == 0;
    };
    for (int i = 0; i < n; i++) {
        if (i == a || i == b || i == c)
            continue;
        if (on_seg(arr[a], arr[b], arr[i]) || on_seg(arr[a], arr[c], arr[i]) || on_seg(arr[b], arr[c], arr[i]))
            return false;
    }
    return true;
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    set<vector<int>> ans;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++) {
                    if (check(i, j, k) && i != j && j != k && k != i) {
                        vector<int> kek = {i, j, k};
                        sort(ALL(kek));
                        ans.insert(kek);
                    }
            }
    }
    cout << SZ(ans) << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
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
