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

const int MAXN = 1e3 + 7;
int n, m;
int arr[MAXN][MAXN];
int up[MAXN][MAXN];
int lft[MAXN][MAXN];
pair<int, int> have[MAXN][MAXN]; // (h, w)
ll cur_max[MAXN];
int pnts[MAXN];
int suff_max[MAXN][MAXN];
ll ans[MAXN][MAXN];
void calc_dp(){
    for (int j = 0; j < m; j++)
        up[0][j] = !arr[0][j];
    for (int i = 1; i < n; i++)
        for (int j = 0; j < m; j++)
            up[i][j] = (arr[i][j] ? 0 : 1 + up[i - 1][j]);
    
    for (int i = 0; i < n; i++){
        vector<pair<int, int>> stack;
        for (int j = 0; j < m; j++){
            while (SZ(stack) && stack.back().second >= up[i][j])
                stack.pop_back();
            if (SZ(stack))
                lft[i][j] = stack.back().first + 1;
            else
                lft[i][j] = 0;
            stack.emplace_back(j, up[i][j]);
        }
        stack.clear();
        for (int j = m - 1; j >= 0; j--){
            while (SZ(stack) && stack.back().second >= up[i][j])
                stack.pop_back();
            int now = 0;
            if (SZ(stack))
                now = stack.back().first;
            else
                now = m;
            stack.emplace_back(j, up[i][j]);
            have[i][j] = {up[i][j], now - lft[i][j]};
        }
        sort(have[i], have[i] + m);
        cur_max[i] = 0;
        pnts[i] = 0;
        suff_max[i][m] = 0;
        for (int j = m - 1; j >= 0; j--)
            suff_max[i][j] = max(suff_max[i][j + 1], have[i][j].second);
    }
}

void calc_ans(){
//    for (int i = 0; i < n; i++)
//        for (int j = 0; j < m; j++)
//            cout << "(" << have[i][j].first << ", " << have[i][j].second << ")" << " \n"[j + 1 == m];
    for (int r = 0; r < n; r++){
        for (int l = r; l >= 0; l--){
            ans[l][r] = ans[l + 1][r];
            while (pnts[r] < m && r - have[r][pnts[r]].first + 1 >= l){
                auto [a, b] = have[r][pnts[r]];
                cur_max[r] = max(cur_max[r], 1LL * a * b);
                pnts[r]++;
            }
            ans[l][r] = max(ans[l][r], max(cur_max[r], 1LL * (r - l + 1) * suff_max[r][pnts[r]]));
        }
    }
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            ans[i][j] = max(ans[i][j], ans[i][j - 1]);
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++)
            cin >> arr[i][j];
    }
    calc_dp();
    calc_ans();
//    for (int i = 0; i < n; i++)
//        for (int j = 0; j < n; j++)
//            cout << ans[i][j] << " \n"[j + 1 == n];
    int q;
    cin >> q;
    for (int i = 0; i < q; i++){
        int l, r;
        cin >> l >> r;
        cout << ans[l - 1][r - 1] << '\n';
    }
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
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
