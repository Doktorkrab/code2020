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
const int MAXN = 1e5 + 7;
ll m;

int arr[MAXN];
ll prefix_sums[MAXN];

ll get_stupid(){
    ll ans = 0;
    for (int i = 0; i < n; i++){
        ll sum = 0;
        for (int j = i; j < n; j++){
            sum += arr[j];
            if (sum >= m)
                ans++;
        }
    }
    return ans;
}

ll get_smart(){
    ll ans = 0;
    for (int i = 0; i < n; i++){
        int pos = (int)(lower_bound(prefix_sums + i, prefix_sums + n + 1, m + prefix_sums[i]) - prefix_sums);
        ans += (n + 1) - pos;
    }
    return ans;
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        prefix_sums[i + 1] = prefix_sums[i] + arr[i];
    }
//    cout << get_stupid() << '\n';
    cout << get_smart() << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("a1.in", "r", stdin);
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
