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
#define int ll
const int MAXN = 1e3 + 7;
struct Query{
    int x1, y1, x2, y2;
    int x3, y3, x4, y4; 
    bool greater;
};

int n, m, q;
int r, c;
int arr[MAXN][MAXN], prefix[MAXN][MAXN];
Query queries[MAXN];

int get(int x1, int y1, int x2, int y2){
    int ans = prefix[x2][y2];
    if (x1)
        ans -= prefix[x1 - 1][y2];
    if (y1)
        ans -= prefix[x2][y1 - 1];
    if (x1 && y1)
        ans += prefix[x1 - 1][y1 - 1];
    return ans;
}
 
int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> arr[i][j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++){
            prefix[i][j] = arr[i][j];
            if (i > 0)
                prefix[i][j] += prefix[i - 1][j];
            if (j > 0)
                prefix[i][j] += prefix[i][j - 1];
            if (i > 0 && j > 0)
                prefix[i][j] -= prefix[i - 1][j - 1];
        }

    cin >> r >> c >> q;
    // cout << r << ' ' << c << ' ' << q << '\n';
    // cout << get(1, 1, 2, 2) << '\n';
    for (int i = 0; i < q; i++){
        int x, y;
        cin >> x >> y;
        --x, --y;
        int rr, cc;
        cin >> rr >> cc;
        queries[i].x1 = x;
        queries[i].y1 = y;

        queries[i].y2 = y + cc - 1;
        queries[i].x2 = x + rr - 1;

        int flag;
        cin >> flag;
        if (flag){
            queries[i].x3 = x + rr;
            queries[i].y3 = y;

            queries[i].x4 = x + 2 * rr - 1;
            queries[i].y4 = y + cc - 1;
        }
        else {
            queries[i].x3 = x;
            queries[i].y3 = y + cc;

            queries[i].x4 = x + rr - 1;
            queries[i].y4 = y + 2 * cc - 1;
        }
        cin >> queries[i].greater;
    }

    int best = 0;
    int x = 0, y = 0;
    // cout << get(3, 1, 4, 2) << '\n';
    for (int i = 0; i + r <= n; i++){
        for (int j = 0; j + c <= m; j++){
            int cur = 0;
            for (int k = 0; k < q; k++){
                auto now = queries[k];
                int sum1 = get(i + now.x1, j + now.y1, i + now.x2, j + now.y2);
                int sum2 = get(i + now.x3, j + now.y3, i + now.x4, j + now.y4);
                // cout << now.x1 + 1<< ' ' << now.y1 + 1 << ' ' << now.x2 + 1 << ' ' << 1 + now.y2 << '\n';
                // cout << i + now.x1 + 1<< ' ' << j + now.y1 + 1 << ' ' << i + now.x2 + 1 << ' ' << j + 1 + now.y2 << '\n';
                // cout << k << ' ' << sum1 << ' ' << sum2 << ' ' << now.greater << '\n';
                if (!now.greater){
                    if (sum1 < sum2)
                        cur++;
                }
                else {
                    if (sum1 >= sum2)
                        cur++;
                }

                if (cur + (q - k - 1) < best)
                    break;
            }
            // cout << i + 1 << ' ' << j + 1 << ' ' << cur << '\n';
            if (cur > best){
                best = cur;
                x = i;
                y = j;
            }
        }
    }
    cout << x + 1 << ' ' << y + 1 << '\n';
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