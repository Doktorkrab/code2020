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
const int MAXN = 1e5 + 7;
int b[MAXN];
int pos_a[MAXN];
 
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        pos_a[x - 1] = i;
    }
    for (int i = 0; i < n; i++){
        cin >> b[i];
        b[i]--;
    }
    int ans = 1;
    for (int i = 1; i < n; i++){
        if (pos_a[b[i - 1]] + 1 != pos_a[b[i]])
            ans++;
    }
    cout << ans << '\n';
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
