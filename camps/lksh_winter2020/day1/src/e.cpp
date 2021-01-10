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
pair<ll, ll> points[MAXN];
ll ans_min = TMAX(ll);
pair<ll, ll> a, b;
inline ll len(const pair<ll, ll>& a, const pair<ll, ll>& b){
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}
vector<pair<ll, ll>> find_ans(int tl, int tr) {
    if (tr - tl == 1) {
        return {points[tl]};
    }
    int tm = (tl + tr) / 2;
    auto l_ret = find_ans(tl, tm);
    auto r_ret = find_ans(tm, tr);
    vector<pair<ll, ll>> ans(tr - tl);
    merge(ALL(l_ret), ALL(r_ret), ans.begin(), [&](const pair<ll, ll>& a, const pair<ll, ll>& b){
        return tie(a.second, a.first) < tie(b.second, b.first);
    });
    vector<pair<int, int>> ans1;
    auto& p = points[tm - 1];
    for (auto& x : ans){
        if ((p.first - x.first) * (p.first - x.first) > ans_min)
            continue;
        ans1.emplace_back(x);
    }
    int sz = SZ(ans1);
    auto recalc = [&](int start, int side){
        for (int i = 1; i < 11 && start + i * side < sz && start + side * i >= 0; i++){
            if (len(ans1[start], ans1[i * side + start]) < ans_min){
                ans_min = len(ans1[start], ans1[i * side + start]);
                a = ans1[start];
//                cerr << "KEK\n";
                b = ans1[i * side + start];
//                cerr << start << ' ' << i * side + start << '\n';
            }
        }
    };
    for (int i = 0; i < sz; i++){
        recalc(i, 1);
        recalc(i, -1);
    }
    return ans;
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> points[i].first >> points[i].second;
    sort(points, points + n);
    find_ans(0, n);
//    cout << ans_min << '\n';
    cout << a.first << ' ' << a.second << '\n';
    cout << b.first << ' ' << b.second << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("e.in", "r", stdin);
#else
    freopen("rendezvous.in", "r", stdin);
    freopen("rendezvous.out", "w", stdout);
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
