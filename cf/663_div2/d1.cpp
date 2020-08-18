#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>

using namespace std;

#define  int long long
#define INF 1e14

int cst(int a, int b){
    bitset<5> c = a ^ b;
    return c.count();
}
signed main() {
    int n, m;
    cin >> n >> m;
    vector<string> lst;
    for (int i =0; i <n; i++){
        string s;
        cin >> s;
        lst.push_back(s);
    }
    if (n == 1){
        cout << "0\n";
        return 0;
    }
    if (n >= 4){
        cout << "-1\n";
        return 0;
    }
    vector<int> cur;
    for (int i =0; i < m; i++) {
        if (n == 1) {
            cur.push_back(lst[0][i] - '0');
        } else if (n == 2) {
            cur.push_back((lst[0][i] - '0') * 2 +  lst[1][i] - '0');
        } else if (n == 3) {
            cur.push_back((lst[0][i] - '0') * 4 + (lst[1][i] - '0') * 2 + (lst[2][i] - '0'));

        }
    }
    vector<vector<int>> dp(m);
    vector<vector<int>> lst1 = {{1}, {0}};
    vector<vector<int>> lst2 = {{1, 2}, {0, 3}, {0, 3}, {1, 2}};
    vector<vector<int>> lst3 = {{5, 2}, {3, 4}, {0, 7}, {6, 1}, {1, 6}, {0, 7}, {4, 3}, {5, 2}};
    int mn = INF;
    for (int i =0; i < m; i++){
        for (int j = 0; j < (1 << n); j++){
            dp[i].push_back(INF);
            int x = cst(j, cur[i]);
            if (i == 0){
                dp[i][j] = x;
                continue;
            }
            if (n == 1)
                dp[i][j] = min(dp[i][j], x + dp[i - 1][lst1[j][0]]);
            else if (n == 2){
                dp[i][j] = min(dp[i][j], x + dp[i - 1][lst2[j][0]]);
                dp[i][j] = min(dp[i][j], x + dp[i - 1][lst2[j][1]]);
            }
            else if (n == 3){
                dp[i][j] = min(dp[i][j], x + dp[i - 1][lst3[j][0]]);
                dp[i][j] = min(dp[i][j], x + dp[i - 1][lst3[j][1]]);
            }
            //cerr << dp[i][j] << " ";
        }
        //cerr << '\n';
    }
    for (int j =0; j < (1 << n); j++){
        mn = min(mn, dp[m - 1][j]);
    }
    cout << mn << '\n';
    return 0;

}
