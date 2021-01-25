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
const int MAXN = 1e5 + 7;
int arr[MAXN];
vector<int> t[4 * MAXN];

int get(int v, int tl, int tr, int l, int r, int x) { // >= x
    if (r <= tl || tr <= l)
        return 0;
    if (l <= tl && tr <= r) {
        int ans = (int) (lower_bound(ALL(t[v]), x) - t[v].begin());
        return SZ(t[v]) - ans;
    }
    int tm = (tl + tr) / 2;
    return get(v * 2, tl, tm, l, r, x) + get(v * 2, tm, tr, l, r, x);
}

vector<int> get_v(int v, int tl, int tr, int l, int r, int x) {
    if (r <= tl || tr <= l)
        return {};
    if (l <= tl && tr <= r) {
        int pos = (int) (lower_bound(ALL(t[v]), x) - t[v].begin());
        return vector<int>{t[v].begin() + max(pos, SZ(t[v]) - 100), t[v].end()};
    }
    int tm = (tl + tr) / 2;
    vector<int> res_l = get_v(v * 2, tl, tm, l, r, x);
    vector<int> res_r = get_v(v * 2 + 1, tm, tr, l, r, x);
    vector<int> res(SZ(res_l) + SZ(res_r));
    merge(ALL(res_l), ALL(res_r), res.begin());
    if (SZ(res) > 100)
        return vector<int>{res.end() - 100, res.end()};
    return res;
}

double solve_slow(vector<int> have) {
    sort(RALL(have));
    if (SZ(have) == 1) {
        return have[0];
    }
    double now = 2;
    double ans = 0;
    for (int j = 0; j < SZ(have) && j < 100; j++) {
        ans += have[j] / now;
        if (j + 2 != SZ(have))
            now *= 2;
    }
    return ans;
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    int N = 1;
    while (N < n)
        N *= 2;
    for (int i = 0; i < n; i++)
        t[i + N] = {arr[i]};
    for (int i = N - 1; i >= 1; i--){
        t[i].resize(SZ(t[2 * i]) + SZ(t[2 * i + 1]));
        merge(ALL(t[2 * i]), ALL(t[2 * i + 1]), t[i].begin());
    }
    int q;
    cin >> q;
    cout << fixed << setprecision(20);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        --l;
        if (get(1, 0, N, l, r, 0) < 100){
            cout << solve_slow(get_v(1, 0, N, l, r, 0)) << '\n';
            continue;
        }
        int low = 0, high = 1e6 + 1;
        while (high - low > 1){
            int tm = (low + high) / 2;
            if (get(1, 0, N, l, r, tm) >= 100)
                low = tm;
            else
                high = tm;
        }
        cout << solve_slow(get_v(1, 0, N, l, r, low)) << '\n';
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
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
