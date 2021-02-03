#pragma GCC optimize("O3,unroll-loops")

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

int n, m, c;
const int MAXN = 11;
int arr[MAXN][MAXN];
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

inline void gen_init() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            arr[i][j] = rnd() % c;
}

int have[MAXN][MAXN][3];

inline int cost() {
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < 3; k++)
                have[i][j][k] = 0;
    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = j + 1; k < m; k++) {
                if (arr[i][j] == arr[i][k])
                    ans += have[j][k][arr[i][j]]++;
            }
    return ans;
}

int solve() {
    if (!(cin >> n >> m >> c))
        return 1;
    if (c == 3) {
        vector<vector<int>> ans = {{2, 1, 3, 3, 1, 3, 2, 1, 2, 1},
                                   {1, 2, 1, 3, 2, 1, 3, 3, 2, 1},
                                   {2, 1, 3, 2, 3, 1, 3, 2, 1, 3},
                                   {1, 3, 2, 1, 2, 3, 2, 1, 1, 3},
                                   {3, 3, 3, 2, 2, 2, 1, 3, 1, 1},
                                   {1, 1, 2, 2, 3, 3, 1, 3, 2, 2},
                                   {2, 3, 1, 3, 3, 2, 1, 1, 3, 2},
                                   {2, 2, 2, 1, 1, 1, 1, 3, 3, 3},
                                   {3, 1, 1, 1, 2, 3, 3, 2, 3, 2},
                                   {3, 2, 1, 3, 1, 2, 2, 2, 1, 3}};
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cout << ans[i][j] << " \n"[j + 1 == m];
        return 0;
    }
    while (true) {
        gen_init();
        int now = cost();
        for (int iter = 0; iter < 50; iter++) {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++) {
                    int was = arr[i][j];
                    arr[i][j] = rnd() % c;
                    int nxt = cost();
                    if (nxt < now)
                        now = nxt;
                    else
                        arr[i][j] = was;
                }
        }
        if (now == 0) {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    cout << arr[i][j] + 1 << " \n"[j + 1 == m];
            return 0;
        }
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("c2.in", "r", stdin);
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
