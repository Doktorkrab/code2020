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
int arr[MAXN];
// int arr1[2 * MAXN];
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    int m = (n + 1) / 2;
    ll cur = 0;
    for (int i = 0; i < m; i++)
        cur += arr[(2 * i) % n];
    ll ans = cur;
    for (int i = 0; i < n - 1; i++){
        cur -= arr[(2 * i) % n];
        cur += arr[(2 * (i + m)) % n];
        ans = max(ans, cur);
    }
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