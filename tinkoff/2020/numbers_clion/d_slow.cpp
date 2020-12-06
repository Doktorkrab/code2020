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

 
int solve() {
    if (!(cin >> n))
        return 1;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    ll ans = 0;

    for (int i = 0; i < n; i++){
        int mx = arr[i];
        int g = abs(arr[i]);
        ll sum = arr[i];
//        cerr << i << '\n';
        for (int j = i - 1; j >= 0; j--){
            mx = max(mx, arr[j]);
            sum += arr[j];
            g = gcd(g, abs(arr[j]));
            ans = max(ans, g * (sum - mx));
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
//    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}