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
const int MAXN = 250007;
const int MAXC = 65536;
set<int> poses[MAXC];
int arr[MAXN];
 
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < MAXC; i++)
        poses[i].clear();
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        poses[arr[i]].insert(i);
    }
    int ans = MAXN;
    for (int i = 0; i < n; i++){
        poses[arr[i]].erase(i);
        if (i == n - i - 1){
            ans = 0;
            break;
        }
        if (SZ(poses[arr[i]])){
            auto x = poses[arr[i]].lower_bound(n - i - 1);
            if (x != poses[arr[i]].end())
                ans = min(abs(n - i - 1 - (*x)), ans);
            if (x != poses[arr[i]].begin()) {
                x = prev(x);
                ans = min(abs(n - i - 1 - (*x)), ans);
            }
        }
        poses[arr[i]].insert(i);
    }
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
