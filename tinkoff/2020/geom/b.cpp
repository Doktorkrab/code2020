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

struct Vector {
    ll x, y;

    ll operator^(const Vector &oth) const {
        return x * oth.y - oth.x * y;
    }

    ll operator*(const Vector &oth) const {
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
};

istream &operator>>(istream &is, Vector &x) {
    is >> x.x >> x.y;
    return is;
}

ostream &operator<<(ostream &os, const Vector &x) {
    os << x.x << ' ' << x.y;
    return os;
}

int n;
string have;
const int MAXN = 2e3 + 7;
Vector points[MAXN];
int ans[MAXN];
bool used[MAXN];

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> points[i];
    cin >> have;
    int pos = (int) (min_element(points, points + n) - points);
    ans[0] = pos;
    used[pos] = true;
    for (int i = 0; i + 1 < n; i++) {
        int now = -1;
        for (int j = 0; j < n; j++) {
            if (used[j])
                continue;
            if (now == -1) {
                now = j;
                continue;
            }
            if (have[i] == 'L' && ((points[j] - points[ans[i]]) ^ (points[now] - points[ans[i]])) > 0)
                now = j;
            if (have[i] == 'R' && ((points[j] - points[ans[i]]) ^ (points[now] - points[ans[i]])) < 0)
                now = j;
        }
        used[now] = 1;
        ans[i + 1] = now;
    }
    for (int i = 0; i < n; i++)
        cout << ans[i] + 1 << " \n"[i + 1 == n];
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
