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
const int MAXN = 2e5 + 7;
int arr[MAXN];
 
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    int pr = 0;
    while (pr < n && arr[pr] - 1 == pr)
        pr++;
    if (pr == n){
        cout << "0\n";
        return 0;
    }
    int sf = 0;
    while (sf >= 0 && arr[n - sf - 1] == n - sf)
        sf++;
    int in_pos = 0;
    for (int i = 0; i < n; i++)
        in_pos += (arr[i] - 1 == i);
    // cout << pr << ' ' << sf << ' ' << in_pos << '\n';
    if (in_pos == pr + sf)
        cout << "1\n";
    else
        cout << "2\n";
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