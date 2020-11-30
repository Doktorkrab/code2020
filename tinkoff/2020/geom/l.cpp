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

    bool operator==(const Vector &oth) const {
        return tie(x, y) == tie(oth.x, oth.y);
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

struct Event {
    int l, index;
};
int n, q;
const int MAXN = 3e5 + 7;
Vector polygon[MAXN];
int poses[MAXN];
int l[MAXN];
int lst[MAXN];
int tree[MAXN];
int ans[MAXN];
vector<Event> events[MAXN];

void add(int pos, int x) {
    for (int r = pos; r < MAXN; r |= r + 1)
        tree[r] += x;
}

int get(int r) {
    int ans = 0;
    for (int i = r; i >= 0; i = (i & (i + 1)) - 1)
        ans += tree[i];
    return ans;
}

int get(int l, int r) {
    return get(r) - get(l - 1);
}

int solve() {
    vector<Vector> have;
    if (!(cin >> n))
        return 1;
    have.reserve(MAXN);
    fill(lst, lst + MAXN, -1);
    int pnt = 0;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        l[i] = pnt;
        for (int j = 0; j < k; j++)
            cin >> polygon[pnt++];
        Vector lst = polygon[pnt - 1];
        for (int j = k - 1; j >= 1; j--) {
            polygon[j + l[i]] = polygon[j + l[i]] - polygon[j + l[i] - 1];
            ll g = gcd(abs(polygon[j + l[i]].x), abs(polygon[j + l[i]].y));
            polygon[j + l[i]].x /= g;
            polygon[j + l[i]].y /= g;
            have.push_back(polygon[j + l[i]]);
        }
        polygon[l[i]] = polygon[l[i]] - lst;
        ll g = gcd(abs(polygon[l[i]].x), abs(polygon[l[i]].y));
        polygon[l[i]].x /= g;
        polygon[l[i]].y /= g;
        have.push_back(polygon[l[i]]);
//        for (int j = 0; j < k; j++)
//            cout << polygon[j + l[i]] << '\n';
//        cout << '\n';
    }
    l[n] = pnt;
    sort(ALL(have));
    have.resize(unique(ALL(have)) - have.begin());
    for (int i = 0; i < pnt; i++)
        poses[i] = (int) (lower_bound(ALL(have), polygon[i]) - have.begin());
//    for (int i = 0; i < n; i++)
//        cout << l[i] << " \n"[i + 1 == n];
//    for (int i = 0; i < pnt; i++)
//        cout << poses[i] << " \n"[i + 1 == pnt];
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l_i, r_i;
        cin >> l_i >> r_i;
        l_i--, r_i--;
        l_i = l[l_i];
        r_i = l[r_i + 1] - 1;
//        cout << "<=>"<< l_i << ' ' << r_i << '\n';
        events[r_i].push_back({l_i, i});
    }
    for (int i = 0; i < pnt; i++) {
        if (lst[poses[i]] != -1)
            add(lst[poses[i]], -1);
        lst[poses[i]] = i;
        add(i, 1);
        for (Event &e : events[i])
            ans[e.index] = get(e.l, i);
    }
    for (int i = 0; i < q; i++)
        cout << ans[i] << '\n';
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
