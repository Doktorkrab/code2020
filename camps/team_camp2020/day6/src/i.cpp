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

int h, w;
int n;
int q;
const int MAXN = 1e5 + 7;
set<int> l_h[MAXN], r_h[MAXN];
set<int> l_v[MAXN], r_v[MAXN];
int ok = 0;
bool ok_h[MAXN];
bool ok_v[MAXN];

void add(int y, set<int> &ls, set<int> &rs, bool &upd) {
    bool was = upd;
    if (rs.count(y)) {
        rs.erase(y);
    } else
        ls.insert(y);
    if (ls.count(y + 1)) {
        ls.erase(y + 1);
    } else
        rs.insert(y + 1);
    upd = (SZ(ls) == 1);
    if (!was && upd)
        ok++;
    if (was && !upd)
        ok--;
}

inline void upd(int x, int y) {
    add(y, l_h[x], r_h[x], ok_h[x]);
    add(x, l_v[y], r_v[y], ok_v[y]);
}

int solve() {
    if (!(cin >> h >> w >> n))
        return 1;
    for (int i = 0; i < h; i++){
        l_h[i].clear();
        r_h[i].clear();
    }

    for (int i = 0; i < w; i++){
        l_v[i].clear();
        r_v[i].clear();
    }
    ok = h + w;
    fill(ok_h, ok_h + h, 1);
    fill(ok_v, ok_v + w, 1);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        upd(x - 1, y - 1);
    }
    cout << (ok == h + w ? "YES" : "NO") << '\n';
    cin >> q;
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        upd(x - 1, y - 1);
        cout << (ok == h + w ? "YES" : "NO") << '\n';
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("i.in", "r", stdin);
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
