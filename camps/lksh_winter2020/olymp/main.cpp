#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct graph_scc {
    // Finds Strongly Connected Components of given graph
    //
    // Correctness tested on the following problem:
    // https://atcoder.jp/contests/arc069/tasks/arc069_d
    //
    int n;
    vector<vector<int> > graph;
    vector<vector<int> > inv_graph;
    vector<int> fr, to;
    vector<int> fn;
    vector<int> vis;
    vector<int> component;
    int col;

    void inv_dfs(int v) {
        vis[v] = 1;
        for (auto id : inv_graph[v]) {
            int u = fr[id];
            if (!vis[u]) {
                inv_dfs(u);
            }
        }
        fn.push_back(v);
    }

    void dfs(int v) {
        component[v] = col;
        for (auto id : graph[v]) {
            int u = to[id];
            if (component[u] == -1) {
                dfs(u);
            }
        }
    }

    graph_scc(int _n) {
        n = _n;
        graph = vector<vector<int> >(n);
        inv_graph = vector<vector<int> >(n);
    }

    void add_edge(int v, int u) {
        graph[v].push_back(fr.size());
        inv_graph[u].push_back(fr.size());
        fr.push_back(v);
        to.push_back(u);
    }

    vector<vector<int> > scc() {
        vis = vector<int>(n);
        component = vector<int>(n, -1);
        fn = {};
        col = 0;
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                inv_dfs(i);
            }
        }
        reverse(fn.begin(), fn.end());
        for (auto i : fn) {
            if (component[i] == -1) {
                dfs(i);
                col++;
            }
        }
        vector<vector<int> > res(col);
        for (int i = 0; i < n; i++) {
            component[i] = col - 1 - component[i];
            cout << component[i] << " \n"[i + 1 == n];
            res[component[i]].push_back(i);
        }
        return res;
    }
};

void dfs(int v, vector<int> &vn, vector<vector<int> > &g, vector<int> &ts) {
    vn[v] = 1;
    for (auto u : g[v])
        if (!vn[u]) {
            dfs(u, vn, g, ts);
        }
    ts.push_back(v);
}

void solve() {
    int n, m;
    cin >> n >> m;
    graph_scc A(n);
    vector<int> pet(n);
    for (int i = 0; i < m; i++) {
        int f, t;
        cin >> f >> t;
        f--, t--;
        if (f == t)
            pet[f] = 1;
        A.add_edge(f, t);
    }
    vector<vector<int> > S = A.scc();

    vector<vector<int> > g(S.size());
    vector<vector<int> > rg(S.size());
    for (int i = 0; i < m; i++) {
        g[A.component[A.fr[i]]].push_back(A.component[A.to[i]]);
        //cout << A.component[A.fr[i]] << " " << A.component[A.to[i]] << "\n";
        rg[A.component[A.to[i]]].push_back(A.component[A.fr[i]]);
    }
    int f = A.component[0], t = A.component[n - 1];
    vector<int> q = {f};
    vector<int> vis(S.size());
    vector<int> q2 = {t};
    vector<int> vis2(S.size());
    vis[f] = 1;
    vis2[t] = 1;
    for (int i = 0; i < q.size(); i++) {
        for (auto u : g[q[i]]) {
            if (vis[u] == 0) {
                vis[u] = 1;
                q.push_back(u);
            }
        }
    }
    for (int i = 0; i < q2.size(); i++) {
        for (auto u : rg[q2[i]]) {
            if (vis2[u] == 0) {
                vis2[u] = 1;
                q2.push_back(u);
            }
        }
    }
    if (!vis[t]) {
        cout << 0 << "\n\n";
        return;
    }
    vector<int> vn(S.size());
    vector<int> ts;
    dfs(f, vn, g, ts);
    reverse(ts.begin(), ts.end());
    vector<int> pos_in_sort(S.size(), -1);

    //cout << "\n";
    for (int i = 0; i < ts.size(); i++) {
        //cout << ts[i] << " ";
        pos_in_sort[ts[i]] = i;
    }
    //cout << "\n";

    vector<int> p(S.size());


    for (int i = 0; i < m; i++) {
        int L = pos_in_sort[A.component[A.fr[i]]];
        int R = pos_in_sort[A.component[A.to[i]]];
        //cout << A.fr[i] << " " << A.to[i] << " -> " << L << " " << R << endl;
        //cout << vis[A.component[A.fr[i]]] << " " << vis[A.component[A.to[i]]] << endl;
        if (0 <= L && 0 <= R && L + 1 < p.size() && vis[A.component[A.fr[i]]] && vis[A.component[A.to[i]]]) {
            p[L + 1]++, p[R]--;
            cout << L << " " << R << endl;
        }
    }

    vector<int> ans;
    if (p[0] == 0) {
        int id = ts[0];
        int v = S[id][0];
        if (!pet[v] && S[id].size() == 1 && vis[id] && vis2[id])
            ans.push_back(v);
    }
    for (int i = 1; i < ts.size(); i++) {
        p[i] += p[i - 1];
        if (p[i] == 0) {
            int id = ts[i];
            int v = S[id][0];
            if (!pet[v] && S[id].size() == 1 && vis[id] && vis2[id])
                ans.push_back(v);
        }
    }
    cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] + 1 << " ";
    }
    cout << "\n";
}

int main() {
    freopen("10.in", "r", stdin);
    freopen("10.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cerr << i << endl;
        solve();
    }
}