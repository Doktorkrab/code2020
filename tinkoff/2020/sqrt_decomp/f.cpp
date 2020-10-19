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

int n, q;
const int MAXN = 4e5 + 7;
struct Edge {
    int index;
    int to;
};

struct Query {
    int l, r, index;
};

vector<Edge> g[MAXN];
int euler[4 * MAXN];
bool used[MAXN];
int pnt = 0;
int cost[MAXN];
int tin[MAXN], tout[MAXN];
int ans[MAXN];
Query queries[MAXN];

void dfs(int v, int p = -1) {
    tin[v] = pnt;
    for (auto[ind, u] : g[v]) {
        if (u == p)
            continue;
        euler[pnt++] = ind;
        dfs(u, v);
        euler[pnt++] = ind;
    }
    tout[v] = pnt;
}

const int BLOCK = 322;

struct Sqrt_Decomposition {
    int blocks[MAXN];
    int cnt[MAXN];

    Sqrt_Decomposition() = default;

    void insert(int x) {
        x = euler[x];
        int who = 1 - 2 * used[x];
        used[x] ^= 1;
        x = cost[x];
        if (cnt[x] == 1 && who == -1)
            blocks[x / BLOCK]--;
        if (cnt[x] == 0 && who == 1)
            blocks[x / BLOCK]++;
        cnt[x] += who;
    }

    int get() {
        for (int block = 0; block < MAXN; block++)
            if (blocks[block] != BLOCK) {
                for (int j = 0; j < BLOCK; j++)
                    if (cnt[j + block * BLOCK] == 0) {
                        return block * BLOCK + j;
                    }
            }
        assert(0);
    }
};

int solve() {
    if (!(cin >> n >> q))
        return 1;
    for (int i = 1; i < n; i++) {
        int v, u, w;
        cin >> v >> u >> w;
        --v, --u;
        cost[i - 1] = min(w, MAXN / 2);
        g[v].push_back({i - 1, u});
        g[u].push_back({i - 1, v});
    }
    dfs(0);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        --l, --r;
        queries[i] = {tin[l], tout[r], i};
    }
    sort(queries, queries + q, [&](const Query &a, const Query &b) {
        if (a.l / BLOCK != b.l / BLOCK)
            return a.l < b.l;
        if ((a.l / BLOCK) & 1)
            return a.r > b.r;
        return a.r < b.r;
    });

    Sqrt_Decomposition decomposition{};
    int l = 0, r = 0;
    for (int i = 0; i < q; i++) {
        auto qe = queries[i];
        while (r < qe.r)
            decomposition.insert(r++);
        while (r > qe.r)
            decomposition.insert(--r);
        while (l < qe.l)
            decomposition.insert(l++);
        while (l > qe.l)
            decomposition.insert(--l);
        ans[queries[i].index] = decomposition.get();
    }
    for (int i = 0; i < q; i++)
        cout << ans[i] << " \n"[i + 1 == q];
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
