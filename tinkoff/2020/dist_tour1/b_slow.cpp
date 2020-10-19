#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ostream>

using namespace std;
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
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
const int MAXN = 2e5 + 7;
vector<int> g[MAXN];
ll ans[MAXN];
int dfs(int v, ordered_set<int>& now) {
    now.insert(v);
    for (int u : g[v]){
        ordered_set<int> ret;
        ans[v] += dfs(u, ret);
        if (SZ(now) <= SZ(ret)){
            for (int x : now)
                ans[v] += ret.order_of_key(x);
            for (int x : now)
                ret.insert(x);
            now = ret;
        }
        else {
            for (int x : ret)
                ans[v] += SZ(now) - now.order_of_key(x);
            for (int x : ret)
                now.insert(x);
        }
    }
    return ans[v];
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++){
        int k;
        cin >> k;
        g[i].resize(k);
        for (int j = 0; j < k; j++){
            cin >> g[i][j];
            g[i][j]--;
        }
    }
    ordered_set<int> kek;
    dfs(0, kek);
    for (int i = 0; i < n; i++)
        cout << ans[i] << " \n"[i + 1 == n];
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
