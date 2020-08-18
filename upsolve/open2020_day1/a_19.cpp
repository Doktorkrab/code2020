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
 
int n, t;
const int MAXN = 1e3 + 7;
int arr[MAXN];
int tmp[MAXN];
int tmp1[3]; 
int solve() {
    if (!(cin >> n >> t))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    bool changed = false;
    int cnt = 0;
    do {
        for (int i = 1; i + 1 < n; i++){
            tmp1[0] = arr[i - 1];
            tmp1[1] = arr[i];
            tmp1[2] = arr[i + 1];
            sort(tmp1, tmp1 + 3);
            tmp[i] = tmp1[1];
        }
        changed = false;
        for (int i = 1; i + 1 < n; i++){
            changed |= (tmp[i] != arr[i]);
            arr[i] = tmp[i];
        }
        for (int i = 0; i < n; i++)
            cout << arr[i] << " \n"[i + 1 == n];
        cnt += changed;
    } while (changed);
    cout << cnt << '\n';
    if (t == 1)
        for (int i = 0; i < n; i++)
            cout << arr[i] << " \n"[i + 1 == n]; 
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