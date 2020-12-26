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
 
int n, m;
const int MAXN = 1e5 + 7;
int fence[MAXN];
int planks[MAXN];
int ans[MAXN];
int pnt = 0;
int used = 0;
bool check(int mid){
    fill(ans, ans + MAXN, -1);
    pnt = 0;
    used = 0;
    for (int i = 0; i < n; i++){
        if (fence[i] >= mid)
            continue;
        while (pnt < m && planks[pnt] + fence[i] < mid)
            pnt++;
        if (pnt == m)
            return false;
        ans[i] = pnt;
        used++;
        pnt++;
    }
    return true;
}
 
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> fence[i];
    cin >> m;
    for (int i = 0; i < m; i++)
        cin >> planks[i];
    int l = 0, r = 1e9;
    while (r - l > 1){
        int m = l + (r - l) / 2;
        if (check(m))
            l = m;
        else
            r = m;
    }
    check(l);
    cout << l << ' ' << used << '\n';
    for (int i = 0; i < n; i++)
        if (ans[i] != -1)
            cout << i + 1 << ' ' << ans[i] + 1 << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("j.in", "r", stdin);
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
