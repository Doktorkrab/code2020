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

int n, q;

const int MAXN = 2e5 + 7;
const ll INF = 1e18;
ll arr[MAXN];
ll lft[MAXN];
ll rgt[MAXN];

int solve() {
    if (!(cin >> n >> q))
        return 1;
    arr[0] = -INF;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    arr[n + 1] = INF;
    fill(lft, lft + n + 2, -1);
    fill(rgt, rgt + n + 2, -1);
    ll mn = 0;
    ll mx = 0;
    ll pos = 0;
    set<pair<ll, int>> have; // (len, start)
    for (int i = 0; i <= n; i++)
        have.emplace(arr[i + 1] - arr[i], i);
    for (int i = 0; i < q; i++) {
        ll x;
        cin >> x;
        pos += x;
        mx = max(mx, pos);
        mn = max(mn, -pos);
        if (x > 0) {
            while (SZ(have) && have.begin()->first <= mx + mn){
                auto [d, j] = (*have.begin());
                have.erase(have.begin());
                ll d1 = d - min(mn, d);
                lft[j + 1] = min(mn, d);
                rgt[j] = d1;
            }
//            for (int j = 1; j <= n; j++) {
//                ll d = arr[j] - arr[j - 1];
//                if (lft[j] != -1)
//                    continue;
//                if (d > mx + mn)
//                    continue;
//            ll d1 = d - min(mn, d);
//            lft[j] = min(mn, d);
//            rgt[j - 1] = d1;
//            }
        }
        if (x < 0) {
            while (SZ(have) && have.begin()->first <= mx + mn){
                auto [d, j] = (*have.begin());
                have.erase(have.begin());
                ll d1 = d - min(mx, d);
                rgt[j] = min(mx, d);
                lft[j + 1] = d1;
            }
//            for (int j = 1; j <= n; j++) {
//                ll d = arr[j + 1] - arr[j];
//                if (rgt[j] != -1)
//                    continue;
//                if (d > mx + mn)
//                    continue;
//                ll d1 = d - min(mx, d);
//                rgt[j] = min(mx, d);
//                lft[j + 1] = d1;
//            }
        }
    }
//    for (int i = 1; i <= n; i++)
//        cout << lft[i] << " \n"[i == n];
//    for (int i = 1; i <= n; i++)
//        cout << rgt[i] << " \n"[i == n];
    for (int i = 1; i <= n; i++) {
        ll now = 0;
        if (lft[i] == -1)
            now += mn;
        else
            now += lft[i];
        if (rgt[i] == -1)
            now += mx;
        else
            now += rgt[i];
        cout << now << '\n';
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
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
