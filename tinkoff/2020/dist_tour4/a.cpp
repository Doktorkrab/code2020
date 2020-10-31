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
const int MAXN = 55;
int arr[MAXN][MAXN];
vector<pair<int, int>> shift = {{-1, 0},
                                {0,  1},
                                {1,  0},
                                {0,  -1}};

void paint(int x, int y, int dir) {
    int now = 0;
    int dd = 0;
    if (dir == 0)
        dd = 1;
    else
        dd = -1;
    int cnt = n * m;
    int end = 1;
    int end_cnt = 0;
    int now_c = 0;
    int num = 1;
    int cnt1 = 0;
    while (cnt > 0) {
//        cnt1++;
//        assert(cnt1 <= 20);
//        cerr << x << ' ' << y << ' ' << cnt << ' ' << end << ' ' << end_cnt << '\n';
        if (0 <= x && x < n && 0 <= y && y < m) {
            cnt--;
            if (arr[x][y] > num)
                arr[x][y] = num;
        }
        num++;

        auto[_x, _y] = shift[now];

        x += _x;
        y += _y;
        now_c++;
        if (now_c == end){;
            now += dd;
            if (now < 0)
                now += 4;
            if (now == 4)
                now = 0;
            now_c = 0;

            end_cnt++;
            if (end_cnt == 2){
                end++;
                end_cnt = 0;
            }
        }
    }
}

int solve() {
    if (!(cin >> n >> m >> k))
        return 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            arr[i][j] = 1e9;
    for (int i = 0; i < k; i++){
        int a, b, c;
        cin >> a >> b >> c;
        paint(a - 1, b - 1, c);
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cout << arr[i][j] << " \n"[j + 1 == m];
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
