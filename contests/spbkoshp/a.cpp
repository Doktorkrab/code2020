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

const int N = 100;
//#ifdef LOCAL
//const int A = 10;
//#else
const int A = 1e6 + 7;
//#endif

int n;
int a[N];
bitset<A> dp;

int solve() {
    if (!(cin >> n))
        return 1;
    dp[0] = 1;
    int s = 0;
    for (int i = 0; i < n; ++i){
        cin >> a[i];
        s += a[i];
        dp |= dp << a[i];
    }
    int cur = 0;
    long long c = 0, ans = 0;
    int kek = 0;
    for (int h = A - 1; h >= 0; --h){
        if (dp[h]){
            if (h == 0 || h == s){
                continue;
            }
            ++kek;
            ans += 2 * (s - h + 1);
            c += cur + 1;
            ++cur;
        }
    }
    ans = ans - c + 2 * s + 1 - 2 * kek;
    cout << ans << '\n';
    return 0;
}

signed main() {
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);
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
