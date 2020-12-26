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
 
int n, k;
const int MAXN = 305;
const int INF = 1e9;
bool have[MAXN][MAXN];
ll d[MAXN][MAXN];
int cnt[MAXN];
int solve() {
    if (!(cin >> n >> k))
        return 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            d[i][j] =
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        for (int j = 0; j < x; j++){
            int y;
            cin >> y;
            have[i][y - 1] = true;
            cnt[y - 1]++;
        }
    }
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++){
            int mn = TMAX(int);
            for (int l = 0; l < k; l++)
                if (have[i][l] && have[j][l])
                    mn = min(mn, cnt[l]);

        }
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
