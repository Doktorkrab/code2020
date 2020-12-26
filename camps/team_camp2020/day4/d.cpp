#pragma GCC optimize("Ofast,unroll-loops")

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
const int MAXN = 1e6 + 7;
const int INF = 1e9;
const int ALP = 26;
char fld[MAXN];
//vector<vector<char>> fld;
int near_v[ALP][MAXN];
int near_h[ALP][MAXN];
//vector<vector<int>> near_v[ALP];
//vector<vector<int>> near_h[ALP];
int tmp[ALP];

int solve() {
    if (!(cin >> n >> m))
        return 1;
//    fld.resize(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> fld[i * m + j];
        }
    }
//    for (int i = 0; i < 26; i++) {
//        near_v[i].resize(n, vector<int>(m, INF));
//        near_h[i].resize(n, vector<int>(m, INF));
//    }
    for (int i = 0; i < n; i++) {
        fill(tmp, tmp + ALP, -INF);
        for (int j = 0; j < m; j++) {
            for (int c = 0; c < 26; c++)
                near_h[c][i * m + j] = tmp[c];
            tmp[fld[i * m + j] - 'a'] = j;
        }
        fill(tmp, tmp + ALP, INF);
        for (int j = m - 1; j >= 0; j--) {
            for (int c = 0; c < ALP; c++) {
                if (j - near_h[c][i * m + j] > tmp[c] - j)
                    near_h[c][i * m + j] = tmp[c];
            }
            tmp[fld[i * m + j] - 'a'] = j;
        }
    }
    for (int i = 0; i < m; i++) {
        fill(tmp, tmp + ALP, -INF);
        for (int j = 0; j < n; j++) {
            for (int c = 0; c < ALP; c++)
                near_v[c][j * m + i] = tmp[c];
            tmp[fld[j * m + i] - 'a'] = j;
        }
        fill(tmp, tmp + ALP, INF);
        for (int j = n - 1; j >= 0; j--) {
            for (int c = 0; c < ALP; c++)
                if (j - near_v[c][j * m + i] > tmp[c] - j)
                    near_v[c][j * m + i] = tmp[c];
            tmp[fld[j * m + i] - 'a'] = j;
        }
    }
    int q;
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        int r = INF;
        int c = INF;
        for (int cc = 0; cc < ALP; cc++)
            for (int ccc = 0; ccc < ALP; ccc++)
                if (cc != ccc) {
                    int r1 = near_v[cc][x * m + y];
                    int c1 = near_h[ccc][x * m + y];
                    if (abs(r1 - x) + abs(c1 - y) < abs(r - x) + abs(c - y)) {
                        r = r1;
                        c = c1;
                    }
                }
        if (r < 0 || c < 0 || r >= n || c >= m)
            cout << "-1\n";
        else
            cout << r + 1 << ' ' << y + 1 << ' ' << x + 1 << ' ' << c + 1 << '\n';
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
