#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct Edge {
    int v, u, f, c;

    operator int() { return c - f; }
};

const int MAXM = 1e6 + 5;
const int MAXN = 3e2 + 15;
Edge edges[2 * MAXM];
int head[MAXN];
int head1[MAXN];
int nxt[2 * MAXM];
int d[MAXN];

int n, m;
const int INF = 1e9;

inline void push_edge(int v, int i) {
    if (head[v] != -1) nxt[i] = head[v];
    head[v] = i;
}

inline void init() {
    memset(head, -1, sizeof(int) * MAXN);
    memset(head1, -1, sizeof(int) * MAXN);
    memset(nxt, -1, 2 * sizeof(int) * MAXM);
}

inline void bfs(int MAX) {
    d[n] = 0;
    deque<int> q = {n};
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (int e = head[v]; e != -1; e = nxt[e]) {
            Edge ee = edges[e];
            if (d[ee.u] == -1 && ee >= MAX) {
                d[ee.u] = d[v] + 1;
                q.push_back(ee.u);
            }
        }
    }
}

int dfs(int v, int mn = 1e9) {
    if (v == n + 1) return mn;
    for (; head1[v] != -1; head1[v] = nxt[head1[v]]) {
        Edge e = edges[head1[v]];
        if (e == 0 || d[e.u] != d[v] + 1) continue;
        int res = dfs(e.u, min(mn, (int) e));
        if (res != 0) {
            edges[head1[v]].f += res;
            edges[head1[v] ^ 1].f -= res;
            return res;
        }
    }
    return 0;
}

inline int find_flow() {
    int ans = 0, fl;
    for (int power = 30; power >= 0; power--) {
        while (1) {
            memset(d, -1, sizeof(int) * MAXN);
            for (int i = 0; i < MAXN; i++) head1[i] = head[i];
            bfs(1 << power);
            // cerr << power << ' ' << d[n + 1] <<
            if (d[n + 1] == -1) break;
            while (fl = dfs(n)) ans += fl;
        }
    }
    return ans;
}

inline void solve() {
    init();
    int t = n + 1, s = n;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int w;
        cin >> w;
        if (w < 0) {
            edges[2 * i] = {i, t, 0, -w};
            edges[2 * i + 1] = {t, i, 0, 0};
            push_edge(i, 2 * i);
            push_edge(t, 2 * i + 1);
        } else {
            edges[2 * i] = {s, i, 0, w};
            edges[2 * i + 1] = {i, s, 0, w};
            push_edge(s, 2 * i);
            push_edge(i, 2 * i + 1);
            sum += w;
        }
    }
    int pnt = 2 * n;
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        cin >> cnt;
        while (cnt--) {
            int kek;
            cin >> kek;
            --kek;
            edges[pnt] = {i, kek, 0, INF};
            push_edge(i, pnt++);
            edges[pnt] = {kek, i, 0, 0};
            push_edge(kek, pnt++);
        }
    }
    // cerr << find_flow() << '\n';
    cout << sum - find_flow() << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    while (cin >> n) solve();
}
