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

int n, k;
const int MAXN = 2e5 + 7;
const int MAXK = 10;
namespace flow {
    struct Edge {
        int v = 0, u = 1;
        ll c = 0, f = 0;
        int nxt = -1;
    };
    const int MAXN = 1e4 + 7;
    const int MAXM = 5e3 + 7;
    Edge edges[2 * MAXM];
    int head[MAXN];
    int head_changed[MAXN];
    int d[MAXN];
    int s, t;
    int pnt = 0;

    void init() {
        pnt = 0;
        fill(head, head + MAXN, -1);
    }

    void bfs(const int MAX) {
        fill(d, d + MAXN, -1);
        d[s] = 0;
        deque<int> q = {s};
        while (!q.empty()) {
            int v = q.front();
            q.pop_front();
            for (int e = head[v]; e != -1; e = edges[e].nxt) {
                auto[_, u, c, f, nxt] = edges[e];
                if (c - f >= MAX && d[u] == -1) {
                    d[u] = d[v] + 1;
                    q.push_back(u);
                }
            }
        }
    }

    ll dfs(int v, ll min_flow) {
        if (v == t || min_flow == 0)
            return min_flow;
        for (int &id = head_changed[v]; id != -1; id = edges[id].nxt) {
            const auto &e = edges[id];
            if (e.c - e.f == 0 || d[e.u] != d[v] + 1)
                continue;
            ll res = dfs(e.u, min(min_flow, e.c - e.f));
            if (res != 0) {
                edges[id].f += res;
                edges[id ^ 1].f -= res;
                return res;
            }
        }
        return 0;
    }

    void add_edge(int v, int u, int w) {
//        cout << v << "->" << u << ' ' << w << '\n';
        edges[pnt] = {v, u, w, 0, head[v]};
        head[v] = pnt++;
        edges[pnt] = {u, v, 0, 0, head[u]};
        head[u] = pnt++;
    }

    ll max_flow() {
        ll ans = 0;
        ll fl = 0;
        for (int power = 30; power >= 0; power--) {
            while (1) {
                bfs(1 << power);
                if (d[t] == -1)
                    break;
                copy(head, head + MAXN, head_changed);
                while (fl = dfs(s, TMAX(int)))
                    ans += fl;
            }
        }
        return ans;
    }
}  // namespace flow
int have[MAXN][MAXK];
int coords[MAXK][MAXN];
int mid[MAXK];
int power3[MAXK];
vector<int> buckets[MAXN];

int solve() {
    flow::init();
    for (auto &bucket : buckets)
        bucket.clear();
    if (!(cin >> n >> k))
        return 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            cin >> have[i][j];
            coords[j][i] = have[i][j];
        }
    }
    for (int i = 0; i < k; i++) {
        nth_element(coords[i], coords[i] + n / 2, coords[i] + n);
        nth_element(coords[i], coords[i] + n / 2 - 1, coords[i] + n / 2);
        mid[i] = coords[i][n / 2] + coords[i][n / 2 - 1];
    }
    power3[0] = 1;
    for (int i = 1; i <= k; i++)
        power3[i] = 3 * power3[i - 1];
    for (int i = 0; i < n; i++) {
        int now = 0;
        for (int j = 0; j < k; j++) {
            if (have[i][j] * 2 < mid[j])
                now += 0 * power3[j];
            else if (have[i][j] * 2 > mid[j])
                now += 2 * power3[j];
            else
                now += 1 * power3[j];
        }
        buckets[now].push_back(i);
    }
    flow::s = power3[k];
    flow::t = power3[k] + 1;
    for (int i = 0; i < flow::s; i++) {
        int mask_now = i;
        int start = mask_now % 3;
        if (start == 1) {
            continue;
        }
        mask_now /= 3;
        bool added = false;
        for (int j = 1; j < k; j++) {
            int x = mask_now % 3;
            mask_now /= 3;
            if (x == 1) {
                added = true;
                if (start == 0) {
//                    cout << "!" << i << ' ' << power3[j] << '\n';
                    flow::add_edge(i, i - power3[j], n);
                    flow::add_edge(i, i + power3[j], n);
                } else {
//                    cout << "!" << i << ' ' << power3[j] << '\n';
                    flow::add_edge(i - power3[j], i, n);
                    flow::add_edge(i + power3[j], i, n);
                }
                break;
            }
        }
        if (!added && start == 0)
            flow::add_edge(i, power3[k] - i - 1, n);
        if (start == 0)
            flow::add_edge(flow::s, i, SZ(buckets[i]));
        else
            flow::add_edge(i, flow::t, SZ(buckets[i]));
    }
    if (flow::max_flow() != n / 2) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    for (int it = 0; it < n / 2; it++) {
        int v = flow::s;
        int v1 = -1, v2 = -1;
        while (v != flow::t) {
            if (v1 == -1 && v != flow::s)
                v1 = v;
            v2 = v;
            bool was = false;
            for (int i = flow::head[v]; i != -1; i = flow::edges[i].nxt) {
                flow::Edge &e = flow::edges[i];
                if (e.f > 0) {
                    e.f--;
                    flow::edges[i ^ 1].f++;
                    v = e.u;
                    was = true;
                    break;
                }
            }
            assert(was);
        }
        cout << buckets[v1].back() + 1 << ' ' << buckets[v2].back() + 1 << endl;
        buckets[v1].pop_back();
        buckets[v2].pop_back();
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
