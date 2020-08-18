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
 
const int MAXN = 2e5 + 7;
int n, k;
int arr[MAXN];
bool check(int x){
    int have = 0;
    // try <= in i%2==0
    for (int i = 0; i < n; i++){
        // cout << arr[i] << ' ' << x << '\n';
        if (arr[i] <= x){
            have++;
            continue;
        }
        if (have % 2 == 1)
            have++;
    }
    // cout << have << "!\n";
    if(have >= k)
        return true;
    have = 0;
    for (int i = 0; i < n; i++){
        if (arr[i] <= x){
            have++;
            continue;
        }
        if (have % 2 == 0)
            have++;
    }
    // cout << have << "!\n";
    return have >= k;
}
 
int solve() {
    if (!(cin >> n >> k))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int l = 0, r = 1e9 + 7;
    while (r - l > 1){
        int m = l + (r - l) / 2;
        if (!check(m))
            l = m;
        else
            r = m;
    }
    // cout << check(1) << '\n';
    cout << r << '\n';
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