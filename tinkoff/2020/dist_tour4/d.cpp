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

int n, q;
const int MAXN = 1005;
const ll MOD = 1e9 + 7;
int arr[2 * MAXN][2 * MAXN];
vector<pair<int, int>> shift = {{0,  1},
                                {1, 0},
                                {0,  -1},
                                {-1,  0}};

void paint(int x, int y) {
    int now = 0;
    int cnt = (2 * n + 1) * (2 * n + 1);
    int end = 1;
    int end_cnt = 0;
    int now_c = 0;
    int num = 1;
    while (cnt > 0) {
//        cnt1++;
//        assert(cnt1 <= 20);
//        cerr << x << ' ' << y << ' ' << cnt << ' ' << end << ' ' << end_cnt << '\n';
        if (0 <= x && x <= 2 * n && 0 <= y && y <= 2 * n) {
            cnt--;
            arr[x][y] = num;
        }
        num++;

        auto[_x, _y] = shift[now];

        x += _x;
        y += _y;
        now_c++;
        if (now_c == end) {
            now++;
            if (now == 4)
                now = 0;
            now_c = 0;

            end_cnt++;
            if (end_cnt == 2) {
                end++;
                end_cnt = 0;
            }
        }
    }
}
ll mul(ll a, ll b){
    return (a * b) % MOD;
}
const ll rev = 500000004;
void solve1(){
    for (int i = 0; i < q; i++){
        int x, y, _;
        cin >> x >> y >> _;
        cin >> _;
        if (-x <= y && y <= x){
            ll kek = mul(8, mul(x, mul(x + 1, rev)));
            ll pos = -x;
            cout << (kek + (y - pos)) % MOD << '\n';
        }
        if (y > -x && y > x){
            
        }
    }
}
int solve() {
    if (!(cin >> n >> q))
        return 1;
    if (n > 1000){
        return 0;
    }
    paint(n, n);
//    for (int i = 0; i <= 2 * n; i++)
//        for (int j = 0; j <= 2 * n; j++)
//            cout << arr[i][j] << " \n"[j == 2 * n];
    for (int xx = 0; xx < q; xx++){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 += n;
        y1 += n;
        x2 += n;
        y2 += n;
//        cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << '\n';
        swap(x1, y1);
        swap(x2, y2);
        ll ans = 0;
        for (int i = x1; i <= x2; i++)
            for (int j = y1; j <= y2; j++) {
//                cout << arr[i][j] << ' ';
                ans = (ans + arr[i][j]) % MOD;
            }
//        cout << '\n';
        cout << ans << '\n';
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
