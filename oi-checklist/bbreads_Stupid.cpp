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
 bool check(const string& s){
    int bal = 0;
    for (char c : s){
        if (c == '(')
            bal++;
        else
            bal--;
        if (bal < 0)
            return false;
    }
    return bal == 0;
 }
int solve() {
    if (!(cin >> s))
        return 1;
    n = SZ(s);
    assert(n <= 20);
    ll ans = 0;
    for (ll mask = 0; mask < (1LL << n); mask++){
        string s1, s2;
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1LL)
                s1 += s[i];
            else
                s2 += s[i];
        if (!check(s1) || !check(s2))
            continue;
        // cout << "1:";
        // for (int i = 0; i < n; i++)
        //     if ((mask >> i) & 1LL)
        //         cout << s[i];
        //     else
        //         cout << ' ';
        // cout << '\n';
        // cout << "2:";
        // for (int i = 0; i < n; i++)
        //     if ((mask >> i) & 1LL)
        //         cout << ' ';
        //     else
        //         cout << s[i];
        // cout << '\n';
        // cout << '\n';
        ans += (check(s1) && check(s2));
        ans %= 2012;
    }
    // assert(ans < 2012);
    cout << ans % 2012 << '\n';
    return 0;
}
 
signed main() {
#ifndef LOCAL
    freopen("bbreeds.in", "r", stdin);
    freopen("bbreeds.out", "w", stdout);
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