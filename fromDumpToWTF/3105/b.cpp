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
string s;
 
int solve() {
    if (!(cin >> n >> s))
        return 1;
    int have = 0;
    int mn = 0;
    int mx = 0;
    for (int i = 0; i < n / 2; i++){
        if (s[i] == '?')
            mn -= 9;
        else
            have -= s[i] - '0';
    }

    for (int i = n / 2; i < n; i++){
        if (s[i] == '?')
            mx += 9;
        else
            have += s[i] - '0';
    }
    mn += have;
    mx += have;
    if (mn + mx == 0)
        cout << "Bicarp\n";
    else
        cout << "Monocarp\n";
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