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

const int INF = 1e9;
int n, m;
const int MAXN = 1e2 + 7;
int mat[MAXN][MAXN];
const int MAXM = 1e6 + 7;
int p[MAXM];
 
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++){
            char x;
            cin >> x;
            if (x == '1')
                mat[i][j] = 1;
            else if (i == j)
                mat[i][j] = 0;
            else
                mat[i][j] = INF;
        }

    cin >> m;
    for (int i = 0; i < m; i++){
        cin >> p[i];
        p[i]--;
    }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);

    vector<int> ans = {p[0]};
    int lst = 0;
    for (int i = 1; i < m; i++){
        // cout << i - lst << ' ' << mat[ans.back()][p[i]] << ' ' << ans.back() + 1 << "->" << p[i] + 1 << '\n';
        if (i - lst > mat[ans.back()][p[i]]){
            ans.push_back(p[i - 1]);
            lst = i - 1;
        }
    }
    ans.push_back(p[m - 1]);
    cout << SZ(ans) << '\n';
    for (int i : ans)
        cout << i + 1 << ' ';
    cout << '\n';
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