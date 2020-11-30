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

    ll operator^(const Vector &oth) const {
        return x * oth.y - oth.x * y;
    }

    ll operator*(const Vector &oth) const {
        return x * oth.x + y * oth.y;
    }

    bool operator<(const Vector &oth) const {
        if (x == oth.x)
            return y < oth.y;
        return x < oth.x;
    }

    Vector operator+(const Vector &oth) const {
        return {x + oth.x, y + oth.y};
    }

    Vector operator-(const Vector &oth) const {
        return {x - oth.x, y - oth.y};
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

bool cmp(const Vector &a, const Vector &b, const Vector &c) {
    return ((b - a) ^ (c - a)) >= 0;
}

int solve() {
    if (!(cin >> n))
        return 1;
    vector<Vector> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i].y -= p[i].x * p[i].x;
    }
    sort(ALL(p));
    vector<Vector> st;
    for (Vector v : p) {
        while (!st.empty() && st.back().x == v.x)
            st.pop_back();
        while (SZ(st) > 1 && cmp(st[SZ(st) - 2], st.back(), v))
            st.pop_back();
        st.push_back(v);
    }
    cout << SZ(st) - 1 << '\n';
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
