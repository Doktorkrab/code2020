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

vector<pair<int, int>> figure = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
 
int solve() {
    if (!(cin >> n))
        return 1;
    int x = 1, y = 1;
    set<pair<int, int>> ans(ALL(figure));
    for (int i = 0; i < n; i++){
        for (auto [sx, sy] : figure)
            ans.insert({x + sx, y + sy});
        x += 1;
        y += 1;
    }
    cout << SZ(ans) << '\n';
    for (auto [x, y] : ans)
        cout << x << ' ' << y << '\n';
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