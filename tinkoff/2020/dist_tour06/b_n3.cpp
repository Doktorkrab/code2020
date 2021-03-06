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
const int MAXLOG = 20;
const int MAXN = (1 << MAXLOG) + 7;
int arr[MAXN];
bool have[MAXN];

int solve() {
    if (!(cin >> n))
        return 1;
    int N = (1 << n);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        have[arr[i]] = 1;
    }
    int need = N - 1;
    ll ans = 0;
    for (int i = 0; i < N; i++) {
        ll xx = 0;
        bool was = true;
        for (int j = i; j >= 0; j--) {
            bool prev = was;
            was = false;
            xx ^= arr[j];
            have[arr[j]] = 0;
            if (xx == need && (i - j + 1 >= 2 || N - (i - j + 1) >= 2)) {
                ans++;
                cout << j << ' ' << i << '\n';
                was = true;
            } else {
                for (int k = j; k <= i; k++) {
                    if (have[xx ^ arr[k] ^ need]) {
                        ans++;
                        cout << j << ' ' << i << '\n';
                        was = true;
                        break;
                    }
                }
            }
        }
        for (int j = 0; j <= i; j++)
            have[arr[j]] = 1;
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
