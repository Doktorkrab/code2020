#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <ostream>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <vector>

using namespace std;

const int N = 3e5;

int n, m;
int a, b;

vector<int> g[N];

void scan() {
    cin >> n >> m;
    cin >> a >> b;
    --a, --b;
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
}

bool used[N];
vector<int> res;
vector<int> stack;

void dfs(int v) {
    if (v == b) {
        res = vector<int>(stack);
        return;
    }
    used[v] = true;
    stack.push_back(v);
    for (int u : g[v]) {
        if (!used[u]) {
            dfs(u);
        }
    }
    stack.pop_back();
}

void solve() {
    dfs(a);
    vector<int> x(res);
    for (int v = 0; v < n; ++v) {
        reverse(g[v].begin(), g[v].end());
    }
    fill(used, used + n, false);
    res.clear();
    dfs(a);
    vector<int> y(res);

    set<int> chx(x.begin(), x.end());
    set<int> chy(y.begin(), y.end());

    vector<int> common;
    for (int v : x) {
        if (chy.count(v)) {
            common.push_back(v);
        }
    }

    map<int, int> xi;
    for (int i = 0; i < x.size(); ++i) {
        xi[x[i]] = i;
    }

    map<int, int> yi;
    for (int i = 0; i < y.size(); ++i) {
        yi[y[i]] = i;
    }

    int ans = common.size();
    for (int i = 1; i < common.size(); ++i) {
        ans += max(xi[common[i]] - xi[common[i - 1]],
                   yi[common[i]] - yi[common[i - 1]]);
    }
    cout << ans - 1 << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    scan();
    solve();
    return 0;
}