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

int n, k, q;
struct Shop {
    int x, t, a, b;

    bool operator<(const Shop &rhs) const {
        return std::tie(x, t, a, b) < std::tie(rhs.x, rhs.t, rhs.a, rhs.b);
    }
};

struct Query {
    int x, type, index;

    bool operator<(const Query &rhs) const {
        return std::tie(x, type, index) < std::tie(rhs.x, rhs.type, rhs.index);
    }
};

const int MAXN = 3e5 + 7;
const int MAXK = 405;
const int INF = 1e9 + 7;
Shop shops[MAXN];
pair<int, int> queries[MAXN];
const int SHOP_OPEN = -1, SHOP_CLOSE = 1, QUERY = 0;
Query scanline[3 * MAXN];

multiset<int> have_small[MAXK];

vector<int> solve_small() {
    vector<int> ans(q);
    for (int i = 0; i < n; i++) {
        scanline[2 * i] = {shops[i].a, SHOP_OPEN, i};
        scanline[2 * i + 1] = {shops[i].b, SHOP_CLOSE, i};
    }
    for (int i = 0; i < q; i++)
        scanline[2 * n + i] = {queries[i].second, QUERY, i};
    sort(scanline, scanline + 2 * n + q);
    for (int i = 0; i < 2 * n + q; i++) {
        const auto &e = scanline[i];
        if (e.type == SHOP_OPEN) {
            const auto &shop = shops[e.index];
            have_small[shop.t].insert(shop.x);
        }
        if (e.type == SHOP_CLOSE) {
            const auto &shop = shops[e.index];
            have_small[shop.t].erase(have_small[shop.t].find(shop.x));
        }
        if (e.type == QUERY) {
            int l = queries[e.index].first;
            ans[e.index] = 0;
            for (int c = 1; c <= k; c++) {
                auto it = have_small[c].lower_bound(l);
                int cur = INF;
                if (it != have_small[c].end())
                    cur = (*it) - l;
                if (it != have_small[c].begin())
                    cur = min(cur, l - (*prev(it)));
                ans[e.index] = max(cur, ans[e.index]);
            }
            if (ans[e.index] == INF)
                ans[e.index] = -1;
        }
    }
    return ans;
}

const int MAXNODE = 2e7 + 7;
struct Node {
    int l = -1, r = -1;
    int mn = -1;
};
Node *nodes = new Node[MAXNODE];
int N = 0;

int new_node() {
    static int nxt = 0;
    return nxt++;
}

int build(int tl, int tr) {
    int now = new_node();
    if (tr - tl == 1)
        return now;
    int tm = (tl + tr) / 2;
    nodes[now].l = build(tl, tm);
    nodes[now].r = build(tm, tr);
    return now;
}

int insert(int v, int tl, int tr, int pos, int x){
    if (pos < tl || pos >= tr)
        return v;
    int nxt = new_node();
    if (tr - tl == 1){
        nodes[nxt].mn = x;
        return nxt;
    }
    int tm = (tl + tr) / 2;
    nodes[nxt].l = insert(nodes[v].l, tl, tm, pos, x);
    nodes[nxt].r = insert(nodes[v].r, tm, tr, pos, x);
    nodes[nxt].mn = min(nodes[nodes[nxt].l].mn, nodes[nodes[nxt].r].mn);
    return nxt;
}

int get(int v, int tl, int tr, int l, int r){
    if (tr <= l || r <= tl)
        return 1e9;
    if (l <= tl && tr <= r)
        return nodes[v].mn;
    int tm = (tl + tr) / 2;
    return min(get(nodes[v].l, tl, tm, l, r), get(nodes[v].r, tm, tr, l, r));
}

vector<int> solve2() {
    vector<int> ans(q);
    vector<int> compress;
    compress.reserve(n + q);
for (int i = 0; i < n; i++)
        compress.push_back(shops[i].x);
    for (int i = 0; i < q; i++)
        compress.push_back(queries[i].first);
    sort(ALL(compress));
    compress.resize(unique(ALL(compress)) - compress.begin());
    vector<vector<int>> enters(SZ(compress));
    for (int i = 0; i < n; i++) {
        shops[i].x = (lower_bound(ALL(compress), shops[i].x) - compress.begin());
        enters[shops[i].x].push_back(i);
        shops[i].t--;
    }

    for (int i = 0; i < q; i++)
        queries[i].first = (lower_bound(ALL(compress), queries[i].first) - compress.begin());

    vector<int> have(SZ(compress));
    int now = build(0, k);
    for (int i = 0; i < SZ(compress); i++){
        for (int x : enters[i])
            now = insert(now, 0, k, shops[x].t, i);
        have[i] = now;
    }
    for (int i = 0; i < q; i++){
        int l = -1, r = INF;
        int pos = queries[i].first;
        while (r - l > 1){
            int mid = l + (r - l) / 2;
            int lx = lower_bound(ALL(compress), compress[pos] - mid) - compress.begin();
            int rx = upper_bound(ALL(compress), compress[pos] + mid) - compress.begin() - 1;
//            cout << mid << ' ' << rx << ' ' << compress[rx] << ' ' << nodes[have[rx]].mn << '\n';
            if (nodes[have[rx]].mn >= lx)
                r = mid;
            else
                l = mid;
        }
        ans[i] = r;
        if (ans[i] >= 100000000)
            ans[i] = -1;
    }
    return ans;
}

int solve() {
    if (!(cin >> n >> k >> q))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> shops[i].x >> shops[i].t >> shops[i].a >> shops[i].b;
    for (int i = 0; i < q; i++)
        cin >> queries[i].first >> queries[i].second;
    vector<int> ans;
    if (n <= 60000 && k <= 400)
        ans = solve_small();
    else
        ans = solve2();
    for (int i = 0; i < q; i++)
        cout << ans[i] << '\n';
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
