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

    void clear() {
        for (int i = 0; i < pnt; i++) {
            auto &e = edges[i];
            e.f = 0;
        }
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

map<char, int> gg = {{'W', 2},
                     {'M', 3},
                     {'C', 4},
                     {'R', 5}};
string ans[] = {"", "", "warrior", "mage", "cleric", "rogue"};

int solve() {
    if (!(cin >> n))
        return 1;
    flow::s = 0;
    flow::t = 1;
    int W = 2;
    int M = 3;
    int C = 4;
    int R = 5;
    flow::init();
    for (auto &[a, b] : gg)
        flow::add_edge(b, flow::t, 1);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        flow::add_edge(flow::s, i + 6, 1);
        for (char c : s)
            flow::add_edge(i + 6, gg[c], 1);
    }
    int aaa = flow::max_flow();
    cout << aaa << '\n';
    vector<string> ans1;
    flow::add_edge(flow::s, n + 6, 1);
    flow::clear();
    for (int i = 2; i <= 5; i++) {
        flow::add_edge(n + 6, i, 1);
        flow::clear();
        int now = flow::max_flow();
        if (now > aaa)
            ans1.push_back(ans[i]);
        flow::edges[flow::pnt - 2].c = 0;
    }
    if (SZ(ans1)) {
        cout << "Looking for ";
        for (const string &s : ans1)
            cout << s << ' ';
        cout << '\n';
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
