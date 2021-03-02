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
string s, t;
const int MAXN = 1e6 + 7;
int prefix[MAXN]; // [0;i)
int suffix[MAXN]; // [i; n)
int solve() {
    if (!(cin >> t >> s))
        return 1;
    n = SZ(s);
    m = SZ(t);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i];
        if (prefix[i + 1] < m && s[i] == t[prefix[i + 1]])
            prefix[i + 1]++;
    }
    suffix[n] = 0;
    for (int i = n - 1; i >= 0; i--){
        suffix[i] = suffix[i + 1];
        if (suffix[i] < n && s[i] == t[m - suffix[i] - 1])
            suffix[i]++;
    }
    for (int i = 0; i < n; i++){
//        cout << prefix[i] << ' ' << suffix[i + 1] << endl;
        if (prefix[i] + suffix[i + 1] + 1 >= m && prefix[i] != m && s[i] != t[prefix[i]]){
            cout << prefix[i] + 1 << ' ' << s[i] << '\n';
            return 0;
        }

    }
    assert(0);
    return 0;
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
