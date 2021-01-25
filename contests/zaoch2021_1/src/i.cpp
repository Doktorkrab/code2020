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
const int MAXC = 1e6 + 7;

struct Edge {
    int u, w, id;

    Edge() = default;

    Edge(int a, int b, int c) : u(a), w(b), id(c) {}

    bool operator<(const Edge &oth) const {
        return w < oth.w;
    }
};

vector<Edge> g[MAXN];
Edge edges[MAXN];
ll ans = 0;

void dfs_super_slow(int v, int now, int p = -1) {
//    cout << v + 1 << " " << now << '\n';
    ans += now;
    for (auto[u, w, _] : g[v]) {
        if (u == p)
            continue;
        ll nxt = gcd(w, now);
        dfs_super_slow(u, nxt, v);
    }
}

void stupid() {
    for (int i = 0; i < n; i++) {
        dfs_super_slow(i, 0, -1);
    }
}

int sz[MAXN], p[MAXN];

int find_set(int x) {
    if (x == p[x])
        return x;
    return p[x] = find_set(p[x]);
}

void un(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a == b)
        return;
    if (sz[a] > sz[b])
        swap(a, b);
    p[a] = b;
    sz[b] += sz[a];
}

void solve_primes() {
    ans = 1LL * n * (n - 1);
    iota(p, p + n, 0);
    fill(sz, sz + n, 1);
    for (int i = 0; i < n; i++) {
        sort(ALL(g[i]));
        for (int j = 1; j < SZ(g[i]); j++) {
            if (g[i][j - 1].w == g[i][j].w)
                un(g[i][j - 1].id, g[i][j].id);
        }
    }
    for (int i = 0; i + 1 < n; i++)
        if (find_set(i) == i) {
            ans += 1LL * sz[i] * (sz[i] + 1) * (edges[i].w - 1);
        }
}

ll cnt_ans[MAXC];
int cnt[MAXC];
int cnt1[MAXC];

void solve_bush() {
    cerr << "bush\n";
    for (auto[u, w, _] : g[0])
        cnt[w]++;
    for (int i = 1; i < MAXC; i++)
        for (int j = 1; i * j < MAXC; j++)
            cnt1[i] += cnt[i * j];
    for (int i = MAXC - 1; i >= 1; i--) {
        cnt_ans[i] = 1LL * (cnt1[i] + 1) * cnt1[i];
        for (int j = 2; i * j < MAXC; j++)
            cnt_ans[i] -= cnt_ans[i * j];
        ans += cnt_ans[i] * i;
    }
}


bool can_use[MAXN];
bool used[MAXN];

int dfs_small(int v, int p) {
    int now = 1;
    used[v] = true;
    for (auto[u, w, id] : g[v]) {
        if (u == p || !can_use[id])
            continue;
        now += dfs_small(u, v);
    }
    return now;
}

const int SMALL_C = 505;

void solve_small() {
    for (int x = SMALL_C; x >= 1; x--) {
        for (int i = 0; i + 1 < n; i++) {
            can_use[i] = (edges[i].w % x == 0);
        }
        int kek;
        fill(used, used + n, 0);
        for (int i = 0; i < n; i++)
            if (!used[i]) {
                kek = dfs_small(i, -1);
                cnt_ans[x] += 1LL * kek * (kek - 1);
            }
        for (int i = 2; i * x < SMALL_C; i++) {
            cnt_ans[x] -= cnt_ans[i * x];
        }
        ans += 1LL * cnt_ans[x] * x;
    }
}

struct Segment {
    int g = 0;
    ll sum = 0;

    Segment() = default;

    Segment(int g, ll sum) : g(g), sum(sum) {}
};

void solve_bamboo() {
    cerr << "bamboo\n";
    int n = ::n - 1;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = edges[i].w;
    ans = 0;
    vector<Segment> have;
    for (int i = 0; i < n; i++){
        vector<Segment> now = {Segment(arr[i], 1)};
        reverse(ALL(have));
        for (Segment& seg : have){
            ll g = gcd(seg.g, now.back().g);
            if (g == now.back().g)
                now.back().sum += seg.sum;
            else{
                seg.g = g;
                now.push_back(seg);
            }
        }
        reverse(ALL(now));
        swap(now, have);
        for (Segment& seg : have) {
//            cout << seg.g << ' ' << seg.sum << '\n';
            ans += seg.sum * seg.g;
        }
    }
    ans *= 2;
}

int solve() {
    if (!(cin >> n))
        return 1;
    ans = 0;
    for (int i = 0; i < n; i++)
        g[i].clear();
    bool is_bush = true;
    bool is_bamboo = true;
    bool is_small = true;
    for (int i = 0; i + 1 < n; i++) {
        int v, u, w;
        cin >> v >> u >> w;
        --v, --u;
        edges[i] = {u, w, i};
        g[v].emplace_back(u, w, i);
        g[u].emplace_back(v, w, i);
//        cerr << v << ' ' << u << '\n';
        is_bush &= (v == 0 && u == i + 1);
        is_bamboo &= (v == i && u == i + 1);
        is_small &= (w <= 500);
    }
    if (is_bush)
        solve_bush();
    else if (is_bamboo)
        solve_bamboo();
    else if (n <= 3000)
        stupid();
    else if (is_small)
        solve_small();
    else
        solve_primes();
//    solve_small();
    cout << ans << '\n';
    ans = 0;
//    stupid();
//    cout << ans << '\n';
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
