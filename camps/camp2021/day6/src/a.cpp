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
string f;
string s, t;
const int MAXC = 26;
int ee[MAXC];
int nxt[MAXC];
int a[MAXC];
int k[MAXC];
int was[MAXC];
const int MAXANS = 1e7;
int dfs(int v, int end) {
    if (v == end)
        return was[end];
    if (nxt[v] == -1)
        return -1;
    if (was[nxt[v]] != -1)
        return -1;
    was[nxt[v]] = was[v]  +1;
    return dfs(nxt[v], end);
}
int find_cycle(int v, int start){
    if (nxt[v] == -1)
        return 0;
    if (nxt[v] == start)
        return was[v] + 1;
    if (was[nxt[v]] != -1)
        return 0;
    was[nxt[v]] = was[v] + 1;
    return find_cycle(nxt[v], start);
}
int solve() {
    if (!(cin >> f >> n >> s >> t))
        return 1;
    fill(k, k + MAXC, 0);
    fill(a, a + MAXC, 0);
    for (int i = 0; i < MAXC; i++)
        nxt[i] = f[i] - 'a';

    fill(ee, ee + MAXC, -1);
    for (int i = 0; i < n; i++) {
        int c = s[i] - 'a';
        int v = t[i] - 'a';
        if (ee[c] == -1)
            ee[c] = v;
        if (ee[c] != v) {
            cout << "-1\n";
            return 0;
        }
    }
    for (int i = 0; i < MAXC; i++) {
        if (ee[i] == -1)
            continue;
        fill(was, was + MAXC, -1);
        was[i] = 0;
        a[i] = dfs(i, ee[i]);
        if (a[i] == -1){
            cout << "-1\n";
            return 0;
        }
        fill(was, was + MAXC, -1);
        was[ee[i]] = 0;
        k[i] = find_cycle(ee[i], ee[i]);
    }
    for (int sol = 0; sol < MAXANS;sol++){
        bool good = true;
        for (int i = 0; i < MAXC; i++){
            if (ee[i] == -1)
                continue;
            if (sol < a[i]){
                good = false;
                break;
            }
            int x = sol - a[i];
            if (k[i] == 0 && x != 0){
                good = false;
                break;
            }
            if (k[i] == 0)
                continue;
            if (x % k[i] != 0){
                good = false;
                break;
            }
        }
        if (good){
            cout << sol << '\n';
            return 0;
        }
    }
    cout << "-1\n";
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
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
