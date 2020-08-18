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
    if (!(cin >> s))
        return 1;
    n = SZ(s);

    int cnt = 0;
    vector<int> have;
    for (int i = 0; i <= n; i++){
        if (s[i] == '0' || i == n){
            if (cnt)
                have.push_back(cnt);
            cnt = 0;
        }
        else
            cnt++;
    }
    sort(ALL(have));
    reverse(ALL(have));
    int ans = 0;
    for (int i = 0; i < SZ(have); i++)
        if (i % 2 == 0)
            ans += have[i];
    cout << ans << '\n';
    return 0;
}
 
signed main() {
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