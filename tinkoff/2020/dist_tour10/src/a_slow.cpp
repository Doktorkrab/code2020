#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

const int maxn = 1 << 17;
const int mod = 1e9 + 7;

int n;
string s;
int dp[maxn], a[maxn][2];

int main() {
//    freopen("binary.in", "r", stdin);
//    freopen("binary.out", "w", stdout);

    cin >> n >> s;
    dp[0] = 1;
    for (int i = 0; i <= n; i++) {
        if (i) {
            a[i][0] = (a[i][0] + a[i - 1][0]) % mod;
            a[i][1] = (a[i][1] + a[i - 1][1]) % mod;
        }
        if (i == n) break;
        dp[i] = (dp[i] + a[i][s[i] - '0']) % mod;
        if (i + 1 < n && s[i + 1] != '0') {
            a[i + 2][(s[i] - '0') ^ 1] = (a[i + 2][(s[i] - '0') ^ 1] + dp[i]) % mod;
        }
    }
    cout << (a[n][0] + a[n][1]) % mod << endl;

    return 0;
}