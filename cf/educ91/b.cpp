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
string have = "RSP";
string ans = "PRS";
int cnt[3];
 
int solve() {
    if (!(cin >> s))
        return 1;
    for (int i = 0; i < 3; i++)
        cnt[i] = count(ALL(s), have[i]);
    int mx = max_element(cnt, cnt + 3) - cnt;
    for (int i = 0; i < SZ(s); i++)
        cout << ans[mx];
    cout << '\n';
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