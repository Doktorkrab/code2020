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
vector<int> last_open;

bool ask(int l, int r) {
    cout << "? " << l + 1 << " " << r + 1 << endl;
    string ans;
    cin >> ans;
    return ans[0] == 'Y';
}

int solve() {
    if (!(cin >> n))
        return 1;
    string ans(n, '(');
    last_open.clear();
    for (int i = 0; i < n; i++) {
        if (SZ(last_open) == 0 || !ask(last_open.back(), i)) {
            ans[i] = '(';
            last_open.push_back(i);
        } else {
            last_open.pop_back();
            ans[i] = ')';
        }
    }
    cout << "! " << ans << endl;
    return 1;
}

signed main() {
//#ifdef LOCAL
//    freopen("d.in", "r", stdin);
//#endif
//    ios::sync_with_stdio(0);
//    cin.tie(0);
//    cout.tie(0);
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
