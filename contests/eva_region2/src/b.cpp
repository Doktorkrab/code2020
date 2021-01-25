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
const int ALP = 26;
const int MAXN = 3e5 + 7;
int prefix[ALP][MAXN];
int suffix[ALP][MAXN];

int solve() {
    string s, t;
    while (cin >> t)
        s += t;
    n = SZ(s);
    for (int i = 0; i < n; i++) {
        for (int c = 0; c < ALP; c++) {
            prefix[c][i + 1] = prefix[c][i] + (s[i] - 'a' == c);
        }
    }
    for (auto & i : suffix)
        i[n] = 0;
    for (int i = n - 1; i >= 0; i--){
        for (int c = 0; c < ALP; c++)
            suffix[c][i] = suffix[c][i + 1] + (s[i] - 'a' == c);
    }
    ll ans = 0;
    for (int i = 0; i < n; i++){
        for (int c = 0; c < ALP; c++){
            ans += 1LL * prefix[c][i] * suffix[c][i + 1];
        }
    }
    cout << ans << '\n';
    return 1;
}

signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
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
