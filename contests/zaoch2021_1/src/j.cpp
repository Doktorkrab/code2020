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

int n, k;

struct Vector {
    ll x, y;

    Vector() = default;

    Vector(ll x, ll y) : x(x), y(y) {}

    Vector operator-(const Vector &oth) const {
        return {x - oth.x, y - oth.y};
    }

    Vector rotate90() const {
        return {-y, x};
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

struct Line {
    ll a, b, c;
    Vector p1, p2;

    Line() = default;

    Line(const Vector &p1, const Vector &p2) : p1(p1), p2(p2) {
        Vector norm = (p2 - p1).rotate90();
//        cout << '\t' << norm << '\n';
        a = norm.x;
        b = norm.y;
        c = -(a * p1.x + b * p1.y);
    }

    ll dist(const Vector &p) const {
        return a * p.x + b * p.y + c;
    }
};

const int MAXN = 2e5 + 7;
mt19937 rnd('k' + 'e' + 'k' + 'e' + 'k' + 'e' + 1488);
Vector arr[MAXN];

int solve() {
    if (!(cin >> n >> k))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    for (int iter = 0; iter < 6000; iter++) {
        shuffle(arr, arr + n, rnd);
        vector<Line> lines;
        lines.emplace_back(arr[0], arr[1]);
        int prev = -1;
        for (int i = 0; i < n; i++) {
            bool good = false;
            for (int j = 0; j < SZ(lines); j++) {
                Line l = lines[j];
                if (l.dist(arr[i]) == 0) {
                    good = true;
                    break;
                }
            }
            if (!good) {
                if (prev != -1) {
                    lines.emplace_back(arr[prev], arr[i]);
                    prev = -1;
                }
                else
                    prev = i;
            }
            if (SZ(lines) > k)
                break;
        }
        if (prev != -1)
            lines.emplace_back(arr[0], arr[prev]);
        if (SZ(lines) > k)
            continue;
        cout << "Yes\n";
        cout << SZ(lines) << '\n';
        for (auto& l : lines)
            cout << l.p1 << ' ' << l.p2 << '\n';
        return 0;
    }
    cout << "No\n";
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("j.in", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}
