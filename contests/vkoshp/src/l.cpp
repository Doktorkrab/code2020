#pragma GCC optimize("O3")

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

#define int long long

const int N = 1e5;

int n, w;
struct Item {
    int w, c, i;
};
Item big[N];
Item small[N];

int solve() {
    if (!(cin >> n >> w))
        return 1;
    int old_w = w;
    w = 3LL * w / 2;
    int pnt_s = 0;
    int pnt_b = 0;
    for (int i = 0; i < n; ++i) {
        Item now;
        cin >> now.w >> now.c;
        now.i = i;
        if (now.w * 2 <= old_w)
            small[pnt_s++] = now;
        else
            big[pnt_b++] = now;

    }
    sort(big, big + pnt_b, [&](const Item &a, const Item &b) {
        return a.w > b.w;
    });
    sort(small, small + pnt_s, [&](const Item &a, const Item &b) {
        return a.c * b.w > b.c * a.w;
    });
    int ans = 0;
    vector<int> best;
    int r = 0;
    int pr = 0;
    int pr_w = 0;
    vector<int> now_v;
    big[pnt_b++] = {0, 0, -1};
    for (int i = 0; i < pnt_b; i++){
        int now = big[i].c + pr;
        int have = big[i].w + pr_w;
        if (have > w)
            continue;
        while (r < pnt_s && have + small[r].w <= w){
            pr_w += small[r].w;
            pr += small[r].c;
            now += small[r].c;
            have += small[r].w;
            now_v.push_back(small[r].i);
            r++;
        }
        if (now > ans){
            ans = now;
            best = now_v;
            if (big[i].i != -1)
                best.push_back(big[i].i);
        }
    }
//    cout << ans << '\n';
    cout << SZ(best) << '\n';
    for (int x : best)
        cout << x + 1 << " ";
    cout << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("l.in", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}
