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
const int MAXN = 505;
int arr[MAXN];
int t[MAXN];
int used[2];
 
int solve() {
    if (!(cin >> n))
        return 1;
    used[0] = used[1] = 0;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    for (int i = 0; i < n; i++){
        cin >> t[i];
        // cout << t[i] << ' ';
        used[t[i]] = 1;
    }
    // cout << '\wn';
    bool good = 1;
    for (int i = 1; i < n; i++){
        if (arr[i] < arr[i - 1]){
            good = 0;
            break;
        }
    }
    if (good){
        cout << "Yes\n";
        return 0;
    }
    if (used[0] + used[1] != 2){
        cout << "No\n";
        return 0;
    }
    cout << "Yes\n";
    return 0;
}
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
   cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}