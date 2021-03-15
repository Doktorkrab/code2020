#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx")
#pragma GCC optimize "-O3"

#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;
using ull = unsigned long long;

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

const int OPEN = -1, CLOSE = 1;

struct Event {
    int pos, type, l;

    bool operator<(const Event &rhs) const {
        return std::tie(pos, type, l) < std::tie(rhs.pos, rhs.type, rhs.l);
    }
};

int t, k, m;
const int MAXN = 2e3 + 7;
const int MAXN1 = 5e5 + 7;
const int BASE = 239;
const ull MOD = 1e9 + 33;
const int INF = 1e9;
string have[MAXN];
vector<ull> hashes[MAXN];
vector<ull> rev_hashes[MAXN];
ull bases[MAXN1];
vector<Event> events[MAXN1];

void build_hash(int index) {
    int n = SZ(have[index]);
    auto &hsh = hashes[index];
    auto &rhsh = rev_hashes[index];
    hsh.resize(n + 1);
    rhsh.resize(n + 1);
    for (int i = 0; i < n; i++)
        hsh[i + 1] = (hsh[i] * BASE % MOD + have[index][i]) % MOD;
    reverse(ALL(have[index]));
    for (int i = 0; i < n; i++)
        rhsh[i + 1] = (rhsh[i] * BASE % MOD + have[index][i]) % MOD;
    reverse(ALL(have[index]));
}

ull get_hash(int x, int l, int r) {
    if (l == r)
        return 0;
    return (hashes[x][r] + MOD - hashes[x][l] * bases[r - l] % MOD) % MOD;
}

ull get_rev_hash(int x, int l, int r) {
    if (l == r)
        return 0;
    auto &rh = rev_hashes[x];
    int l1 = SZ(have[x]) - r;
    int r1 = SZ(have[x]) - l;
    return (rh[r1] + MOD - rh[l1] * bases[r1 - l1] % MOD) % MOD;
}


bool can[MAXN][MAXN];
int dp[MAXN];
int p[MAXN];
int mx[MAXN1];

void precalc_events() {
    for (int i = 0; i < m; i++)
        events[i].clear(), mx[i] = 0;
    for (int i = 0; i < m; i++) {
        int l = 0, r = min((m - i), i) + 1;
        cout << i << ' ' << l << ' ' << r << '\n';
        while (r - l > 1) {
            int mid = (l + r) / 2;
            int len = mid;
            unordered_set<ull> now;
            for (int x = 0; x < k; x++) {
                if (i + len + 1 > SZ(have[x]))
                    break;
                now.insert(get_hash(x, i - len + 1, i + len + 1));
            }
            bool was = false;
            for (int x = 0; x < k; x++) {
                if (i + len + 1 > SZ(have[x]))
                    break;
                if (now.count(get_rev_hash(x, i - len + 1, i + len + 1))) {
                    was = true;
                    break;
                }
            }
            if (was)
                l = mid;
            else
                r = mid;
        }
        mx[i - l / 2] = max(mx[i - l / 2], 2 * l);
        l = 0, r = min((m - i), i) + 1;
        while (r - l > 1) {
            int mid = (l + r) / 2;
            int len = mid;
            unordered_set<ull> now;
            for (int x = 0; x < k; x++) {
                if (i + len > SZ(have[x]))
                    break;
                now.insert(get_hash(x, i - len + 1, i + len));
            }
            bool was = false;
            for (int x = 0; x < k; x++) {
                if (i + len > SZ(have[x]))
                    break;
                if (now.count(get_rev_hash(x, i - len + 1, i + len))) {
                    was = true;
                    break;
                }
            }
            if (was)
                l = mid;
            else
                r = mid;
        }
        mx[i - l / 2] = max(mx[i - l / 2], 2 * l + 1);
    }
    for (int i = 0; i < m; i++) {

        events[i].push_back({i, OPEN, mx[i]});
        events[i + mx[i]].push_back({i, CLOSE, mx[i]});
    }
    for (int i = 0; i < m; i++) {
        cout << mx[i] << " \n"[i + 1 == m];
    }
}

int solve() {
    if (!(cin >> t >> k >> m))
        return 1;
//    assert(t < 2);
    for (int i = 0; i < k; i++) {
        cin >> have[i];
    }
    sort(have, have + k, [&](const string &a, const string &b) {
        return SZ(a) > SZ(b);
    });
    for (int i = 0; i < k; i++)
        build_hash(i);

    fill(dp, dp + m + 1, INF);
    fill(p, p + m + 1, -1);
    dp[0] = 0;
    /*for (int i = 0; i < m; i++) {
        if (dp[i] >= INF)
            continue;
        for (int j = i + 1; j <= m; j++) {
            unordered_set<ull> now;
            for (int x = 0; x < k; x++) {
                if (SZ(have[x]) < j)
                    break;
                now.insert(get_hash(x, i, j));
            }
            for (int x = 0; x < k; x++) {
                if (SZ(have[x]) < j)
                    break;
                if (now.count(get_rev_hash(x, i, j))) {
                    can[i][j] = true;
                    break;
                }
            }
            if (can[i][j] && dp[j] > dp[i] + 1) {
                dp[j] = dp[i] + 1;
                p[j] = i;
            }
        }
    }*/
    precalc_events();
    set<Event> opened;
    for (int i = 0; i < m; i++) {
        int j = i + 1;
        if (dp[j] > dp[i] + 1) {
            dp[j] = dp[i] + 1;
            p[j] = i;
        }
        for (Event &e : events[i]) {
            if (e.type == OPEN)
                opened.insert(e);
            else {
                e.type = OPEN;
                opened.erase(e);
            }
        }
        for (const Event &e : opened) {
            j = e.pos + (e.l - (i - e.pos) - 1) + 1;
            if (dp[j] > dp[i] + 1) {
                dp[j] = dp[i] + 1;
                p[j] = i;
            }
        }
    }
    cout << dp[m] << '\n';
    vector<int> ans;
    int now = m;
    while (p[now] != 0) {
        ans.push_back(p[now]);
        now = p[now];
    }
    reverse(ALL(ans));
    for (int x : ans)
        cout << x << ' ';
    cout << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("this_gonna_be_hurt.in", "r", stdin);
#endif
    bases[0] = 1;
    for (int i = 1; i < MAXN1; i++)
        bases[i] = bases[i - 1] * BASE % MOD;
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
