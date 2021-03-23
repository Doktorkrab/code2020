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
ll k;
set<pair<ll, ll>> have;

int solve() {
    if (!(cin >> n >> k))
        return 1;
    have.clear();
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        char dir;
        cin >> dir;
        ll l;
        cin >> l;
        if (dir == 'S')
            y--;
        if (dir == 'W')
            x--;
        for (int j = 0; j < l; j++) {
            if (dir == 'N' || dir == 'S') {
                auto now = make_pair(x, y);
                if ((x + y) % 2 == 0)
                    have.emplace(x, y);
                else
                    have.emplace(x - 1, y), now.first--;
//                cout << now.first << ' ' << now.second << '\n';
                if (SZ(have) == k){
                    cout << now.first << ' ' << now.second << '\n';
                    return 1;
                }
                if (dir == 'N')
                    y++;
                else
                    y--;
            }
            if (dir == 'W' || dir == 'E'){
                auto now = make_pair(x, y);
                if ((x + y) % 2 == 0)
                    have.emplace(x, y);
                else
                    have.emplace(x, y - 1), now.second--;
                if (SZ(have) == k){
                    cout << now.first << ' ' << now.second << '\n';
                    return 1;
                }
                if (dir == 'W')
                    x--;
                else
                    x++;
            }
        }
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("e.in", "r", stdin);
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
