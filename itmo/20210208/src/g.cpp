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
const int MAXN = 105;
const int PRIMES = 17;
const int MAXC = 61;
int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};
const int INF = 1e9;
int arr[MAXN];
int dp[MAXN][(1 << PRIMES)];
int fact[MAXC];
int p[MAXN][1 << PRIMES];

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < MAXC; i++)
        for (int j = 0; j < PRIMES; j++)
            fact[i] |= (1 << j) * (i % primes[j] == 0);

    for (int i = 0; i <= n; i++)
        for (int j = 0; j < (1 << PRIMES); j++)
            dp[i][j] = INF, p[i][j] = -1;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int now = 0; now < MAXC; now++) {
            int mask = (~fact[now]) & ((1 << PRIMES) - 1);
            for (int submask = mask;; submask = (submask - 1) & mask) {
                if (dp[i][submask] + abs(arr[i] - now) < dp[i + 1][submask | fact[now]]) {
                    dp[i + 1][submask | fact[now]] = dp[i][submask] + abs(arr[i] - now);
                    p[i + 1][submask | fact[now]] = now;
                }
                if (submask == 0)
                    break;
            }
        }
    }
    int now = 0;
    for (int mask = 0; mask < (1 << PRIMES); mask++){
        if (dp[n][mask] < dp[n][now]){
            now = mask;
        }
    }
    vector<int> ans;
    int x = n;
    while (x > 0){
        ans.push_back(p[x][now]);
        now &= ~(fact[ans.back()]);
        x--;
    }
    reverse(ALL(ans));
    for (int x : ans)
        cout << x << ' ';
    cout << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("g.in", "r", stdin);
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
