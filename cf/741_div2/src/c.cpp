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
 
string s;
int n;

 
int solve() {
    if (!(cin >> n >> s))
        return 1;
    if (count(ALL(s), '0') == 0){
        cout << "1 " << n - 1 << " 2 " << n << '\n';
        return 0;
    }
    int last = 0;
    for (int i = 0; i < n; i++)
        if (s[i] == '0')
            last = i;
    if (last < n / 2){
        cout << last + 1 << ' ' << n << ' ' << last + 2 << ' ' << n << '\n';
        return 0;
    }
    cout << 1 << ' ' << last + 1 << ' ' << 1 << ' ' << last << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}
