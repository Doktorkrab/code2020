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
const int MAXN = 1e6 + 7;
vector<int> have[2][MAXN];
int choose[MAXN];
int solve() {
    if (!(cin >> n >> k))
        return 1;
    vector<int> perm(n);
    iota(ALL(perm), 1);
    for (int i = 0; i < k; i++){
        unordered_set<int> have1{ALL(perm)};
        int x;
        cin >> x;
        for (int j = 0; j < x; j++){
            int y;
            cin >> y;
            have1.erase(y);
            have[0][i].push_back(y);
        }
        for (int y : have1)
            have[1][i].push_back(y);
    }
    int best_mask = 0;
    int ans = 0;
    for (int mask = 0; mask < (1 << k); mask++){
        for (int i = 0; i < k; i++){
            int now = (mask >> i) & 1;
            for (int x : have[now][i])
                choose[x] = 1;
        }
        int now = 0;
        for (int i = 1; i <= n; i++) {
            now += choose[i];
            choose[i] = 0;
        }
        if (now > ans){
            ans = now;
            best_mask = mask;
        }
    }
//    for (int i = 0; i < k; i++)
//        cout << ((best_mask >> i) & 1);
//    cout << '\n';
    cout << ans << '\n';
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
