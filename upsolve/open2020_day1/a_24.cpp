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
const int MAXN = 5e5 + 7;
int arr[MAXN];
bool stable[MAXN];
 
int solve() {
    if (!(cin >> n >> t))
        return 1;
    for (int i = 0; i < n; i++){
        cin >> arr[i];
        stable[i] = false;
    }
    stable[0] = stable[n - 1] = true;
    for (int i = 1; i + 1 < n; i++)
        if (arr[i - 1] == arr[i] || arr[i] == arr[i + 1])
            stable[i] = true;

    int start = 0;
    int len = 0;
    int ans = 0;
    for (int i = 0; i < n; i++){
        if (!stable[i]){
            if (len == 0)
                start = i;
            len++;
            continue;
        }
        if (len == 0)
            continue;
        ans = max(ans, (len + 1) / 2);
        for (int j = 0; j < len / 2; j++)
            arr[start + j] = arr[start - 1];
        for (int j = len / 2; j < len; j++)
            arr[start + j] = arr[i];
        len = 0;
    }
    cout << ans << '\n';
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