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
int k;
 
int solve() {
    if (!(cin >> n >> k))
        return 1;
    vector<int> ans;
    for (int i = 1; i < k; i++){
        if (n < i){
            cout << "-1\n";
            return 0;
        }
        ans.push_back(i);
        n -= i;
    }
    if (n < k)
        cout << "-1\n";
    else {
        cout << SZ(ans) + 1 << '\n' << n << ' ';
        for (int x : ans)
            cout << x << ' ';
        cout << '\n';
    }
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
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
