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
const int MAXN = 2e3 + 7;
int a[MAXN][MAXN];
int b[MAXN][MAXN];
int deg[MAXN];
bool used[MAXN];
deque<int> ans;
int order[MAXN];

int solve() {
    if (!(cin >> n >> m))
        return 1;
    ans.clear();
    fill(deg, deg + m, 0);
    fill(used, used + n, false);
    iota(order, order + n, 0);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> b[i][j];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j + 1 < n; j++) {
            if (b[j][i] > b[j + 1][i])
                deg[i]++;
        }
    }
    for (int i = 0; i < m; i++)
        if (deg[i] == 0)
            ans.push_back(i);
    for (int iter = 0; iter < SZ(ans); iter++) {
        int now = ans[iter];
        for (int i = 0; i + 1 < n; i++) {
            if (!used[i] && b[i][now] != b[i + 1][now]) {
                used[i] = true;
                for (int j = 0; j < m; j++) {
                    if (b[i][j] > b[i + 1][j]) {
                        deg[j]--;
                        if (deg[j] == 0)
                            ans.push_back(j);
                    }
                }
            }
        }
    }
    reverse(ALL(ans));
    for (int x : ans)
        stable_sort(order, order + n, [&](int i1, int i2) { return a[i1][x] < a[i2][x]; });
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++){
            if (a[order[i]][j] != b[i][j]){
                cout << "-1\n";
                return 0;
            }
        }
    cout << SZ(ans) << '\n';
    for (int x : ans)
        cout << x + 1 << ' ';
    cout << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("bukhalter.in", "r", stdin);
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
