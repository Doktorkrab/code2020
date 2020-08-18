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

const int MAXN = 2e6 + 7;
const long double eps = 1e-9;
int arr[MAXN];
bool check(long double x){
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
    orderedSet have;
    for (int i = 0; i < n; i++)
            have.insert(i + 1);
    long double x = 0;
    for (int i = 0; i < n; i++){
        int need = have.order_of_key(arr[i]);
        x = max(x, 1.L * need / n);
        // cerr << need / n << '\n';
        if (x > 0.5){
            cout << "-1\n";
            return 0;
        }
        have.erase(arr[i]);
    }
    cout << fixed << setprecision(20) << x << '\n';
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