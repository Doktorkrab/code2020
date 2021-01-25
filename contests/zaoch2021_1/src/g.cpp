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
 
int n, m, q;

const int MAXN = 505;
int field[MAXN][MAXN];
vector<pair<int, int>> shift = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
int type_1(int x){
    if (x == 0)
        return 1;
    if (x == 1)
        return 0;
    if (x == 2)
        return 3;
    if (x == 3)
        return 2;
}
int type_2(int x){
    if (x == 0)
        return 2;
    if (x == 1)
        return 3;
    if (x == 2)
        return 0;
    if (x == 3)
        return 1;
}
int find_ans(){
    int ans = 0;
    for (int start_y = 0; start_y < m; start_y++){
        int x = 0, y = start_y;
        int d = 0;
        while (x < n && x >= 0 && y >= 0 && y < m){
            if (field[x][y] == 1)
                d = type_1(d);
            else if (field[x][y] == 2)
                d = type_2(d);
            auto [sx, sy] = shift[d];
            x += sx;
            y += sy;
        }
        if (x == n)
            ans++;
    }
    return ans;
}
int solve() {
    if (!(cin >> n >> m >> q))
        return 1;
    for (int i = 0; i < q; i++){
        int x, y, c;
        cin >> c >> x >> y;
        field[x - 1][y - 1] = c;
        cout << find_ans() << '\n';
    }
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("g.in", "r", stdin);
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
