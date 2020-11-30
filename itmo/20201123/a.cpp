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
const int MAXN = 1e5 + 7;
const int INF = 1e9 + 7;
pair<int, int> arr[MAXN];


ll prefix[MAXN];
int solve() {
    if (!(cin >> n >> k))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i].second >> arr[i].first;
    sort(arr, arr + n);

    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + arr[i].second;
    ll ans = 0;
    for (int i = 0; i < n; i++){
        int pos = lower_bound(arr, arr + n, make_pair(arr[i].first - k, 0)) - arr;
//        cout << pos << ' ' << i << '\n';
        ans = max(ans, prefix[i + 1] - prefix[pos]);
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
