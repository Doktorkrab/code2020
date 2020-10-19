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
const int MAXN = 3e5 + 7;
pair<int, int> arr[MAXN];
ll prefix[2][MAXN];
ll ans[MAXN];
 
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++){
        cin >> arr[i].first;
        arr[i].second = i;
    }
    sort(arr, arr + n);
    for (unsigned i = 0; i < n; i++){
        prefix[i & 1][i + 1] = prefix[i & 1][i] + arr[i].first;
        prefix[(i & 1) ^ 1][i + 1] = prefix[(i & 1) ^ 1][i];
    }
    for (int i = 0; i < n; i++){
        ans[arr[i].second] = prefix[0][i] + (prefix[1][n] - prefix[1][i + 1]);
    }
    for (int i = 0; i < n; i++)
        cout << ans[i] << " \n"[i + 1 == n];
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
