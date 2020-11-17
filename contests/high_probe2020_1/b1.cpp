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
#define int ll
int n, k;
const int MOD = 998244353;
const int MAXN = 1e6 + 7;
int arr[MAXN];
int get(int x){
    return (x * (x + 1) / 2) % MOD;
}
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    cin >> k;
    for (int i = 0; i < k; i++){
        int l, r;
        cin >> l >> r;
        --l;
        int ans = 0;
        int m = (l + r) / 2;
        for (int j = l; j < m; j++){
            ans += (get(j - l + 1) * arr[j]) % MOD;
            ans %= MOD;
        }
        for (int j = m; j < r; j++) {
            ans += (get(r - j) * arr[j]) % MOD;
            ans %= MOD;
        }
        cout << ans << '\n';
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
