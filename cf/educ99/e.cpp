#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
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
pair<int, int> have[4];

ll dist(const pair<int, int> &a, const pair<int, int> &b) {
    return abs(1LL * a.first - b.first) + abs(1LL * a.second - b.second);
}
int xs[4];
int ys[4];
int sides[32];
int solve() {
    if (!(cin >> have[0].first >> have[0].second))
        return 1;
    for (int i = 1; i < 4; i++)
        cin >> have[i].first >> have[i].second;
    int pnt = 0;
    for (int i = 0; i < 4; i++) {
        xs[i] = (have[i].first);
        ys[i] = (have[i].second);
        for (auto & j : have) {
            sides[pnt++] = ((have[i].first - j.first));
            sides[pnt++] = ((have[i].second - j.second));
        }
    }
    sort(sides, sides + 32);
    int cnt = unique(sides, sides + 32) - sides;
    vector<int> perm(4);
    iota(ALL(perm), 0);
    ll ans = 1e18;
    do {
        for (int x : xs)
            for (int y : ys) {
                for (int j = 0; j < cnt; j++) {
                    int side = sides[j];
                    ll now = 0;
                    vector<pair<int, int>> to_check = {{x, y}, {x + side, y}, {x, y + side}, {x + side, y + side}};
                    for (int i = 0; i < 4; i++)
                        now += dist(have[perm[i]], to_check[i]);
                    ans = min(ans, now);
                }
            }
    } while (next_permutation(ALL(perm)));
    cout << ans << '\n';
    return 0;
}

signed main() {
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
