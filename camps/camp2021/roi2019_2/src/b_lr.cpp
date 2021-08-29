#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;
#define int ll

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

int m, n, k;
const int MAXN = 2e5 + 7;
int l[MAXN];
int r[MAXN];
int arr[2 * MAXN];
vector<int> buckets[MAXN];
vector<ll> prefix[MAXN];
vector<ll> suffix[MAXN];

ll get(int h, int index) {
    if (h < l[index])
        return l[index] - h;
    if (h <= r[index])
        return 0;
    return h - r[index];
}

ll get_bucket(int bucket, int index) {
//    ll now = 0;
//    for (int x : buckets[bucket])
//        now += get(x, index);
//    return now;
    int l1 = (int)(lower_bound(ALL(buckets[bucket]), l[index]) - buckets[bucket].begin());
    int r1 = (int)(upper_bound(ALL(buckets[bucket]), r[index]) - buckets[bucket].begin());
    return l1 * l[index] - prefix[bucket][l1] - (SZ(buckets[bucket]) - r1) * r[index] + suffix[bucket][r1];
}


ll rec(int tl, int tr, int opt_l, int opt_r) {
    if (tr - tl + 1 <= 0)
        return 0;
    int tm = (tl + tr) / 2;
    ll best = TMAX(ll);
    int where = -1;

    for (int x = opt_l; x <= opt_r; x++) {
        ll now = get_bucket(tm, x);
        if (now < best) {
            best = now;
            where = x;
        }
    }
//    cout << tm << ' ' << best << ' ' << where + 1 << '\n';
    return rec(tl, tm - 1, opt_l, where) + rec(tm + 1, tr, where, opt_r) + best;
}

int solve() {
    if (!(cin >> m >> n >> k))
        return 1;
    for (int i = 0; i < n; i++)
        buckets[i].clear();
    vector<pair<int, int>> segs(k);
    for (int i = 0; i < k; i++) {
        cin >> segs[i].first >> segs[i].second;
    }
    sort(ALL(segs));
    int pnt = 0;
    int mx = -1;
    for (int i = 0; i < k; i++){
        if (mx >= segs[i].second)
            continue;
        l[pnt] = segs[i].first;
        r[pnt++] = segs[i].second;
        mx = segs[i].second;
    }
    for (int i = 0; i < n; i++)
        buckets[i].reserve(2 * m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < 2 * n; j++)
            cin >> arr[j];
        sort(arr, arr + 2 * n);
        for (int j = 0; j < n; j++) {
            buckets[j].push_back(arr[2 * j]);
            buckets[j].push_back(arr[2 * j + 1]);
        }
    }
    for (int i = 0; i < n; i++){
        sort(ALL(buckets[i]));
        prefix[i].resize(SZ(buckets[i]) + 1);
        suffix[i].resize(SZ(buckets[i]) + 1);
        for (int j = 0; j < SZ(buckets[i]); j++)
            prefix[i][j + 1] = prefix[i][j] + buckets[i][j];
        for (int j = SZ(buckets[i]) - 1; j >= 0; j--){
            suffix[i][j] = suffix[i][j + 1] + buckets[i][j];
        }
    }
    cout << rec(0, n - 1, 0, pnt - 1) << '\n';
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
