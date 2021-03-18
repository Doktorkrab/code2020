#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


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
ll e;

const int MAXN = 3e5 + 7;
ll arr[MAXN];

int solve_slow() {
    int ans = 0;
    for (int i = 0; i < n; i++) {
        vector<ll> have;
        for (int j = i; j < n; j++) {
            have.push_back(arr[j]);
            if ((j - i + 1) % 2) {
                sort(ALL(have));
                ans += (have[SZ(have) / 2] == e);
            }
        }
    }
    return ans;
}

ll st[4 * MAXN];
int N;

void insert(int v, ll x) {
    st[v += N] += x;
    while (v > 1) {
        v /= 2;
        st[v] += x;
    }
}

int get(int v, int tl, int tr, ll need) {
    if (tr - tl == 1)
        return tl;
    int tm = (tl + tr) / 2;
    if (st[v * 2] >= need)
        return get(v * 2, tl, tm, need);
    return get(v * 2 + 1, tm, tr, need - st[v * 2]);
}

unordered_map<ll, int> was[2];
ll prefix[MAXN];

ll solve_once() {
    if (count(arr, arr + n, e) == 0)
        return 0;
    int pos = find(arr, arr + n, e) - arr;
    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + (arr[i] < e);
    was[0].clear();
    was[1].clear();
    for (int i = 0; i <= pos; i++) {
//        cout << i << ' ' << (i + 1) / 2 - prefix[i] << '\n';
        was[i % 2][(i + 1) / 2 - prefix[i]]++;
    }
    ll ans = 0;
    for (int i = pos + 1; i <= n; i++) {
//        cout << i << ' ' << (i + 1) / 2 - prefix[i] << ' ' << was[1 - (i % 2)][(i + 1) / 2 - prefix[i]] << '\n';
        ans += was[1 - (i % 2)][i / 2 - prefix[i]];
    }
    return ans;
}

ll prefix1[MAXN];
ll prefix2[MAXN];

ll solve_fast() {
    ll ans = 0;
//    if (count(arr, arr + n, e) < 2)
//        return solve_once();
    for (int i = 0; i < n; i++) {
        prefix1[i + 1] = prefix1[i] + (arr[i] < e);
        prefix2[i + 1] = prefix2[i] + (arr[i] <= e);
    }
    vector<ordered_set<pair<ll, int>>> was1(2);
    vector<ordered_set<pair<ll, int>>> was2(2);
    auto get_cnt = [&](const ordered_set<pair<ll, int>>& s, ll sum){
        auto it = s.lower_bound({sum, -1});
        if (it == s.end())
            return SZ(s);
        return (int)s.order_of_key(*it);
    };
    for (int i = 0; i <= n; i++){
        ll sum1 = 2 * prefix1[i] - i;
        ll sum2 = 2 * prefix2[i] - i;
        ll cnt1 = get_cnt(was1[1 - (i % 2)], sum1);
        ll cnt2 = get_cnt(was2[1 - (i % 2)], sum2);
        ans += cnt2 - cnt1;
        was1[i % 2].insert({2 * prefix1[i] - i, i});
        was2[i % 2].insert({2 * prefix2[i] - i, i});
    }
    return ans;
}



int solve() {
    if (!(cin >> n >> e))
        return 1;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    N = 1;
    vector<ll> to_sort(n + 1);
    for (int i = 0; i < n; i++)
        to_sort[i] = arr[i];
    to_sort[n] = e;
    sort(ALL(to_sort));
    to_sort.resize(unique(ALL(to_sort)) - to_sort.begin());
    for (int i = 0; i < n; i++)
        arr[i] = (int) (lower_bound(ALL(to_sort), arr[i]) - to_sort.begin());
    e = (int) (lower_bound(ALL(to_sort), e) - to_sort.begin());
    while (N < SZ(to_sort))
        N *= 2;

    cout << solve_fast() << '\n';
    return 0;
}

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

void gen() {
    n = rnd() % 20 + 1;
    const ll MAXN = 1e18;
    for (int i = 0; i < n; i++) {
        arr[i] = (ll) (rnd() % (2 * MAXN + 1)) - MAXN;
    }
    e = arr[rnd() % n];
}

void stress() {
    while (true) {
        gen();
        int a = solve_fast();
        int b = solve_slow();
        if (a != b) {
            cout << "WA!\n";
            cout << n << ' ' << e << '\n';
            for (int i = 0; i < n; i++)
                cout << arr[i] << " \n"[i + 1 == n];
            cout << "Fast: " << a << "\nSlow: " << b << '\n';
            exit(0);
        }
        cout << a << ' ' << b << '\n';
//        cout << ".";
    }
}

signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
#endif
//    cout << rnd.max() << '\n';
//    stress();
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
