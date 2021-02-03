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

int n;

int get_prefix_xor(int x) {
    int y = x % 4;
    if (y == 0)
        return x;
    if (y == 1)
        return 1;
    if (y == 2)
        return x + 1;
    return 0;
}

const int MAXN = 1e5 + 7;
pair<int, int> have[MAXN];

int get(int l, int r) {
    return get_prefix_xor(r) ^ get_prefix_xor(l - 1);
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> have[i].first >> have[i].second;
    int t = 0;
    for (int i = 0; i < n; i++)
        t ^= get(have[i].first, have[i].second);
    if (t == 0) {
        cout << "Lose\n";
        return 0;
    }
    cout << "Win\n";
    for (int i = 0; i < n; i++) {
        int now = 0;
        int j = 63;
        for (; j >= 0; j--) {
            if ((t >> j) & 1) {
                now |= (1LL << j);
                break;
            } else {
                now |= (1LL << j) & have[i].first;
            }
        }
        if (now < have[i].first) {
            assert((have[i].first & now) == now);
            for (; j >= 0; j--)
                now |= (1LL << j) & have[i].first;
        }
        if (have[i].first <= now && now <= have[i].second) {
            cout << now << " " << (t ^ now) << '\n';
            return 0;
        }
    }
    assert(0);
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
//    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}
