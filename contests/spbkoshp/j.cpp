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
 
int n;
const int MAXLEN = 1e4 + 7;
const int MAXN = 1e3 + 1337;
const int INF = 1e9 + 7;
int dp[MAXLEN][MAXLEN];

int get_len(const string& s, const string& t){
    int n = SZ(s);
    int m = SZ(t);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            dp[i][j] = i + j;
    dp[0][0] = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++){
            dp[i + 1][j + 1] = min(min(dp[i][j + 1] + 1, dp[i + 1][j] + 1), dp[i][j] + (s[i] != t[j]));
        }
    return dp[n][m];
}
int matrix[MAXN][MAXN];
int d[MAXN];
bool used[MAXN];
int dp1[MAXN];
string have[MAXN];
int dfs(int v){
    if (used[v])
        return dp1[v];
    if (v == 1)
        return 0;
    used[v] = true;
    dp1[v] = -INF;
    for (int i = 0; i < n; i++)
        if (d[v] + matrix[v][i] == d[i] && i != v) {
            int t = dfs(i);
            dp1[v] = max(dp1[v], dfs(i) + 1);
        }
    return dp1[v];
}
int solve() {
    if (!(cin >> have[0] >> have[1] >> n))
        return 1;
    n += 2;
    for (int i = 2; i < n; i++)
        cin >> have[i];
    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++)
            matrix[i][j] = matrix[j][i] = get_len(have[i], have[j]);
    }
//    for (int i = 0; i < n; i++)
//        for (int j = 0; j < n; j++)
//            cout << matrix[i][j] << " \n"[j + 1 == n];
    fill(d, d + n, INF);
    d[0] = 0;
    for (int iter = 0; iter <= n; iter++){
        int min_val = -1;
        for (int j = 0; j < n; j++){
            if (!used[j] && (min_val == -1 || d[min_val] > d[j]))
                min_val = j;
        }
        if (min_val == -1)
            break;
        used[min_val] = true;
        for (int i = 0; i < n; i++){
            if (d[i] > d[min_val] + matrix[min_val][i])
                d[i] = d[min_val] + matrix[min_val][i];
        }
    }
    cout << d[1] << ' ';
    fill(used, used + n, 0);
    dfs(0);
    cout << dp1[0] - 1 << endl;
    int now = 0;
    vector<string> ans;
    while (now != 1){
        for (int i = 0; i < n; i++){
            if (i != now && d[now] + matrix[now][i] == d[i] && dp1[i] + 1 == dp1[now]){
                ans.push_back(have[i]);
                now = i;
                break;
            }
        }
//        cerr << now << '\n';
    }
    ans.pop_back();
//    reverse(ALL(ans));
    for (const string& s : ans)
        cout << s << '\n';
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
