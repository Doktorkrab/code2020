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
set<ll> have;
map<ll, ll> cnt;
map<ll, map<ll, ll>> left_borders;
map<ll, vector<pair<ll, ll>>> borders_par;
map<ll, vector<ll>> borders_prefix;
vector<ll> added;
vector<pair<ll, ll>> lens;
vector<ll> prefix_lens;

void add() {
    while (SZ(have)){
        ll v = (*have.rbegin());
        cout << SZ(have) - 20 * ((int)3e5) << "\n";
        have.erase(v);
        ll l1 = 0, r1 = (v - 1) / 2;
        ll l2 = (v - 1) / 2 + 1, r2 = v;
        if (r1 - l1 > 0) {
            cnt[r1 - l1] += cnt[v], have.insert(r1 - l1);
            for (auto [x, y] : left_borders[v]) {
                left_borders[r1 - l1][x] += y;
            }
        }
        if (r2 - l2 > 0) {
            cnt[r2 - l2] += cnt[v], have.insert(r2 - l2);
            for (auto [x, y] : left_borders[v])
                left_borders[r2 - l2][x] += y;
        }
    }
}

unordered_map<ll, ll> kek;

ll restore_cnt(ll now, ll need){
    if (kek.count(now))
        return kek[now];
    if (now == need)
        return kek[now] = 1;
    if (now < need)
        return 0;
    ll l1 = 0, r1 = (now - 1) / 2;
    ll l2 = (now - 1) / 2 + 1, r2 = now;
    if (r1 - l1 > 0)
        kek[now] += restore_cnt(r1 - l1, need);
    if (r2 - l2 > 0)
        kek[now] += restore_cnt(r2 - l2, need);
    return kek[now];
}

ll get_pos(ll now, ll need, ll c){
    if (now == need)
        return 0;
    ll l1 = 0, r1 = (now - 1) / 2;
    ll l2 = (now - 1) / 2 + 1, r2 = now;
    if (r1 - l1 > 0){
        if (kek[r1 - l1] > c)
            return get_pos(r1 - l1, need, c);
        c -= kek[r1 - l1];
    }
    return l2 + get_pos(r2 - l2, need, c);
}


ll find_len(ll x){
    if (lens[0].first > x)
        return 0;
    int l = 0, r = SZ(cnt);
    while (r - l > 1){
        int mid = (l + r) / 2;
        if (prefix_lens[mid + 1] > x)
            r = mid;
        else
            l = mid;
    }
    return r;
}

ll find_parent(ll x, ll len){
    auto& prefixes = borders_prefix[len];
    if (prefixes[1] > x)
        return 0;
    int l = 0, r = SZ(prefixes);
    while (r - l > 1){
        int mid = (r + l) / 2;
        if (prefixes[mid + 1] <= x)
            l = mid;
        else
            r = mid;
    }
    return r;
}
unordered_map<ll, ll> left_to_len;
ll recover(ll x){
    ll need_index = find_len(x);
    if (need_index != 0)
        x -= prefix_lens[need_index];
    ll need = lens[need_index].second;
    ll parent_index = find_parent(x, need);
    ll parent = borders_par[need][parent_index].second;
    if (parent_index != 0)
        x -= borders_prefix[need][parent_index];
    kek.clear();
    restore_cnt(left_to_len[parent], need);
    return parent + get_pos(left_to_len[parent], need, x) + (need - 1) / 2;
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
        if (l != 0) {
            have.emplace(l);
            cnt[l]++;
            left_borders[l][prev] = 1;
            left_to_len[prev] = l;
        }
        prev = x + 1;
    }
    if (n - prev + 1 > 0) {
        have.emplace(n - prev + 1);
        cnt[n - prev + 1]++;
        left_borders[n - prev + 1][prev] = 1;
        left_to_len[prev] = n - prev + 1;
    }
    cout << SZ(have);
    return 0;
    add();
    lens.resize(SZ(cnt));
    prefix_lens.resize(SZ(cnt) + 1);
    int pnt = 0;
    for (auto [a, b] : cnt)
        lens[pnt++] = {b, a};
    reverse(ALL(lens));
    for (int i = 0; i < SZ(cnt); i++)
        prefix_lens[i + 1] = prefix_lens[i] + lens[i].first;
    for (auto [a, b] : left_borders){
        borders_par[a].resize(SZ(b));
        borders_prefix[a].resize(SZ(b) + 1);
        pnt = 0;
        for (auto [c, d] : b)
            borders_par[a][pnt++] = {d, c};
        for (int i = 0; i < SZ(b); i++)
            borders_prefix[a][i + 1] = borders_prefix[a][i] + borders_par[a][i].first;
    }
    for (int i = 0; i < q; i++){
        ll x;
        cin >> x;
        --x;
        if (x < m)
            cout << added[x] << '\n';
        else
            cout << recover(x - m) << '\n';
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
