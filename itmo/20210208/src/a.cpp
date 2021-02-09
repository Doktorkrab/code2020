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
const int MAXN = 1e6 + 7;
bool is_prime[MAXN];
 
int solve() {
    if (!(cin >> n))
        return 1;
    fill(is_prime, is_prime + n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i < n; i++){
        if (!is_prime[i])
            continue;
        for (ll j = 1LL * i * i; j <= n; j += i)
            is_prime[j] = false;
    }
    for (int i = 2; i <= n; i++){
        if (!is_prime[i] && !is_prime[n - i]){
            cout << i << ' ' << n - i << '\n';
            return 0;
        }
    }
    assert(0);
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
