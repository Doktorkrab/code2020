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
const int MAXN = 27;
ll arr[MAXN][MAXN];
 
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i += 2)
        for (int j = 0; j < n; j++)
            arr[i][j] = (1LL << (i + j));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
            cout << arr[i][j] << " ";
        cout << endl;
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++){
        ll k;
        cin >> k;
        int x = 0, y = 0;
        int stage = 0;
        while (x != n - 1 || y != n - 1){
            cout << x + 1 << ' ' << y + 1 << endl;
            if (!stage){
                if (y + 1 < n && (k & (1LL << (x + y + 1))))
                    y++;
                else{
                    x++;
                    stage ^= 1;
                }
            }
            else {
                if (x + 1 < n && (k & (1LL << (x + y + 1)))){
                    x++;
                    stage ^= 1;
                }
                else
                    y++;
            }
        }
        cout << n << ' ' << n << '\n';
    }
    return 0;
}
 
signed main() {
    //ios::sync_with_stdio(0);
    //cin.tie(0);
    //cout.tie(0);
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
