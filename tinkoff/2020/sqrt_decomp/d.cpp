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

const int MAXN = 1e5 + 7;
int n, m;

vector<vector<int>> hist;  // for heavy vertexes
vector<int> g[MAXN];
vector<int> big[MAXN];
int arr[MAXN];
int is_big[MAXN];

inline void init() { memset(is_big, -1, sizeof(int) * MAXN); }

inline void solve() {
    init();
    const int HEAVY = 2 * ((int) sqrt(m + 0.5));
    for (int i = 0; i < n; i++) cin >> arr[i];
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        // cerr << v << ' ' << u << '\n';
        g[--v].push_back(--u);
        g[u].push_back(v);
    }

    for (int i = 0; i < n; i++)
        if (g[i].size() >= HEAVY) {
            is_big[i] = hist.size();
            hist.push_back(vector<int>(1e5 + 7));
            for (int j : g[i]) hist[is_big[i]][arr[j]]++;
        }
    for (int i = 0; i < n; i++)
        for (int j : g[i])
            if (is_big[j] != -1) big[i].push_back(is_big[j]);
    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j : g[i]) ans += (i < j && arr[i] != arr[j]);

    int q = 0;
    cin >> q;
    // cerr << q <<
    while (q--) {
        int v, c;
        cin >> v >> c;
        --v;
        for (int j : big[v]) {
            hist[j][arr[v]]--;
            hist[j][c]++;
        }
        if (is_big[v] != -1) {
            ans -= (int) (g[v].size()) - hist[is_big[v]][arr[v]];
            arr[v] = c;
            ans += (int) (g[v].size()) - hist[is_big[v]][arr[v]];
            cout << ans << '\n';
            continue;
        }
        for (int j : g[v]) ans -= (arr[v] != arr[j]);
        arr[v] = c;
        for (int j : g[v]) ans += (arr[v] != arr[j]);
        cout << ans << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    while (cin >> n >> m) solve();
}
