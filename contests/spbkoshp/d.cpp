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
#define int ll
int n, L;

struct Point {
    int x, y;
    Point() : x(0), y(0) {}
    explicit Point(int x, int y) : x(x), y(y) {}
    Point operator-(const Point& oth) const {
        return Point(x - oth.x, y - oth.y);
    }
    Point operator+(const Point& oth) const {
        return Point(x + oth.x, y + oth.y);
    }
    bool operator<(const Point& oth) const {
         return tie(x, y) < tie(oth.x, oth.y);
    }
    bool operator==(const Point& oth) const {
        return tie(x, y) == tie(oth.x, oth.y);
    }

    long double len() const {
        return sqrtl(x * x + y * y);
    }
};
istream& operator>>(istream& is, Point& p){
    is >> p.x >> p.y;
    return is;
}
ostream& operator<<(ostream& os, const Point& p){
    os << p.x << " " << p.y;
    return os;
}

int vector_product(const Point& a, const Point& b){
    return a.x * b.y - a.y * b.x;
}

int scalar_product(const Point& a, const Point& b){
    return a.x * b.x + a.y * b.y;
}

inline int cmp(const Point& a, const Point& b, const Point& c){
    if (vector_product(b - a, c - b) > 0)
        return 1;
    if (vector_product(b - a, c - b) < 0)
        return -1;
    return 0;
}

vector<Point> build_convex_hull(vector<Point> p){
    int n = p.size();
    if (n <= 2)
        return p;
    sort(ALL(p));
    vector<Point> lower{p.begin(), p.begin() + 2};
    for (int i = 2; i < n; i++){
        while (lower.size() >= 2 && cmp(lower[SZ(lower) - 2], lower.back(), p[i]) <= 0)
            lower.pop_back();
        lower.push_back(p[i]);
    }
    lower.pop_back();
    reverse(ALL(p));
    vector<Point> upper(p.begin(), p.begin() + 2);
    for (int i = 2; i < n; i++){
        while (upper.size() >= 2 && cmp(upper[SZ(upper) - 2], upper.back(), p[i]) <= 0)
            upper.pop_back();
        upper.push_back(p[i]);
    }
    upper.pop_back();
    for (auto i : upper)
        lower.push_back(i);
    return lower;
}

int solve() {
    if (!(cin >> n >> L))
        return 1;
    vector<Point> p(n);
    for (Point& i : p)
        cin >> i;
    auto convex_hull1 = build_convex_hull(p);
    vector<Point> have;
    have.reserve(4 * SZ(convex_hull1));
    vector<Point> shift = {Point(-L, 0), Point(L, 0), Point(0, L), Point(0, -L)};
    for (const auto& i : convex_hull1){
        for (const auto &sh : shift)
        have.push_back(i + sh);
    }
    sort(ALL(have));
    have.resize(unique(ALL(have)) - have.begin());
    auto convex_hull2 = build_convex_hull(have);
    convex_hull2.push_back(convex_hull2.front());
    long double ans = 0;
    for (int i = 0; i + 1 < SZ(convex_hull2); i++)
        ans += (convex_hull2[i + 1] - convex_hull2[i]).len();
    cout << setprecision(20) << ' ' << fixed;
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
