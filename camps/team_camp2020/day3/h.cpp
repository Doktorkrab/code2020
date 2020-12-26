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

struct Rollback {
    int pa, pb, par, sz, is_good, len;
};
int n, m, k;
const int MAXN = 5e5 + 7;
int p[MAXN];
int sz[MAXN];
int len[MAXN];
bool is_good[MAXN];
vector<int> g[MAXN];
vector<pair<int, int>> g1[MAXN];
int color[MAXN];
int leader[MAXN];
bool bibibi[MAXN];
vector<Rollback> roll_back;

pair<int, bool> get(int v) {
    if (p[v] == v)
        return make_pair(p[v], false);
    auto par = get(p[v]);
    par.second = (par.second + len[v]) % 2;
    return par;
}

void un(int a, int b, bool is_rollback = 0) {
    auto[pa, la] = get(a);
    auto[pb, lb] = get(b);
    if (pa == pb) {
        if (is_rollback)
            roll_back.push_back({pa, pa, p[pa], sz[pa], is_good[pa], len[pa]});
        if (la == lb) {
            is_good[pa] = false;
        }
        return;
    }
    if (sz[pa] > sz[pb])
        swap(pa, pb);
    if (is_rollback)
        roll_back.push_back({pa, pb, p[pa], sz[pb], is_good[pb], len[pa]});
    p[pa] = pb;
    sz[pb] += sz[pa];
    is_good[pb] &= is_good[pa];
    len[pa] = (la + lb + 1) % 2;
}

bool is_bi(int v) {
    if (v == -1)
        return true;
    return is_good[get(v).first];
}

void do_rollback() {
    assert(SZ(roll_back));
    auto[pa, pb, pp, ss, gg, ln] = roll_back.back();
    roll_back.pop_back();
    p[pa] = pp;
    sz[pb] = ss;
    is_good[pb] = gg;
    len[pa] = ln;
}

int solve() {
    if (!(cin >> n >> m >> k))
        return 1;
    fill(leader, leader + k, -1);
    fill(bibibi, bibibi + k, 1);
    for (int i = 0; i < n; i++) {
        cin >> color[i];
        color[i]--;
        p[i] = i;
        sz[i] = 1;
        is_good[i] = true;
        if (leader[color[i]] == -1)
            leader[color[i]] = i;
    }
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
        if (color[v] == color[u])
            un(v, u);
        if (!is_bi(v))
            bibibi[color[v]] = false;
        if (!is_bi(u))
            bibibi[color[u]] = false;
    }
    int bi = 0;
    for (int i = 0; i < k; i++) {
        bi += bibibi[i];
    }
    for (int i = 0; i < n; i++) {
        if (!bibibi[color[i]])
            continue;
        for (int v : g[i]) {
//            cout << v << " " << i << ' ' << color[v] << ' ' << color[i] << '\n';
            if (bibibi[color[v]] && color[v] != color[i]) {
                g1[color[i]].emplace_back(i, v);
                g1[color[v]].emplace_back(v, i);
            }
        }
    }
    for (int i = 0; i < k; i++) {
        sort(ALL(g1[i]),
             [&](const pair<int, int> &a, const pair<int, int> &b) { return color[a.second] < color[b.second]; });
    }
    ll ans = 1LL * bi * (bi - 1) / 2;
//    cout << ans << '\n';
    for (int i = 0; i < k; i++) {
        int now = 0;
        if (!bibibi[i])
            continue;
        while (now < SZ(g1[i])) {
            int cnt = 0;
            int c = color[g1[i][now].second];
            bool ok = bibibi[c];
            if (!ok || c < i) {
                while (now < SZ(g1[i]) && c == color[g1[i][now].second])
                    now++;
                continue;
            }
            bool good = true;
            while (now < SZ(g1[i]) && c == color[g1[i][now].second]) {
                un(g1[i][now].first, g1[i][now].second, true);
                if (!is_bi(g1[i][now].first) || !is_bi(g1[i][now].second))
                    good = false;
                now++;
                cnt++;
            }
            if (!good)
                ans--;
            for (int j = 0; j < cnt; j++)
                do_rollback();
        }
    }
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
