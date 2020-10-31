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
const int MAXN = 10;
ll ans = 0;
int chosen[MAXN];
void rec(int pos){
    if (pos == n){
        vector<int> cnt(m);
        for (int i = 0; i < n; i++)
            cnt[chosen[i]]++;
        bool good = true;
        for (int i : cnt)
            good &= (i > 0);
        ans += good;
        return;
    }
    for (int i = 0; i < m; i++){
        chosen[pos] = i;
        rec(pos + 1);
    }
}

 
int solve() {
    if (!(cin >> n >> m))
        return 1;
    ans = 0;
    rec(0);
    ll x = 1;
    for (int xx = 2; xx <= m; xx++)
        x *= xx;
    cout << ans << '\n';
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
