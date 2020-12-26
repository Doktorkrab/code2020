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
 
long long n;
long long b, c;
 
int solve() {
    if (!(cin >> n))
        return 1;
    cin >> b >> c;
    long long summ = n + b + c;
    vector<pair<long long, int>> slits = {{n, 1}, {b, 2}, {c, 3}};
    sort(ALL(slits));
    reverse(ALL(slits));
    if (slits[0].first == slits[1].first + slits[2].first) {
        cout << 0 << '\n';
    } else {
        cout << slits[0].second << '\n';
        cout << summ / 2 - slits[1].first << ' ' << summ / 2 - slits[2].first;
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
