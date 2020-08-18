#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int VERYBIG = 1<<30;
const int MAXN = 20;

int n, k;
int v[MAXN][MAXN];

int ans;

int DP[MAXN][MAXN], cost[MAXN][MAXN], s[MAXN];

int main() {
  // freopen("partition.in", "r", stdin);
  // freopen("partition.out", "w", stdout);
  scanf("%d%d", &n, &k);
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
      scanf("%d", &v[i][j]);
    }
  }
  ans = VERYBIG;
  for(int mask = 0; mask < (1<<(n - 1)); ++mask) {
    int k1 = 0;
    for(int i = 0; i < n; ++i) {
      k1 += (mask >> i) % 2;
    }
    if(k1 <= k) {
      for(int i = 0; i < n; ++i) {
        memset(s, 0, sizeof(s));
        for(int i1 = i + 1; i1 <= n; ++i1) {
          cost[i][i1] = 0;
          int s1 = 0;
          for(int j = 0; j < n; ++j) {
            s[j] += v[i1 - 1][j];
            s1 += s[j];
            cost[i][i1] = max(cost[i][i1], s1);
            if((mask >> j) % 2 == 1) {
              s1 = 0;
            }
          }
        }
      }
      for(int k2 = 0; k2 <= n; ++k2) {
        for(int i = 0; i <= n; ++i) {
          DP[k2][i] = VERYBIG;
        }
      }
      DP[0][0] = 0;

      for(int k2 = 1; k2 <= n && k2 <= (k - k1 + 1); ++k2) {
        for(int i = 0; i < n; ++i) {
          for(int i1 = i + 1; i1 <= n; ++i1) {
            DP[k2][i1] = min(DP[k2][i1], max(DP[k2 - 1][i], cost[i][i1]));
          }
        }
        ans = min(ans, DP[k2][n]);
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}