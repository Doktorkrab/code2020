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
const int MAXN = 2e5 + 7;
int prefix[MAXN];
int arr[MAXN];

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++){
        char x;
        cin >> x;
        arr[i] = (x == '1');
        prefix[i + 1] = prefix[i] ^ arr[i];
    }
    auto get = [&](int l, int r){
        return prefix[r] ^ prefix[l];
    };
    int ans = 0;
    for (int l = 2; l <= n; l++){
        bool good = true;
        for (int i = l - 1; i < n; i += l){
            good = arr[i] == get(i - l + 1, i);
            if (!good)
                break;
        }
        ans += good;
    }
    cout << ans << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
#else
    freopen("encode.in", "r", stdin);
    freopen("encode.out", "w", stdout);
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
