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

int n, m;
const int MAXLOG = 20;
const int MAXN = 1 << MAXLOG;
int arr[MAXN];
int pos[MAXN];
int t_pos[MAXN];

int solve() {
    if (!(cin >> m))
        return 1;


    n = (1 << m);
    int need = n - 1;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        pos[arr[i]] = i;
    }
    if (m == 1){
        cout << "2\n";
        return 0;
    }
    for (int i = 0; i < n; i++)
        t_pos[arr[i]] = pos[need ^ arr[i]];
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = i; j >= 0; j--) {
            if (t_pos[arr[j]] >= j && t_pos[arr[j]] <= i)
                cnt++;
            if (((i - j + 1) > 2 * cnt) || cnt & 1) {
//                cout << j << ' ' << i << '\n';
                ans++;
            }
        }
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
