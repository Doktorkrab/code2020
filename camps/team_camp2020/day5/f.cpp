
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
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i <n; i++)
        cin >> arr[i];
    int ans = 0;
    int cnt = 0;
    for (int i = n - 1; i >= 0; i--){
        ans = max(ans, arr[i] + cnt);
        cnt += (arr[i] > 0);
    }
    cout << ans << '\n';
    return 0;
}
 
signed main() {
    freopen("handshakes.in", "r", stdin);
    freopen("handshakes.out", "w", stdout);
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
