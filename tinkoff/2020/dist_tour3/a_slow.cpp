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
const int MAXN = 3e5;
int arr[MAXN];
 
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    int ans = MAXN;
    for (int i = 0; i < n; i++){
        int now = arr[i];
        if (i == n - i - 1){
            ans = 0;
            break;
        }
        for (int j = n - i - 1; j < n; j++)
            if (now == arr[j] && j != i)
                ans = min(abs(n - i - 1 - j), ans);
        for (int j = n - i - 1; j >= 0; j--)
            if (now == arr[j] && j != i)
                ans = min(abs(n - i - 1 - j), ans);
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
