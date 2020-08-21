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
 
int n, m, x, y;
const int MAXN = 105;
bool used[MAXN][MAXN];
 
int solve() {
    if (!(cin >> n >> m >> x >> y))
        return 1;
    x--, y--;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            used[i][j] = false;
    //used[x][y] = true;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++, y = (y + 1) % m){
            if (used[x][y])
                continue;
            used[x][y] = true;
            cout << x + 1 << ' ' << y + 1 << '\n';
        }
        x = (x + 1) % n;
        y = (y - 1 + m) % m;
    }
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
