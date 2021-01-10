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
vector<ll> arr;
 
int solve() {
    if (!(cin >> n))
        return 1;
    vector<ll> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    ll best = 0;
    if (n == 2) {
        cout << 6;
        return 0;
    }
    bool was = false;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (arr[i] % 6 == 0){
            best = arr[i];
            was = true;
        }
    }
    if (was)
        cout << best << '\n';
    else
        cout << "-1\n";
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("n.in", "r", stdin);
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
