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
ll arr[MAXN];
ll arr1[MAXN];

struct Fenwick {
    vector<ll> tree;
    int sz;

    Fenwick(int sz_) : tree(sz_), sz(sz_) {}

    Fenwick() : tree(0), sz(0) {}

    ll get(int r) {
        ll ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += tree[r];
        return ret;
    }

    void upd(int pos, ll x) {
        for (; pos < sz; pos |= pos + 1)
            tree[pos] += x;
    }
};

Fenwick cnt_le, cnt_gt;
Fenwick sum_le, sum_gt;
vector<ll> to_sort_le, to_sort_gt;

ll get_cnt(ll x, int ind) {
//    cout << x << ' ' << ind << '\n';
//    cout << ' ' << (int) (upper_bound(ALL(to_sort_le), x - ind) - to_sort_le.begin()) - 1 << '\n';
//    cout << '\t' << cnt_le.get((int) (upper_bound(ALL(to_sort_le), x - ind) - to_sort_le.begin()) - 1) << ' ';
//    cout << cnt_gt.get((int) (upper_bound(ALL(to_sort_gt), x + ind) - to_sort_gt.begin()) - 1) << '\n';
    return cnt_le.get((int) (upper_bound(ALL(to_sort_le), x - ind) - to_sort_le.begin()) - 1) +
           cnt_gt.get((int) (upper_bound(ALL(to_sort_gt), x + ind) - to_sort_gt.begin()) - 1);
}

ll relax(ll x, int ind) {
    ll ans = 0;
    int le = (int) (upper_bound(ALL(to_sort_le), x - ind) - to_sort_le.begin()) - 1;
    int gt = (int) (upper_bound(ALL(to_sort_gt), x + ind) - to_sort_gt.begin()) - 1;
//    ind++;
    ans += (x - ind) * cnt_le.get(le) - sum_le.get(le);
    ans += sum_le.get(n - 1) - sum_le.get(le) - (x - ind) * (cnt_le.get(n - 1) - cnt_le.get(le));
    ans += (x + ind) * cnt_gt.get(gt) - sum_gt.get(gt);
    ans += sum_gt.get(n - 1) - sum_gt.get(gt) - (x + ind) * (cnt_gt.get(n - 1) - cnt_gt.get(gt));

    return ans;
}

int solve() {
    if (!(cin >> n))
        return 1;
    cnt_le = Fenwick(n + 1);
    cnt_gt = Fenwick(n + 1);
    sum_le = Fenwick(n + 1);
    sum_gt = Fenwick(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        to_sort_le.push_back(arr[i] - i);
        to_sort_gt.push_back(arr[i] + i);
    }
    sort(ALL(to_sort_le));
    sort(ALL(to_sort_gt));
    to_sort_le.erase(unique(ALL(to_sort_le)), to_sort_le.end());
    to_sort_gt.erase(unique(ALL(to_sort_gt)), to_sort_gt.end());

    for (int i = 1; i <= n; i++) {
        cnt_gt.upd(lower_bound(ALL(to_sort_gt), arr[i] + i) - to_sort_gt.begin(), 1);
        sum_gt.upd(lower_bound(ALL(to_sort_gt), arr[i] + i) - to_sort_gt.begin(), arr[i] + i);
    }

    ll ans = TMAX(ll);
    for (int i = 1; i <= n; i++) {
        ll le = lower_bound(ALL(to_sort_le), arr[i] - i) - to_sort_le.begin();
        ll gt = lower_bound(ALL(to_sort_gt), arr[i] + i) - to_sort_gt.begin();

        cnt_le.upd(le, 1);
        sum_le.upd(le, arr[i] - i);

        cnt_gt.upd(gt, -1);
        sum_gt.upd(gt, -(arr[i] + i));

        ll l = max(i, n + 1 - i), r = 1e9 + 1e6;
//        cout << l << '\n';
        while (r != l) {
            ll m = (l + r) / 2;
            if (get_cnt(m, i) >= (n + 1) / 2)
                r = m;
            else
                l = m + 1;
        }
//        ++l;
//        get_cnt(4, i);
//        cout << i << ' ' << l << ' ';
//        cout << relax(l, i) << '\n';
        ans = min(ans, relax(l, i));
    }
    cout << ans << '\n';
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
