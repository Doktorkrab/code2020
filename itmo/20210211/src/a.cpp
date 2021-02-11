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
 
int n, m;
const int MAXN = 50;
char arr[MAXN][MAXN];
pair<int, int> shift[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++)
            cin >> arr[i][j];
    }
    auto check = [&](int x, int y){
        return 0 <= x && x < n && 0 <= y && y < m && arr[x][y] == 'P';
    };
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++){
            if (arr[i][j] != 'W')
                continue;
            for (auto [sx, sy] : shift){
                if (check(i + sx, j + sy)){
//                    cout << i << ' ' << j << '\n';
//                    cout << sx << ' ' << sy << '\n';
                    cout << "No\n";
                    return 0;
                }
            }
        }
    cout << "Yes\n";
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
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
