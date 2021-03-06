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


int solve() {
    if (!(cin >> n))
        return 1;
    string t;
    cin >> t;
    string have;
    clock_t start = clock();
    double stop = 1. * CLOCKS_PER_SEC * 2.5;
    for (int i = 1; clock() - start < stop; i++) {
        int was = SZ(have);
        have += to_string(i);
        for (int now = was; now < SZ(have); now++)
            if (now - n + 1 >= 0 && have.substr(now - n + 1, n) ==t){
                cout << now - n + 2 << ' ' << now + 1 << '\n';
                return 0;
            }
    }
    cout << "0 0\n";
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
