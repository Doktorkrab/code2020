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
int cnt[2];
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++){
        char x;
        cin >> x;
        arr[i] = (x == 'R');
    }
    int pnt = n - 1;
    cnt[0] = cnt[1] = 0;
    while (pnt >= 0 && arr[0] == arr[pnt]){
        cnt[arr[pnt]]++;
        pnt--;
    }
    if (pnt == -1){
        cout << (n - 1) / 3 + 1 << '\n';
        return 0;
    }
    int ans = 0;
    for (int i = 0; i < n; i++){
        ans += cnt[!arr[i]] / 3;
        cnt[!arr[i]] = 0;
        cnt[arr[i]]++;
    }
    if (arr[n - 1] != arr[0])
        ans += (cnt[0] / 3) + (cnt[1] / 3);
    cout << ans << '\n';
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
