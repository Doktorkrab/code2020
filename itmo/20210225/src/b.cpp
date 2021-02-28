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
const int MAXN = 1e5 + 7;
const int MAXC = 505;
pair<ll, ll> arr[MAXN];

bool check(ll a, ll b, ll c) {
    return a < (b + c) && b < (a + c) && c < (a + b);
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i].first >> arr[i].second;
    vector<pair<ll, ll>> kek;
    for (int i = 0; i < n; i++) {
        if (arr[i].second < MAXC)
            kek.push_back(arr[i]);
    }
    n = SZ(kek);
    ll ans = TMAX(ll);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++)
            for (int k = j + 1; k < n; k++)
                if (check(kek[i].first, kek[j].first, kek[k].first))
                    ans = min(ans, kek[i].second + kek[j].second + kek[k].second);
    }
    if (ans != TMAX(ll))
        cout << ans << '\n';
    else
        cout << "-1\n";
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
