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

int n;

struct Vector {
    ll x, y;

    Vector operator-(const Vector &oth) const {
        return {x - oth.x, y - oth.y};
    }

    Vector operator+(const Vector &oth) const {
        return {x + oth.x, y + oth.y};
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

ll trap_square(const Vector &a, const Vector &b) {
    return 1LL * (a.y + b.y) * (b.x - a.x);
}

ll square(const vector<Vector> &polygon) {
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        Vector now = polygon[i];
        Vector nxt = polygon[(i + 1) % n];
        ans += trap_square(now, nxt);
    }
    return ans;
}

int solve() {
    if (!(cin >> n))
        return 1;
    vector<Vector> polygon(n);
    for (Vector &v : polygon)
        cin >> v;
    ll sq = square(polygon);
    sq += 2 + n;
    for (int i = 0; i < n; i++) {
        Vector now = polygon[i];
        Vector nxt = polygon[(i + 1) % n];
        sq -= 1 + gcd(abs(nxt.x - now.x), abs(nxt.y - now.y));
    }
    cout << sq / 2 << '\n';
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
