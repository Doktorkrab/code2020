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
    if (!(cin >> s))
        return 1;
    n = s.size();
    vector<int> have(3, -1);
    int ans = 1e9;
    for (int i = 0; i < n; i++){
        int now = s[i] - '1';
        have[now] = i;
        int mn = min(have[0], min(have[1], have[2]));\
        if (mn >= 0){
            ans = min(ans, i - mn + 1);
        }
    }
    if (ans > n)
        cout << "0\n";
    else
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