#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <ostream>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <vector>

using namespace std;

const int N = 51;

int n;
char f[N][N];
int dp[N][N][N][N];
bool ok_r[N][N][N], ok_c[N][N][N];

void print(int a, int b, int c, int d) {
    cout << a + 1 << ' ' << b + 1 << ' ' << c + 1 << ' ' << d + 1 << ": "
         << dp[a][b][c][d] << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    for (int a = 0; a < n; a++)
    for (int b = 0; b < n; b++)
    for (int c = 0; c < n; c++)
    for (int d = 0; d < n; d++)
        dp[a][b][c][d] = 1e9;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> f[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int a = 0; a < n; ++a) {
            for (int b = a; b < n; ++b) {
                if (a == b) {
                    ok_r[i][a][b] = (f[i][a] == '.');
                    ok_c[i][a][b] = (f[a][i] == '.');
                } else {
                    ok_r[i][a][b] = (f[i][b] == '.' && ok_r[i][a][b - 1]);
                    ok_c[i][a][b] = (f[b][i] == '.' && ok_c[i][a][b - 1]);
                }
            }
        }
    }
    for (int len_r = 1; len_r <= n; ++len_r) {
        for (int len_c = 1; len_c <= n; ++len_c) {
            for (int a = 0; a + len_r - 1 < n; ++a) {
                for (int b = 0; b + len_c - 1 < n; ++b) {
                    int c = a + len_r - 1;
                    int d = b + len_c - 1;
                    if (ok_r[a][b][d]) {
                        dp[a][b][c][d] = (a == c ? 0 : dp[a + 1][b][c][d]);
                    } else if (ok_r[c][b][d]) {
                        dp[a][b][c][d] = (a == c ? 0 : dp[a][b][c - 1][d]);
                    } else if (ok_c[b][a][c]) {
                        dp[a][b][c][d] = (b == d ? 0 : dp[a][b + 1][c][d]);
                    } else if (ok_c[d][a][c]) {
                        dp[a][b][c][d] = (b == d ? 0 : dp[a][b][c][d - 1]);
                    } else {
                        dp[a][b][c][d] = max(c - a + 1, d - b + 1);
                        for (int k = a + 1; k < c; ++k) {
                            if (ok_r[k][b][d]) {
                                dp[a][b][c][d] = min(dp[a][b][c][d],
                                                     dp[a][b][k - 1][d] + dp[k + 1][b][c][d]);
                            }
                        }
                        for (int k = b + 1; k < d; ++k) {
                            dp[a][b][c][d] =
                                    min(dp[a][b][c][d], dp[a][b][c][k - 1] + dp[a][k + 1][c][d]);
                        }
                    }
                }
            }
        }
    }
    print(0, 0, 1, 1);
    print(3, 3, 4, 4);
    print(0, 0, 1, 4);
    cout << dp[0][0][n - 1][n - 1];
    return 0;
}