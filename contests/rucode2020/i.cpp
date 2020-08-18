#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,abm,mmx,popcnt,avx,avx2")
#include <bits/stdc++.h>
#include <ostream>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> orderedSet;


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

const int MAXN = 1e6 + 7;
const double eps = 1e-9;
int arr[MAXN];
bool check(double x){
    orderedSet have;
    for (int i = 0; i < n; i++)
            have.insert(i + 1);
    for (int i = 0; i < n; i++){
        int need = have.order_of_key(arr[i]);
        // cerr << x * n << ' ' << need << '\n';
        if (x * n > need){
            have.erase(arr[i]);
            continue;
        }
        return 0;
    }
    return 1;
}
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    double l = 0, r = 0.8;
    for (int i = 0; i < 80; i++){
        double m = (l + r) / 2;
        // cerr << m << ' ' << check(m) << '\n';
        if (!check(m))
            l = m;
        else
            r = m;
    }
    if (l > 0.5){
        cout << "-1\n";
        return 0;
    }
    cout << fixed << setprecision(15) << l << '\n';
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