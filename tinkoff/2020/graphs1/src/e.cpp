#include <bits/stdc++.h>


using namespace std;
vector<vector<int>> matrix;
vector<int> p, used;
int run = 0;
vector<vector<int>> g;

bool dfs(int v) {
    used[v] = run;
    for (int i = 0; i < matrix[v].size(); i++) {
        if (!matrix[v][i]) continue;
        if (p[i] == -1) {
            p[i] = v;
            return 1;
        }
    }
    for (int i = 0; i < matrix[v].size(); i++) {
        if (!matrix[v][i]) continue;
        if (used[p[i]] != run && dfs(p[i])) {
            p[i] = v;
            return 1;
        }
    }
    return 0;
}


void dfs1(int v) {
    used[v] = 1;
    for (int u : g[v]) {
        if (!used[u]) dfs1(u);
    }
}

int main() {
    int k;
    cin >> k;
    while (k--) {
        int n, m;
        cin >> m >> n;
        matrix.assign(m, vector<int>(n, 1));
        for (int i = 0; i < m; i++) {
            int tmp;
            cin >> tmp;
            while (tmp != 0) {
                --tmp;
                matrix[i][tmp] = 0;
                cin >> tmp;
            }
        }
        p.assign(n, -1);
        used.assign(m, -1);
        int ans = 0;
        for (int i = 0; i < m; i++) {
            ans += dfs(i);
            run++;
        }

        vector<int> start(m, 1);
        g.assign(n + m, {});
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!matrix[i][j]) continue;
                if (p[j] == i) {
                    g[j + m].push_back(i);
                } else {
                    g[i].push_back(j + m);
                }
            }
        }
//        cerr << "here";
        used.assign(n + m, 0);
        for (int i = 0; i < n; i++)
            if (p[i] != -1) {
                start[p[i]] = 0;
            }
        for (int i = 0; i < m; i++) {
            if (start[i] && !used[i]) {
                dfs1(i);
            }
        }
        vector<int> independent(n + m, 1);
        int ans1 = m, ans2 = n;
        for (int i = 0; i < m; i++) {
            if (!used[i]) {
                independent[i] = 0;
                ans1--;
            }
        }
        for (int i = 0; i < n; i++) {
            if (used[i + m]) {
                ans2--;
                independent[i + m] = 0;
            }
        }
        cout << n + m - ans << '\n' << ans1 << ' ' << ans2 << '\n';
        for (int i = 0; i < m; i++) {
            if (independent[i]) cout << i + 1 << ' ';
        }
        cout << '\n';
        for (int i = 0; i < n; i++) {
            if (independent[i + m]) cout << i + 1 << ' ';
        }
        cout << '\n';
    }
}
