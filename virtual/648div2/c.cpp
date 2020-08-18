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
const int MAXN = 2e5 + 7;
int a[MAXN];
int b[MAXN];
int pos[MAXN];
int offset[2 * MAXN];
 
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < 2 * n; i++)
        offset[i] = 0;
    for (int i = 0; i < n; i++){
        cin >> a[i];
        pos[a[i]] = i;
    }
    for (int i = 0; i < n; i++){
        cin >> b[i];
        int diff = pos[b[i]] - i;
        if (diff < 0)
            diff += n;
        offset[diff]++;
    }
    int ans = 0;
    for (int i = 0; i < 2 * n; i++)
        ans = max(ans, offset[i]);
    cout << ans << '\n';
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