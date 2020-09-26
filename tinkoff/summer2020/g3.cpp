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

const int MAXN = 2e5 + 7;
const int BIG = 322;
struct SegmentTree{
    int st[4 * MAXN];
    SegmentTree() {}
    int N;
    SegmentTree(int size) {
        N = 1;
        while (N < size) N *= 2;
        fill(st, st + 2 * N, TMAX(int));
    }
    int get(int v, int tl, int tr, int l, int r){
        //cerr << v << ' ' << tl << ' ' << tr << ' ' << l << ' ' << r << '\n';
        if (tr <= l || r <= tl)
            return TMAX(int);
        if (l <= tl && tr <= r)
            return st[v];
        int tm = (tl + tr) / 2; 
        return min(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
    }
    int get(int l, int r){
        return get(1, 0, N, l, r);
    }
    void insert(int v, int tl, int tr, int pos, int x){
        //cerr << tl << ' ' << tr << ' ' << pos << ' ' << x << '\n';
        if (pos < tl || tr <= pos)
            return;
        if (tr - tl == 1){
            st[v] = x;
            return;
        }
        int tm = (tl + tr) / 2; 
        insert(v * 2, tl, tm, pos, x);
        insert(v * 2 + 1, tm, tr, pos, x);
        st[v] = min(st[2 * v], st[2 * v + 1]);
    }
    void insert(int pos, int x){
        insert(1, 0, N, pos, x);
    }
};

int n, m, d, q;
vector<pair<int, int>> g[MAXN];
vector<pair<int, int>> g_big[MAXN];
int is_big[MAXN];
int color[MAXN];
vector<SegmentTree> big_seg;
vector<vector<multiset<int>>> big_set;
int solve() {
    if (!(cin >> n >> m >> d >> q))
        return 1;
    for (int i = 0; i < m; i++){
        int v, u, c;
        cin >> v >> u >> c;
        --v, --u;
        g[v].push_back({u, c});
        g[u].push_back({v, c});
    }
    vector<int> bigs;
    fill(is_big, is_big + n, -1);
    for (int i = 0; i < n; i++){
        if (SZ(g[i]) >= BIG){
            is_big[i] = SZ(bigs);
            bigs.push_back(i);
        }
    }
    int big_cnt = SZ(bigs);
    big_seg.resize(big_cnt, SegmentTree(d));
    big_set.resize(big_cnt, vector<multiset<int>>(d));

    for (int i = 0; i < n; i++){
        cin >> color[i];
        color[i]--;
    }

    for (int i = 0; i < big_cnt; i++){
        int v = bigs[i];
        for (auto [u, d] : g[v]){
            big_set[i][color[u]].insert(d);
            if (is_big[u] != -1)
                g_big[v].push_back({is_big[u], d});
        }
        for (int j = 0; j < d; j++)
            if (SZ(big_set[i][j]))
                big_seg[i].insert(j, (*big_set[i][j].begin()));
    }
    set<pair<int, pair<int, int>>> edges;
    for (int v = 0; v < n; v++){
        if (is_big[v] != -1)
            continue;
        for (auto [u, d] : g[v]){
            if (is_big[u] != -1){
                g_big[v].push_back({is_big[u], d});
                continue;
            }
            if (color[v] != color[u]){
                int a = v, b = u;
                if (a > b)
                    swap(a, b);
                edges.insert({d, {a, b}});
            }

        }
    }
    //for (auto [a, b] : edges){
        //cout << b.first + 1 << "->" << b.second + 1 << " " << a << '\n';
    //}
    for (int i = 0; i < q; i++){
        int v, x;
        cin >> v >> x;
        --v;
        --x;
        for (auto [u, d] : g_big[v]){
            int was = (*big_set[u][color[v]].begin());
            big_set[u][color[v]].erase(big_set[u][color[v]].find(d));
            if (!SZ(big_set[u][color[v]]))
                big_seg[u].insert(color[v], TMAX(int));
            if (SZ(big_set[u][color[v]]) && (*big_set[u][color[v]].begin()) != was)
                big_seg[u].insert(color[v], (*big_set[u][color[v]].begin()));
            was = (SZ(big_set[u][x]) ? (*big_set[u][x].begin()) : TMAX(int));
            big_set[u][x].insert(d);
            if ((*big_set[u][x].begin()) != was)
                big_seg[u].insert(x, (*big_set[u][x].begin())); 
        }

        if (is_big[v] == -1){
            for (auto [u, d] : g[v]){
                if (is_big[u] != -1)
                    continue;
                //cout << "!" << v + 1 << "->" << u + 1 << ' ' << x << ' ' << color[u] << '\n'; 
                if (color[u] == x){
                    int a = v, b = u;
                    if (a > b)
                        swap(a, b);
                    edges.erase({d, {a, b}});
                }
                if (color[u] == color[v] && color[v] != x){
                    int a = v, b = u;
                    if (a > b)
                        swap(a, b);
                    edges.insert({d, {a, b}});
                }
            }
        }
        color[v] = x;
        int ans = TMAX(int);
        if (SZ(edges))
            ans = edges.begin()->first;
        for (int j = 0; j < big_cnt; j++){
            //cout << bigs[j] + 1 << ' ' << min(big_seg[j].get(0, color[bigs[j]]), big_seg[j].get(color[bigs[j]] + 1, d)) << '\n';
            ans = min(ans, min(big_seg[j].get(0, color[bigs[j]]), big_seg[j].get(color[bigs[j]] + 1, d)));
        }
        //for (auto [a, b] : edges){
            //cout << b.first + 1 << "->" << b.second + 1 << " " << a << '\n';
        //}
        cout << ans << '\n';
    }
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

