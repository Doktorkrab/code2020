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
 
int n, q;
const int MAXN = 1e6 + 7;
int t[MAXN];
void upd(int pos, int how){
    for (int i = pos; i < MAXN; i |= i + 1)
        t[i] += how;
}
int get(int pos){
    int now = 0;
    if (pos < 0)
        return 0;
    for (int i = pos; i >= 0; i = (i & (i + 1)) - 1)
        now += t[i];
    return now;
}
int get(int l, int r){
    return get(r) - get(l - 1);
}
int solve() {
    if (!(cin >> n >> q))
        return 1;
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        upd(x - 1, 1);
        // cout << x - 1 << '\n';
    }
    for (int i = 0; i < q; i++){
        int x;
        cin >> x;
        // for (int j = 0; j < n; j++)
        //     cout << get(j, j) << " \n"[j + 1 == n];
        if (x > 0){
            upd(x - 1, 1);
            continue;
        }
        x = -x;
        --x;
        if (get(0) > x){
            upd(0, -1);
            // cout << "0\n";
            continue;
        }
        int l = 0, r = n;
        while (r - l > 1){
            int m = (l + r) / 2;
            if (get(m) > x)
                r = m;
            else
                l = m;
        }
        // cout << l << ' ' << r << '\n';
        // cout << get(l) << ' ' << get(r) << '\n';
        // cout << r + 1 << '\n';
        upd(r, -1);
    }
    if (get(n - 1) == 0){
        cout << "0\n";
        return 0;
    }
    int x = 0;
    int l = 0, r = n;
    if (get(0) > 0){
        cout << "1\n";
        return 0;
    }
    while (r - l > 1){
        int m = (l + r) / 2;
        if (get(m) > x)
            r = m;
        else
            l = m;
    }
    cout << r + 1 << '\n';
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