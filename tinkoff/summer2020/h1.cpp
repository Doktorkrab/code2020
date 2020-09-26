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
 
int n, m, k, xs, ys;
const vector<pair<int, int>> shift = {{-1, 0}, {0, 1}, {1, 0}, {0,-1}};
const int MAXN = 55;
const int MAXK = 7;
const int MAXANS = 1e6 + 7;
int arr[MAXK][MAXN][MAXN];
pair<int, int> pos[MAXK];
int dir[MAXK];
string s_dir = "URDL";

bool check(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < m;
}

int solve() {
    if (!(cin >> n >> m >> k >> xs >> ys))
        return 1;
    xs--, ys--;

    for (int x = 0; x < k; x++){
        cin >> pos[x].first >> pos[x].second;
        pos[x].first--, pos[x].second--;
        char c_dir;
        cin >> c_dir;
        dir[x] = 0;
        for (; s_dir[dir[x]] != c_dir; dir[x]++);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++){
                char y;
                cin >> y;
                arr[x][i][j] = y - '0';
            }
        //cerr << x << '\n';
    }
    int cnt = 0;
    while (cnt < MAXANS){
        //cerr << cnt << '\n';
        bool ok = true;
        for (int i = 0; i < k; i++)
            ok &= pos[i] == make_pair(xs, ys);
        if (ok){
            cout << cnt << '\n';
            return 0;
        }
        //if (cnt == 12)
            //for (int i = 0; i < k; i++)
                //cout << pos[i].first << ' ' << pos[i].second << '\n';
        for (int i = 0; i < k; i++){
            auto& [x, y] = pos[i];
            int& d = dir[i];
            d = (d + arr[i][x][y]) % 4;
            auto& [__x, __y] = shift[d];
            if (!check(x + __x, y + __y))
                d = (d + 2) % 4;
            auto [_x, _y] = shift[d];
            x += _x, y += _y;
        }
        cnt++;
    }
    cout << "-1\n";
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
