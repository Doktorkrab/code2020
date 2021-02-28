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
 
int n, m;

const int MAXN = 1e5 + 7;
int arr[MAXN];
int lft[MAXN];
int rgt[MAXN];

int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    for (int i = 0; i < n; i++){
        if (i == 0 || arr[i - 1] >= m)
            lft[i] = i;
        else
            lft[i] = lft[i - 1];
    }
    for (int i = n - 1; i >= 0; i--){
        if (i + 1 == n || arr[i + 1] > m)
            rgt[i] = i;
        else
            rgt[i] = rgt[i + 1];
    }
    ll ans = 0;
    for (int i = 0; i < n; i++){
        if (arr[i] == m){
            ans += 1LL * (i - lft[i] + 1) * (rgt[i] - i + 1);
        }
    }
    cout << ans << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
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
