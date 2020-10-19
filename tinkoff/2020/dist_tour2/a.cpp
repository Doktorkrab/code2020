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

const int MAXN = 5e5;
int n;
const unsigned rev = 3115528533; // 214013^(-1);
pair<unsigned, int> st[MAXN];


int solve() {
    if (!(cin >> n))
        return 1;
    unsigned x;
    cin >> st[0].first;
    st[0].second = 0;
    x = st[0].first;
    int pnt = 1;
    unsigned ans = 1;
    for (int i = 1; i < n; i++) {
        x = (x * 214013 + 2531011);
        int l = i;
        while (pnt > 0 && st[pnt - 1].first < x)
            --pnt;

        if (pnt == 0)
            l = 0;
        else
            l = st[pnt - 1].second + 1;
        if (pnt == 0 || st[pnt - 1].first > x)
            st[pnt++] = {x, i};
        ans += -l + 1;
    }
    pnt = 1;
    st[0] = {x, n - 1};
//    cout << x << '\n';
    for (int i = n - 2; i >= 0; i--) {
        x = (x - 2531011) * rev;
        int r = i;
        while (pnt > 0 && st[pnt - 1].first < x)
            --pnt;
        if (pnt == 0)
            r = n - 1;
        else
            r = st[pnt - 1].second - 1;
        if (pnt == 0 || st[pnt - 1].first > x)
            st[pnt++] = {x, i};
        ans += r;
    }
    cout << ans + n - 1 << '\n';
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
