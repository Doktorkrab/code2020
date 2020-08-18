#include <bits/stdc++.h>
#include <ostream>
 
using namespace std;
using ll = long long;
#define int ll

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
const int MAXN = 505;
int arr[MAXN];
 
int solve() {
    if (!(cin >> n))
        return 1;
    arr[0] = arr[1] = arr[2] = 0;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    if (n <= 3){
        cout << (arr[0] | arr[1] | arr[2]) << '\n';
        return 0;
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = j + 1; k < n; k++)
                ans = max(ans, (arr[i] | arr[j] | arr[k]));
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