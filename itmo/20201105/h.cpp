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
const int MAXN = 4e5 + 7;
pair<int, int> lst[MAXN];
pair<int, int> queries[MAXN];
int suf[MAXN];
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++){
        cin >> lst[i].first;
        lst[i].second = -1;
    }
    int q;
    cin >> q;
    int pnt = 0;
    for (int i = 0; i < q; i++){
        int type;
        cin >> type;
        if (type == 1){
            int a, b;
            cin >> a >> b;
            lst[a - 1] = {b, i};
        }
        else {
            int x;
            cin >> x;
            queries[pnt++] = {i, x};
        }
    }
    suf[pnt] = 0;
    for (int i = pnt - 1; i >= 0; i--)
        suf[i] = max(suf[i + 1], queries[i].second);
    for (int i = 0; i < n; i++){
        int pos = upper_bound(queries, queries + pnt, make_pair(lst[i].second, -1)) - queries;
        cout << max(lst[i].first, suf[pos]) << " \n"[i + 1 == n];
    }
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
