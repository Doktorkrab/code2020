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

const int INF = 1e9;
int n, s, t;
vector<int> have;
vector<vector<pair<int, int>>> g;
vector<int> d;
vector<char> used;
const int MAXN = 1e5 + 7;
pair<int, int> teleports[MAXN];

int solve() {
    if (!(cin >> n >> s >> t))
        return 1;
    have.push_back(s);
    have.push_back(t);
    for (int i = 0; i < n; i++) {
        cin >> teleports[i].first >> teleports[i].second;
        have.push_back(teleports[i].first);
        have.push_back(teleports[i].first + teleports[i].second);
        have.push_back(teleports[i].first - teleports[i].second);
    }
    sort(ALL(have));
    have.resize(unique(ALL(have)) - have.begin());
    auto upd = [&](int x){
        return (int)(lower_bound(ALL(have), x) - have.begin());
    };
    g.resize(SZ(have));
    d.resize(SZ(have), INF);
    used.resize(SZ(have));
    s = upd(s);
    t = upd(t);
    d[s] = 0;
    for (int i = 0; i < SZ(have); i++){
        if (i + 1 < SZ(have))
            g[i].emplace_back(i + 1, have[i + 1] - have[i]);
        if (i > 0)
            g[i].emplace_back(i - 1, have[i] - have[i - 1]);
    }
    for (int i = 0; i < n; i++){
        int x = upd(teleports[i].first);
        int l = upd(teleports[i].first + teleports[i].second);
        int r = upd(teleports[i].first - teleports[i].second);
        g[x].emplace_back(l, 0);
        g[x].emplace_back(r, 0);
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
    q.push({0, s});
    while (SZ(q)){
        auto [_, v] = q.top();
        q.pop();
        if (used[v])
            continue;
        used[v] = true;
        for (auto [u, w] : g[v]){
            if ((ll)(d[v] + w) < d[u]){
                d[u] = d[v] + w;
                q.push({d[u], u});
            }
        }
    }
//    for (int i = 0; i < SZ(have); i++)
//        cout << d[i] << " \n"[i + 1 == SZ(have)];
    cout << d[t] << '\n';
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
