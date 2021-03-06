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
int check(const vector<vector<int>>& arr) {
    int n = SZ(arr), m = SZ(arr[0]);
    vector<vector<int>> up(n, vector<int>(m));
    vector<vector<int>> left_dp(n, vector<int>(m));
    vector<vector<int>> right_dp(n, vector<int>(m));

//    for (int i = 0; i < n; i++)
//        for (int j = 0; j < m; j++)
//            cout << tmp[i][j] << " \n"[j + 1 == m];

    for (int i = 0; i < m; i++)
        up[0][i] = arr[0][i];
    for (int i = 1; i < n; i++)
        for (int j = 0; j < m; j++)
            if (arr[i][j])
                up[i][j] = up[i - 1][j] + 1;
            else
                up[i][j] = 0;
//    for (int i = 0; i < n; i++)
//        for (int j = 0; j < m; j++)
//            cout << up[i][j] << " \n"[j + 1 == m];
    int ans = 0;
    for (int i = 0; i < n; i++) {
        vector<pair<int, int>> stack;
        for (int j = 0; j < m; j++) {
            while (SZ(stack) && stack.back().first >= up[i][j])
                stack.pop_back();
            if (SZ(stack))
                left_dp[i][j] = stack.back().second + 1;
            else
                left_dp[i][j] = 0;
            stack.emplace_back(up[i][j], j);
        }
        stack.clear();
        for (int j = m - 1; j >= 0; j--) {
            while (SZ(stack) && stack.back().first >= up[i][j])
                stack.pop_back();
            if (SZ(stack))
                right_dp[i][j] = stack.back().second;
            else
                right_dp[i][j] = m;
            stack.emplace_back(up[i][j], j);
            ans = max(ans, up[i][j] * (right_dp[i][j] - left_dp[i][j]));
        }
    }
    return ans;
}

 
int solve() {
    if (!(cin >> n >> m))
        return 1;
    vector<vector<int>> arr(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
            arr[i][j] ^= 1;
        }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++){
        int l, r;
        cin >> l >> r;
        --l;
        cout << check(vector<vector<int>>(arr.begin() + l, arr.begin() + r)) << '\n';
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
