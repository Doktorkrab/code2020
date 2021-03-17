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
const int MAXN = 1.5e3;
const int MAXQ = 11;
int arr[MAXN][MAXN];
bool used[MAXN * MAXN];
int ans[MAXN];
pair<int, int> colors[MAXN][MAXN][MAXQ];

int solve() {
    if (!(cin >> n >> q))
        return 1;
    fill(ans, ans + n, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> arr[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k <= q; k++)
                colors[i][j][k] = {-1, -1};
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            vector<pair<int, int>> nxt;
            nxt.emplace_back(0, arr[i][j]);
            if (i >= 1){
                for (int k = 0; k <= q; k++) {
                    if (colors[i - 1][j][k].first == -1)
                        break;
                    nxt.push_back(colors[i - 1][j][k]);
                    nxt.back().first++;
                }
            }
            if (j >= 1){
                for (int k = 0; k <= q; k++) {
                    if (colors[i][j - 1][k].first == -1)
                        break;
                    nxt.push_back(colors[i][j - 1][k]);
                    nxt.back().first++;
                }
            }
            if (i >= 1 && j >= 1){
                for (int k = 0; k <= q; k++) {
                    if (colors[i - 1][j - 1][k].first == -1)
                        break;
                    nxt.push_back(colors[i - 1][j - 1][k]);
                    nxt.back().first++;
                }
            }
            sort(ALL(nxt));
            int pnt = 0;
            for (auto [d, c] : nxt){
                if (used[c])
                    continue;
                used[c] = true;
                colors[i][j][pnt++] = {d, c};
                if (pnt > q)
                    break;
            }
            for (auto [d, c] : nxt)
                used[c] = false;
            int ans_now = min(i, j) + 1;
            if (colors[i][j][q].first != -1)
                ans_now = min(ans_now, colors[i][j][q].first);
            ans[ans_now + 1]++;
        }
    }
    int now = n * n;
    for (int i = 1; i <= n; i++){
        now -= ans[i];
        cout << now << '\n';
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("next_episode.in", "r", stdin);
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
