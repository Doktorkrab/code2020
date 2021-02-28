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

struct Vector {
    ll x, y;

    Vector operator-(const Vector &oth) const {
        return {x - oth.x, y - oth.y};
    }

    ll len2() {
        return x * x + y * y;
    }
};

struct Circle {
    Vector center;
    ll r;
};
const int MAXN = 3e5 + 7;
Circle have[MAXN];
int ans[MAXN];
void solve_slow(){
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++)
            if (ans[j] == -1 && (v == -1 || have[v].r < have[j].r))
                v = j;
        for (int j = 0; j < n; j++)
            if (ans[j] == -1 &&
                (have[j].center - have[v].center).len2() <= (have[v].r + have[j].r) * (have[v].r + have[j].r))
                ans[j] = v + 1;
    }
    for (int i = 0; i < n; i++)
        cout << ans[i] << " \n"[i + 1 == n];
}

void solve_one_line(){
    vector<pair<ll, pair<ll, ll>>> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = {have[i].center.x, {have[i].r, -i}};
    sort(ALL(arr));
    set<pair<pair<ll, ll>, ll>> setik;
    for (int i = 0; i < n; i++)
        setik.emplace(arr[i].second, i);
    for (int i = 0; i < n; i++){
        if (!SZ(setik))
            break;
        auto [r, v] = (*setik.rbegin());
        setik.erase({r, v});
        ll x = arr[v].first;
        auto lft = lower_bound(ALL(arr), make_pair(x - r.first, make_pair(0LL, 0LL))) - arr.begin();
        auto rgt = lower_bound(ALL(arr), make_pair(x + r.first + 1, make_pair(0LL, 0LL))) - arr.begin();
        for (int j = lft; j < rgt; j++)
            if (ans[-arr[j].second.second] == -1) {
                ans[-arr[j].second.second] = -arr[v].second.second + 1;
                setik.erase({arr[j].second, j});
            }
    }
    for (int i = 0; i < n; i++)
        cout << ans[i] << " \n"[i + 1 == n];
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++) {
        cin >> have[i].center.x >> have[i].center.y >> have[i].r;
    }
    fill(ans, ans + n, -1);
//    if (n <= 5000)
//        solve_slow();
//    else
        solve_one_line();
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("d.in", "r", stdin);
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
