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
 
int n, x;
const int MAXN = 1e5 + 7;
int arr[MAXN];
 
int solve() {
    if (!(cin >> n >> x))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    sort(arr, arr + n);
    reverse(arr, arr + n);
    int pnt = 0;
    int ans = 0;
    int cur = 0;
    while (pnt < n){
        cur++;
        if (1LL * cur * arr[pnt] >= x){
            ans++;
            cur = 0;
        }
        pnt++;
    }
    cout << ans << '\n';
    return 0;
}
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
   cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}