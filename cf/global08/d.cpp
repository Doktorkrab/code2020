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

const int MAXN = 2e5 + 7;
const int MAXLOG = 24;
int n;
int arr[MAXN];
int cnt[MAXLOG]; 
int solve() {
    if (!(cin >> n))
        return 1;

    for (int i = 0; i < n; i++)
        cin >> arr[i];
    for (int i = 0; i < MAXLOG; i++)
        cnt[i] = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < MAXLOG; j++)
            cnt[j] += ((arr[i] >> j) & 1);

    for (int i = 0; i < n; i++){
        arr[i] = 0;
        for (int j = MAXLOG - 1; j >= 0; j--)
            if (cnt[j] > 0){
                arr[i] |= (1 << j);
                cnt[j]--;
            }
    }
    ll ans = 0;
    // for (int i = 0; i < n; i++)
    //     cout << arr[i] << " \n"[i + 1 == n];
    for (int i = 0; i < n; i++)
        ans += 1LL * arr[i] * arr[i];
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