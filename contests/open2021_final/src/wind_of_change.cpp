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
vector<ll> s;

ll find_ans() {
    vector<set<ll>> sums(n + 1);
    sort(ALL(s));
    ll now = 0;
    for (int i = 0; i < n; i++){
        now += s[i];
        sums[i + 1].insert(now);
    }
    now = 0;
    for (int i = 0; i < n; i++){
        now += s[n - i - 1];
        sums[i + 1].insert(now);
    }
    ll ans = 0;
    vector<pair<ll, int>> events;
    for (int i = 0; i <= n; i++) {
        if (SZ(sums[i]) < 2)
            continue;
        events.emplace_back(*sums[i].begin(), 1);
        events.emplace_back(*sums[i].rbegin(), -1);
    }
    ll bal = 0;
    sort(ALL(events));
    for (int i = 0; i < SZ(events); i++) {
        if (i == 0 || events[i - 1].first != events[i].first){
            ll prev = 0;
            if (i)
                prev = events[i - 1].first;
            ans += (bal != 0) * (events[i].first - prev);
        }
        bal += events[i].second;
    }
    return ans;
}

int solve() {
    if (!(cin >> n >> q))
        return 1;
    s.resize(n);
    for (int i = 0; i < n; i++)
        cin >> s[i];
    cout << find_ans() << '\n';
    for (int i = 0; i < q; i++) {
        int t;
        ll x;
        cin >> t >> x;
        if (t == 1)
            s.push_back(x), n++;
        else
            s.erase(find(ALL(s), x)), n--;
        cout << find_ans() << '\n';
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("wind_of_change.in", "r", stdin);
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
