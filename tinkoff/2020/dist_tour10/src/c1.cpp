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

int n, k, q;
struct Shop{
    int x, t, a, b;
};
struct Query{
    int x, type, index;

    bool operator<(const Query &rhs) const {
        return std::tie(x, type, index) < std::tie(rhs.x, rhs.type, rhs.index);
    }
};
const int MAXN = 3e5 + 7;
const int MAXK = 405;
const int INF = 1e9 + 7;
Shop shops[MAXN];
pair<int, int> queries[MAXN];
const int SHOP_OPEN = -1, SHOP_CLOSE = 1, QUERY = 0;
Query scanline[3 * MAXN];

multiset<int> have_small[MAXK];
vector<int> solve_small(){
    vector<int> ans(q);
    for (int i = 0; i < n; i++){
        scanline[2 * i] = {shops[i].a, SHOP_OPEN, i};
        scanline[2 * i + 1] = {shops[i].b, SHOP_CLOSE, i};
    }
    for (int i = 0; i < q; i++)
        scanline[2 * n + i] = {queries[i].second, QUERY, i};
    sort(scanline, scanline + 2 * n + q);
    for (int i = 0; i < 2 * n + q; i++){
        const auto& e = scanline[i];
        if (e.type == SHOP_OPEN){
            const auto& shop = shops[e.index];
            have_small[shop.t].insert(shop.x);
        }
        if (e.type == SHOP_CLOSE){
            const auto& shop = shops[e.index];
            have_small[shop.t].erase(have_small[shop.t].find(shop.x));
        }
        if (e.type == QUERY){
            int l = queries[e.index].first;
            ans[e.index] = 0;
            for (int c = 1; c <= k; c++) {
                auto it = have_small[c].lower_bound(l);
                int cur = INF;
                if (it != have_small[c].end())
                    cur= (*it) - l;
                if (it != have_small[c].begin())
                    cur = min(cur, l - (*prev(it)));
                ans[e.index] = max(cur, ans[e.index]);
            }
            if (ans[e.index] == INF)
                ans[e.index] = -1;
        }
    }
    return ans;
}

int solve() {
    if (!(cin >> n >> k >> q))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> shops[i].x >> shops[i].t >> shops[i].a >> shops[i].b;
    for (int i = 0; i < q; i++)
        cin >> queries[i].first >> queries[i].second;
    auto ans = solve_small();
    for (int i = 0; i < q; i++)
        cout << ans[i] << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
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