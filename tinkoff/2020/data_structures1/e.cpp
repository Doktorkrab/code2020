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

int n, d;
const int MAXLOG = 16;
const int MAXN = (1 << (MAXLOG));
const int MAXM = 3e5 + 7;
const ll INF = 1e18;
int logn = 0;
vector<ll> dst[MAXN + 7];
ll have[3][MAXN + 7];
vector<ll> neutral;
vector<pair<pair<int, int>, int>> queries[MAXLOG];
ll ans[MAXM];

vector<ll> f(int pos, const vector<ll> &b) {
    vector<ll> res(d, -INF);
    for (int cur = 0; cur < 3; cur++)
        for (int x = 0; x < d; x++) {
            ll xx = (x + have[cur][pos]) % d;
            res[xx] = max(res[xx], have[cur][pos] + b[x]);
        }
    return res;
}

ll f(const vector<ll> &a, const vector<ll> &b) {
    ll ret = max(a[0] + b[0], -1LL);
    for (int i = 1; i < d; i++)
        ret = max(ret, a[i] + b[d - i]);
    return ret;
}

void build() {
    for (int lvl = 0; lvl < MAXLOG; lvl++) {
        for (int block = 0; block < (1 << lvl); ++block) {
            int l = block << (MAXLOG - lvl);
            int r = min(MAXN, (block + 1) << (MAXLOG - lvl));
            int m = (l + r) / 2;
            dst[m] = vector<ll>(d, -INF);
            for (int i = 0; i < 3; i++) {
                ll dm = (have[i][m]) % d;
                dst[m][dm] = max(dst[m][dm], have[i][m]);
            }
            for (int i = m + 1; i < r; i++)
                dst[i] = f(i, dst[i - 1]);
            if (m - 1 >= 0) {
                dst[m - 1] = vector<ll>(d, -INF);
                for (int i = 0; i < 3; i++) {
                    ll dm = (have[i][m - 1]) % d;
                    dst[m - 1][dm] = max(dst[m - 1][dm], have[i][m - 1]);
                }
                for (int i = m - 2; i >= l; i--)
                    dst[i] = f(i, dst[i + 1]);
            }
        }
        for (auto[ends, i] : queries[lvl]) {
            auto[l, r] = ends;
            ans[i] = f(dst[l], dst[r]);
        }
    }
}

void query(int l, int r, int index) {
    if (l == r) {
        ll res = -INF;
        for (int i = 0; i < 3; i++)
            if (have[i][l] % d == 0)
                res = max(have[i][l], res);
        ans[index] = res;
        return;
    }
    int t = 31 - __builtin_clz(l ^ r);
    int level = MAXLOG - t - 1;
    queries[level].emplace_back(make_pair(l, r), index);
}

int solve() {
    if (!(cin >> n >> d))
        return 1;
    assert(logn < MAXLOG);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> have[j][i];
//            cerr << have[j][i] << " \n"[j == 2];
        }
    }
    neutral = vector<ll>(d, -INF);
    neutral[0] = 0;
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        query(l - 1, r - 1, i);
    }
    build();
    for (int i = 0; i < m; i++)
        cout << max(-1LL, ans[i]) << '\n';
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
    }
}
