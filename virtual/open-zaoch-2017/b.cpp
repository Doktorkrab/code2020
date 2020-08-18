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
 
int n, k;
const int MAXN = 3e5 + 7;
string s;
int poses[MAXN];
 
int solve() {
    if (!(cin >> k >> s))
        return 1;
    n = 0;
    for (int i = 0; i < SZ(s); i++){
        if (s[i] == '1')
            poses[n++] = i;
    }

    deque<int> have;
    int pnt = 0;
    for (; pnt < n && SZ(have) < k; pnt++)
        have.push_back(poses[pnt]);
    for (int i = 0; i < n; i++){
        have.pop_front();
        while (pnt < n && SZ(have) < k)
            have.push_back(poses[pnt++]);
        cout << 2 * (have.back() - poses[i]) << " \n"[i + 1 == n];
    }
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