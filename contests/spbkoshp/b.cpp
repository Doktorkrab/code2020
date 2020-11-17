#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;


#define SZ(x) (int)((x).size())
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()

#define TMAX(type) numeric_limits<type>::max()
#define TMIN(type) numeric_limits<type>::min()
#define int ll
#ifdef LOCAL
#define ass(X) assert(X)
#else
#define ass(X) {}
#endif

int n, L;
const int MAXN = 3e5 + 7;
int arr[MAXN];


int solve() {
    if (!(cin >> n >> L))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    int ans = n * (n - 1) * (n - 2) / 6;
    sort(arr, arr + n);
//    cout << ans << '\n';
    for (int i = 0; i < n; i++) {
        int l = 0, r = n;
        while (r - l > 1) {
            int m = (l + r) / 2;
            int coord = (i + m) % n;
            int d = arr[coord] - arr[i];
            if (d < 0)
                d += L;
            if (d > L / 2)
                r = m;
            else
                l = m;
        }
        if (r == n)
            continue;
        int gg = n - r - 1;
//        cout << i << ' ' << gg << '\n';
        ans -= gg * (gg + 1) / 2;
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
