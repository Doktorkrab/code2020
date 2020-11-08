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
const int MAXN = 1e3 + 7;
int arr[MAXN];
vector<int> g[MAXN];
bool used[MAXN];
int color[MAXN];
bool ok = true;
void dfs(int v, int c = 0){
    color[v] = c;
    used[v] = 1;
    for (int u : g[v]){
        if (!used[u])
            dfs(u, 3 - c);
        if (color[u] != 3 - color[v])
            ok = false;
        if (!ok)
            return;
    }
}
int solve() {
    ok = true;
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        g[i].clear();
        color[i] = used[i] = 0;
    }
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++){
            if (gcd(arr[i], arr[j]) != 1) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    for (int i = 0; i < n; i++)
        if (!used[i])
            dfs(i, 1);
    if (!ok){
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    for (int i = 0; i < n; i++)
        cout << color[i] << " \n"[i + 1 == n];
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
