#ifdef LOCAL
#  define _GLIBCXX_DEBUG
#else
#  define cerr __get_ce
#endif
#include <bits/stdc++.h>
#define ff first
#define ss second
#define szof(x) ((int)x.size())

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
int const INF = (int)1e9 + 1e3;
ll const INFL = (ll)1e18 + 1e6;
mt19937 tw(9450189);
uniform_int_distribution<ll> ll_distr;
ll rnd(ll a, ll b) { return ll_distr(tw) % (b - a + 1) + a; }


void solve() {
    int n;
    cin >> n;
    vector<pii> edges;
    for (int i = 0; i < n; ++i) {
        int ind;
        cin >> ind;
        if (ind != -1) {
            --ind;
            edges.push_back({i, ind});
        }
    }

    vector<int> arr(n);
    int ans = 0;
    for (int i = 0; i < 1 << n; ++i) {
        for (int j = 0; j < n; ++j) {
            arr[j] = (i >> j) & 1;
        }

        bool fl = true;
        for (pii e : edges) {
            if (arr[e.ff] && arr[e.ss]) {
                fl = false;
            }
        }

        if (fl) {
            ans = max(ans, __builtin_popcount(i));
        }
    }

    cout << ans << "\n";
}


signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
//    cin >> tests;
    for (int i = 1; i <= 1; i++) {
        solve();
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}
