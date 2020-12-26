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
const ld EPS = 1e-9;

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
        return sqrtl(x * x + y * y);
    }

    Vector rotate90() const {
        return {-y, x};
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

    Vector intersect(const Line &oth) const {
        return Vector((b * oth.c - c * oth.b) / (oth.b * a - b * oth.a),
                      (c * oth.a - oth.c * a) / (oth.b * a - b * oth.a));
    }
};

struct MergeSortTree {
    struct Node {
        vector<int> have;

        Node() = default;

        Node(vector<int> &x) : have(x) {}

        Node(const Node &a, const Node &b) {
            have.resize(SZ(a.have) + SZ(b.have));
            merge(ALL(a.have), ALL(b.have), have.begin());
        }
    };

    Node *t;
    int N = 1;

    MergeSortTree() {}

    MergeSortTree(int sz, vector<int> *have) {
        while (N < sz)
            N *= 2;
        t = new Node[2 * N];
        for (int i = 0; i < sz; i++) {
            sort(ALL(have[i]));
            t[i + N] = have[i];
        }
        for (int i = N - 1; i >= 1; i--)
            t[i] = Node(t[2 * i], t[2 * i + 1]);
    }

    bool get(int v, int tl, int tr, int xl, int xr, int yl, int yr) {
        if (tr <= xl || xr <= tl)
            return false;
        if (xl <= tl && tr <= xr) {
            int pos = (int) (lower_bound(ALL(t[v].have), yl) - t[v].have.begin());
            int pos1 = (int) (lower_bound(ALL(t[v].have), yr) - t[v].have.begin());
            return pos < pos1;
        }
        int tm = (tl + tr) / 2;
        return get(v * 2, tl, tm, xl, xr, yl, yr) || get(v * 2 + 1, tm, tr, xl, xr, yl, yr);
    }

    bool get(int xl, int xr, int yl, int yr) {
        return get(1, 0, N, xl, xr, yl, yr);
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

int n, q;
const int MAXN = 1e5 + 7;
Vector points[MAXN];
pair<int, int> pp[MAXN];
vector<int> have[MAXN];

void solve_square() {
    vector<int> x_cmp(n + 1);
    vector<int> y_cmp(n + 1);
    for (int i = 0; i < n; i++)
        x_cmp[i] = pp[i].first, y_cmp[i] = pp[i].second;
    x_cmp[n] = 1e8;
    y_cmp[n] = 1e8;
    sort(ALL(x_cmp));
    x_cmp.resize(unique(ALL(x_cmp)) - x_cmp.begin());
    sort(ALL(y_cmp));
    y_cmp.resize(unique(ALL(y_cmp)) - y_cmp.begin());
    for (int i = 0; i < n; i++) {
        int x = (int) (lower_bound(ALL(x_cmp), pp[i].first) - x_cmp.begin());
        int y = (int) (lower_bound(ALL(y_cmp), pp[i].second) - y_cmp.begin());
        have[x].push_back(y);
    }
    MergeSortTree mst(SZ(x_cmp), have);
    for (int i = 0; i < q; i++) {
        int type;
        cin >> type;
        assert(type == 2);
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2)
            swap(x1, x2);
        if (y1 > y2)
            swap(y1, y2);
        x1 = (int) (lower_bound(ALL(x_cmp), x1) - x_cmp.begin());
        x2 = (int) (upper_bound(ALL(x_cmp), x2) - x_cmp.begin());
        y1 = (int) (lower_bound(ALL(y_cmp), y1) - y_cmp.begin());
        y2 = (int) (upper_bound(ALL(y_cmp), y2) - y_cmp.begin());
        cout << (mst.get(x1, x2, y1, y2) ? "Yes" : "No") << '\n';
    }

}

int solve() {
    if (!(cin >> n >> q))
        return 1;
    for (int i = 0; i < n; i++) {
        cin >> pp[i].first >> pp[i].second;
        points[i] = Vector(pp[i].first, pp[i].second);
    }
    if (n > 1000) {
        solve_square();
        return 0;
    }
    for (int i = 0; i < q; i++) {
        int type;
        Vector a, b;
        cin >> type >> a >> b;
        bool good = false;
        if (type == 1) {
            Line l(a, b);
            for (int j = 0; j < n; j++) {
                if (l(points[j]) < EPS) {
                    good = true;
                    break;
                }
            }
        } else if (type == 2) {
            vector<Vector> square(4);
            square[0] = a;
            square[2] = b;
            Vector ab = (b - a) / 2.;
            Vector mid = (a + b) / 2.;
            square[1] = mid + ab.rotate90();
            square[3] = mid - ab.rotate90();
            good = false;
            for (int j = 0; j < n; j++) {
                bool was = false;
                for (int k = 0; k < 4; k++) {
                    ld now = (square[(k + 1) % 4] - square[k]) ^(points[j] - square[k]);
                    if (fabs(now) < EPS) {
                        was = true;
                        if (((points[j] - square[k]).len() < (square[(k + 1) % 4] - square[k]).len() ||
                             fabs((points[j] - square[k]).len() - (square[(k + 1) % 4] - square[k]).len()) < EPS) &&
                            (square[(k + 1) % 4] - square[k]) * (points[j] - square[k]) > -EPS)
                            good = true;
                        else
                            good = false;
                        break;
                    }
                }
                if (was) {
                    if (good)
                        break;
                    continue;
                }
//                cerr << j << ' ' << points[j] << '\n';
                ld sign = (square[1] - square[0]) ^(points[j] - square[0]);
                good = true;
                for (int k = 1; k < 4; k++) {
                    ld now = (square[(k + 1) % 4] - square[k]) ^(points[j] - square[k]);
                    if (sign * now < EPS) {
                        good = false;
                        break;
                    }
                }
                if (good)
                    break;
            }
        }
        if (good)
            cout << "Yes\n";
        else
            cout << "No\n";
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
