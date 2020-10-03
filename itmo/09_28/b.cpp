#include <bits/stdc++.h>
#include <ostream>
 
using namespace std;
using ll = long long;

#define int ll
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
int c1, c2;
multiset<pair<int, pair<int, int>>> kek;
const int MAXN = 2e6 + 7;
int nxt[MAXN];
bool used[MAXN];
int solve() {
    if (!(cin >> c1 >> c2 >> n))
        return 1;
    int inf = 1e9 + 7;
    for (int i = 0; i < n; i++){
        int a, b;
        cin >> a >> b;
        kek.insert({b, {-inf, a}});
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        nxt[i] = b;
        kek.insert({a, {c1, i}});
        kek.insert({b, {c2, i}});
    }
    int ans = 0;
    int cur = 0;
    while (SZ(kek)){
        auto [t, tt] = (*kek.begin());
        kek.erase(kek.begin());
        auto [type, x] = tt;
        if (type == -inf)
            cur += x;
        else {
            assert(x < m);
            if (!used[x]){
                if (cur >= type){
                    used[x] = true;
                    ans++;
                    cur -= type;
                }
                //nxt[x] = -1;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("bestbuy.in", "r", stdin);
    freopen("bestbuy.out", "w", stdout);
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
