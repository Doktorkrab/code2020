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

int n, m, k;
const int MAXN = 15;
const int MAXK = 105;
int arr[MAXN][MAXN];
const pair<int, int> shift[] = {{0,  -1},
                                {0,  1},
                                {-1, 0},
                                {1,  0}};
int lst[MAXN][MAXN];
int wait[MAXN][MAXN];

int solve() {
    clock_t start = clock();
    if (!(cin >> n >> m >> k))
        return 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
            int cnt = 1, now = 1;
            while (now < arr[i][j]) {
                cnt++;
                now *= 2;
            }
            lst[i][j] = -1e9;
            wait[i][j] = cnt;
        }
    int ans = 0;
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    while ((clock() - start) * 1. / CLOCKS_PER_SEC < 0.45) {
        int x = 0, y = 0;
        bool good = true;
        int now = 0;
        for (int i = 0; i < k; i++) {
            now += arr[x][y];
            lst[x][y] = i;
            auto[xs, ys] = shift[rnd() % 4];
            int cnt = 0;
            while ((!(0 <= x + xs && x + xs < n && 0 <= y + ys && y + ys < m) ||
                   i - lst[x + xs][y + ys] < wait[x + xs][y + ys]) && cnt < 6) {
                auto t = shift[rnd() % 4];
                xs = t.first;
                ys = t.second;
                cnt++;
            }
            if (cnt == 6) {
                good = false;
                break;
            }
            x += xs;
            y += ys;
        }
        if (good && ans < now) {
            ans = now;
        }
    }
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
