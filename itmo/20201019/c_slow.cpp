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
 
int n, q;
const int MAXN = 3e5 + 7;
int arr[MAXN];
 
int solve() {
    if (!(cin >> n >> q))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    for (int i = 0; i < q; i++){
        int type;
        cin >> type;
        if (type == 1){
            int l, r;
            cin >> l >> r;
            --l, --r;
            bool good = true;
            if (l <= r){
                for (int j = l; j < r; j++)
                    good &= (arr[j + 1] - arr[j] <= 1);
            }
            else {
                for (int j = l; j > r; j--) {
                    good &= (arr[j - 1] - arr[j] <= 1);
                }
            }
            if (good)
                cout << "YES\n";
            else
                cout << "NO\n";
        }
        if (type == 2){
            int l, r, d;
            cin >> l >> r >> d;
            --l;
            for (int j = l; j < r; j++)
                arr[j] += d;
        }
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
