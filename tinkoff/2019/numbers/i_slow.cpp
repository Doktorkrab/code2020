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
const int MAXN = 5e4 + 7;
int arr[MAXN];
 
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    ll best = 0;
    for (int i = 0; i < n; i++){
        ll sum = arr[i];
        int mx = arr[i];
        int g = arr[i];
        for (int j = i + 1; j < n; j++){
            sum += arr[j];
            mx = max(mx, arr[j]);
            g = gcd(arr[j], g);
            best = max(best, (sum - mx) * g);
            cout << i + 1 << ' ' << j + 1 << ' ' << (sum - mx) * g << '\n';
        }
    }
    cout << best << '\n';
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