#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<int> p, used;
int run = 0;

int dfs(int v) {
    used[v] = run;
    for (int u : g[v]) {
        if (p[u] == -1) {
            p[u] = v;
            return 1;
        }
    }
    for (int u : g[v]) {
        if (used[p[u]] != run && dfs(p[u])) {
            p[u] = v;
            return 1;
        }
    }
    return 0;
}

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    g.resize(s.size());
    used.assign(s.size(), -1);
    p.assign(n, -1);

    vector<vector<int>> letters(255);
    for (int i = 0; i < s.size(); i++) {
        letters[s[i] - 'A'].push_back(i);
    }
    for (int i = 0; i < n; i++) {
        string t;
        cin >> t;
        for (char c : t) {
            for (int v : letters[c - 'A']) {
                if (g[v].empty() || g[v].back() != i)
                    g[v].push_back(i);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < s.size(); i++) {
        ans += dfs(i);
        run++;
    }
    if (ans != s.size()) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    vector<int> ans1(s.size());
    for (int i = 0; i < n; i++) {
        if (p[i] == -1) continue;
        ans1[p[i]] = i + 1;
    }
    for (int u : ans1) cout << u << ' ';
    cout << '\n';
}
