#include <algorithm>
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
const int MAXN = 1505;
int a[MAXN][MAXN];

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    vector<int> have(n);
    iota(ALL(have), 0);
    int ans = TMAX(int);
    do {
        vector<bool> used(n);
        bool good = true;
        for (int i = 0; i < n; i++){
            int cnt = 0;
            for (int j = 0; j < have[i]; j++)
                cnt += used[have[j]];
            if (cnt != 0 && cnt != have[i]){
                good = false;
                break;
            }
            used[have[i]] = true;
        }
        if (good){
            int now = 0;
            for (int i = 0; i + 1 < n; i++){
                //cout << have[i] << ' ' << have[i + 1] << ' ' << a[have[i]][have[i + 1]] << '\n';
                now += a[have[i]][have[i + 1]];
            }
            //cout << now << '\n';
            if (now == 10){
                for (int i : have)
                    cout << i + 1 << ' ';
                cout << '\n';
            }
            ans = min(ans, now);
        }
    } while(std::next_permutation(ALL(have)));
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
