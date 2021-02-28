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

ll n, m, q;
const int MAXN = 3e5 + 7;
set<pair<ll, ll>> have;
ll ans[MAXN];
vector<ll> added;

bool add(int x) {
    if (!SZ(have))
        return false;
//    cout << x << ": ";
//    for (auto[a, b] : have)
//        cout << "[" << -b << ", " << -b + a - 1 << "] ";
//    cout << "\n";
    auto[d, l] = (*have.rbegin());
    have.erase(prev(have.end()));

    l *= -1;
    ans[x] = l + (d - 1) / 2;
    ll l1 = l, r1 = l + (d - 1) / 2;
    ll l2 = l + (d - 1) / 2 + 1, r2 = l + d;
    if (r1 - l1 > 0)
        have.emplace(r1 - l1, -l1);
    if (r2 - l2 > 0)
        have.emplace(r2 - l2, -l2);
    return true;
}

int solve() {
    if (!(cin >> n >> m >> q))
        return 1;
    added.resize(m);
    ll prev = 1;
    for (int i = 0; i < m; i++)
        cin >> added[i];
    ll c = 1;
    for (ll x : added) {
        ll l = x - prev;
        ans[c++] = x;
        if (l != 0) {
            have.emplace(l, -prev);
        }
        prev = x + 1;
    }
    if (n - prev + 1 > 0)
        have.emplace(n - prev + 1, -prev);
    while (c < MAXN && add(c))
        c++;
    for (int i = 0; i < q; i++) {
        ll x;
        cin >> x;
        cout << ans[x] << '\n';
    }
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