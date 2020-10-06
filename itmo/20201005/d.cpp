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
const int MAXN = 1e4 + 7;
int arr[MAXN];
vector<int> g[MAXN];
vector<pair<int, int>> ans;
bool fail;
bool used[MAXN];
int dfs(int v) {
    used[v] = true;
    vector<pair<int, int>> have; // rank, v
    for (int u : g[v]) {
        int rank = dfs(u);
        have.emplace_back(rank, u);
        if (fail)
            return 0;
    }
    sort(ALL(have));
    int now = 0;
    for (auto [rank, u] : have){
//        cout << v + 1 << "->" << u + 1 << ' ' << rank << ' ' << now << '\n';
        if (rank > now) {
            fail = true;
            return 0;
        }
        ans.emplace_back(v + 1, u + 1);
        now = max(now, rank + 1);
    }
    return now;
}


int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        g[i].clear();
    fill(used, used + n, 0);
    ans.clear();
    fail = false;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (arr[i] - 1 != i)
            g[arr[i] - 1].push_back(i);
    }
    for (int i = 0; i < n; i++)
        if (arr[i] - 1 == i)
            dfs(i);
    for (int i = 0; i < n; i++)
        if (!used[i])
            fail = true;

    if (fail)
        cout << "-1\n";
    else {
        cout << SZ(ans) << '\n';
        for (auto[a, b] : ans)
            cout << a << ' ' << b << '\n';
    }
    return 0;
}

signed main() {
//#ifdef LOCAL
//    freopen("inp", "r", stdin);
//#endif
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