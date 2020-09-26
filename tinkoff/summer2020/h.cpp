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
 
int n, m, k, xs, ys;

const int MAXN = 55;
const int MAXK = 7;
int arr[MAXN][MAXN];
const vector<pair<int, int>> shift = {{-1, 0}, {0, 1}, {1, 0}, {0,-1}};
string s_dir = "URDL";
int used[4][MAXN][MAXN];
int prv[4][MAXN][MAXN];
int a[4][MAXK], b[4][MAXK];

bool check(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < m;
}

void find_cycle(int now_k){
    int x, y;
    cin >> x >> y;
    x--, y--;
    int dir = 0;
    char dd;
    cin >> dd;
    for (; dd != s_dir[dir]; dir++);
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            char c;
            cin >> c;
            arr[i][j] = c - '0';
            for (int g = 0; g < 4; g++){
                used[g][i][j] = 0;
                prv[g][i][j] = 0;
            }
        }
    }
    for (int i = 0; i < 4; i++){
        a[i][now_k] = -1;
        b[i][now_k] = -1;
    }
    int cnt = 0;
    while (used[dir][x][y] < 2){
        used[dir][x][y]++;
        if (x == xs && y == ys && used[dir][x][y] == 1)
            b[dir][now_k] = cnt;
        if (x == xs && y == ys && used[dir][x][y] == 2)
            a[dir][now_k] = cnt - prv[dir][x][y];
        prv[dir][x][y] = cnt;
        cnt++;
        dir = (dir + arr[x][y]) % 4;
        auto [_x, _y] = shift[dir];
        if (!check(x + _x, y + _y))
            dir = (dir + 2) % 4;
        x += shift[dir].first;
        y += shift[dir].second;
    }
    //for (int i = 0; i < 4; i++)
        //cout << a[i][now_k] << ' ' << b[i][now_k] << '\n';
    //cout << "xxxxxxxxxxxxx\n";

}

struct GCD_return{
    int x, y, d;
};

GCD_return gcd(int x, int y){
    if (y == 0)
        return {1, 0, x};
    auto ret = gcd(y, x % y);
    return {ret.y, ret.x - x / y * ret.y, ret.d};
}

int chosen[MAXK];
int ans = TMAX(int);

int mod(int x, int y){
    x %= y;
    if (x < 0)
        x += y;
    return x;
}

void rec(int pos){
    if (pos == k){
        int to_check = -1;
        vector<pair<int, int>> have;
        int mx = TMIN(int);
        for (int i = 0; i < k; i++) {
            if (a[chosen[i]][i] == -1){
                if (b[chosen[i]][i] == -1)
                    return;
                if (to_check == -1 || to_check == b[chosen[i]][i])
                    to_check = b[chosen[i]][i];
                else
                    return;
            } else {
                have.push_back({a[chosen[i]][i], mod(b[chosen[i]][i], a[chosen[i]][i])});
                mx = max(mx, b[chosen[i]][i]);
            }
        }
        assert(SZ(have) || to_check != -1);
        if (!SZ(have)){
            ans = min(ans, to_check);
            return;
        }
        int ans_t = have[0].second;
        int lcm = have[0].first;
        for (int i = 1; i < SZ(have); i++){
            auto ret = gcd(lcm, have[i].first);
            int x1 = ret.x;
            int d = ret.d;
            if ((have[i].second - ans_t) % d != 0)
                return;
            ans_t = mod(ans_t + x1 * (have[i].second - ans_t) / d % (have[i].first / d) * lcm, lcm * have[i].first / d);
            lcm = lcm * have[i].first / d;
        }
        //for (int i = 0; i < k; i++)
            //cout << s_dir[chosen[i]];
        //cout << '\n';
        //cout << ans_t << ' ' << lcm << ' ' << to_check << '\n';
        //cout << "xxxxxxxxxxxxxxxxxxxxxxx\n";
        if (ans_t < mx){
            int t = (mx - ans_t + lcm - 1) / lcm;
            ans_t += lcm * t;
        }
        ans_t -= (ans_t - mx) / lcm * lcm;
        if (to_check != -1){
            bool good = (to_check >= ans_t);
            for (auto [x, y] : have)
                good &= (mod(to_check, x) == y);
            if (!good)
                return;
            ans_t = to_check;
        }
        ans = min(ans, ans_t);
        return;
    }
    for (int i = 0; i < 4; i++){
        chosen[pos] = i;
        rec(pos + 1);
    }
}
int solve() {
    if (!(cin >> n >> m >> k >> xs >> ys))
        return 1;
    xs--, ys--;
    ans = TMAX(int);
    for (int i = 0; i < k; i++)
        find_cycle(i);
    rec(0);
    if (ans == TMAX(int))
        cout << "-1\n";
    else
        cout << ans << '\n';
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
