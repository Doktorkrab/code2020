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
 
int n, k;
const int MAXN = 2e5 + 7;
int arr[MAXN];
int fr[MAXN];
bool mx[MAXN];
int solve() {
    if (!(cin >> n >> k))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    sort(arr, arr + n);
    for (int i = 0 ; i < k; i++){
        cin >> fr[i];
        mx[i] = 0;
    }
    sort(fr, fr + k);
    ll ans = 0;
    int pnt = 0;
    for (int i = 0; i < k; i++){
        ans += arr[n - i - 1];
        fr[i]--;
        if (fr[i] == 0){
            ans += arr[n - i - 1];
        }
    }
    while (pnt < k && fr[pnt] == 0)
        pnt++;
    // cout << ans << '\n';
    for (int i = n - k - 1; i >= 0 && pnt < k; i--){
        fr[pnt]--;
        if (fr[pnt] == 0){
            ans += arr[i];
            pnt++;
        }
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