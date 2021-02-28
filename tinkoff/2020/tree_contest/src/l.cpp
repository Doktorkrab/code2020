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
const int ALP = 26;
const int MAXN = 3e5 + 7;
pair<int, int> g[MAXN][ALP];
int sz[MAXN];
int cnt[MAXN];  // cnt vertexes on level i
int ans[MAXN];  // ans for dp i
vector<int> available;

int merge(int now, int v) {
    int add = 0;
    for (int i = 0; i < ALP; i++) {
        if (g[v][i] == make_pair(0, 0))
            continue;
        if (g[now][i].first == 0) {
            add++;
            g[now][i] = {available.back(), 1};
            available.pop_back();
        } else if (g[now][i].second != 0) {
            g[now][i].second++;
        }
        add += merge(g[now][i].first, g[v][i].first);
    }
    return add;
}

void unmerge(int now, int v) {
    for (int i = 0; i < ALP; i++) {
        if (g[v][i] == make_pair(0, 0))
            continue;
        unmerge(g[now][i].first, g[v][i].first);
        if (g[now][i].second == 1) {
            available.push_back(g[now][i].first);
            g[now][i] = {0, 0};
        } else if (g[now][i].second) {
            g[now][i].second--;
        }
    }
}

void dfs(int v, int d) {
    sz[v] = 1;
    cnt[d + 1]++;
    int mx_c = -1;
    for (int c = 0; c < ALP; c++) {
        if (!g[v][c].first)
            continue;
        dfs(g[v][c].first, d + 1);
        sz[v] += sz[g[v][c].first];
        if (mx_c == -1 || sz[g[v][c].first] > sz[g[v][mx_c].first])
            mx_c = c;
    }
    if (mx_c == -1) {
        ans[d]++;
        return;
    }
    ans[d] += sz[g[v][mx_c].first];
    for (int c = 0; c < ALP; c++) {
        if (c == mx_c || g[v][c].first == 0)
            continue;
        ans[d] += merge(g[v][mx_c].first, g[v][c].first);
    }
    for (int c = 0; c < ALP; c++) {
        if (c == mx_c || g[v][c].first == 0)
            continue;
        unmerge(g[v][mx_c].first, g[v][c].first);
    }
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 1; i < n; i++) {
        int u, v;
        char x;
        cin >> u >> v >> x;
        g[u][x - 'a'] = {v, 0};
    }
    available.reserve(MAXN);
    available.clear();
    for (int i = n + 1; i < MAXN; i++)
        available.push_back(i);
    dfs(1, 0);
    int ans1 = n, pos = -1;
    for (int i = 1; i <= n; i++) {
        cnt[i] += cnt[i - 1];
        if (cnt[i - 1] + ans[i - 1] < ans1) {
            ans1 = cnt[i - 1] + ans[i - 1];
            pos = i;
        }
    }
    cout << ans1 << '\n' << pos << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("l.in", "r", stdin);
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
