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

struct Query{
    ll len, cnt, from;

    bool operator<(const Query &rhs) const {
        return make_pair(-len, from) < make_pair(-rhs.len, rhs.from);
//        return std::tie(len, from) < std::tie(rhs.len, rhs.from);
    }
};

ll n, m, q;
vector<Query> queries;
vector<ll> blocks;
vector<ll> lefts;

void add(ll start, ll pos, ll x){
    set<ll> have;
    blocks.push_back(start);
    have.insert(start);
    lefts.push_back(x);
    unordered_map<ll, ll> cnts;
    cnts[start] = 1;
    while (SZ(have)){
        auto top = (*have.rbegin());
        have.erase(top);
        ll l1 = 0, r1 = (top - 1) / 2;
        ll l2 = (top - 1) / 2 + 1, r2 = top;
        if (r1 - l1 > 0){
            have.insert(r1 - l1);
            cnts[r1 - l1] += cnts[top];
        }
        if (r2 - l2 > 0){
            have.insert(r2 - l2);
            cnts[r2 - l2] += cnts[top];
        }
    }
    for (auto [a, b] : cnts)
        queries.push_back({a, b, pos});
}

vector<ll> added;
unordered_map<ll, ll> cnts;

ll restore_cnt(ll x, ll need){
    if (x == need)
        return cnts[x] = 1;
    if (cnts.count(x))
        return cnts[x];
    ll l1 = 0, r1 = (x - 1) / 2;
    ll l2 = (x - 1) / 2 + 1, r2 = x;
    if (r1 - l1 > 0)
        cnts[x] += restore_cnt(r1 - l1, need);
    if (r2 - l2 > 0)
        cnts[x] += restore_cnt(r2 - l2, need);
    return cnts[x];
}

ll get_ans(ll x, ll need, ll finding){
    assert(finding >= 0);
    if (x == need)
        return (x - 1) / 2;
    assert(x > need);
    ll l1 = 0, r1 = (x - 1) / 2;
    ll l2 = (x - 1) / 2 + 1, r2 = x;
    ll cnt1 = cnts[r1 - l1];
    if (cnt1 > finding)
        return get_ans(r1 - l1, need, finding);
    return get_ans(r2 - l2, need, finding - cnt1) + l2;
}

int solve() {
    if (!(cin >> n >> m >> q))
        return 1;
    ll prev = 1;
    added.resize(m);
    for (int i = 0; i < m; i++){
        ll& x = added[i];
        cin >> x;
        if (x - prev > 0)
            add(x - prev, SZ(blocks), prev);
        prev = x + 1;
    }
    if (n - prev + 1 > 0)
        add(n - prev + 1, SZ(blocks), prev);
    sort(ALL(queries));
    vector<ll> prefix_sums(SZ(queries) + 1);
    for (int i = 0; i < SZ(queries); i++)
        prefix_sums[i + 1] = prefix_sums[i] + queries[i].cnt;
    for (int i = 0; i < q; i++){
        ll x;
        cin >> x;
        --x;
        if (x < m){
            cout << added[x] << '\n';
            continue;
        }
        x -= m;
        ll l = 0, r = SZ(queries) + 1;
        while (r - l > 1){
            ll mid = (l + r) / 2;
            if (x - prefix_sums[mid] < 0)
                r = mid;
            else
                l = mid;
        }
        ll need = r - 1;
        cnts.clear();
        restore_cnt(blocks[queries[need].from], queries[need].len);
        cout << get_ans(blocks[queries[need].from], queries[need].len, x - prefix_sums[r - 1]) +
                lefts[queries[need].from] << '\n';
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
