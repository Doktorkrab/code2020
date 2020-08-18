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
const int MAXN = 505;
bool arr[MAXN][MAXN];
int sumr[MAXN];
int sumc[MAXN];

 
int solve() {
    if (!(cin >> n >> k))
        return 1;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
            arr[i][j] = false;
        sumr[i] = sumc[i] = 0;
    }
    int x = 0, y = 0;
    int start = 1;
    for (int i = 0; i < k; i++){
        arr[x][y] = true;
        sumr[x]++;
        sumc[y]++;
        x++;
        y++;
        x %= n;
        if (y == n){
            y = 0;
            x = start++;
        }
    }
    // for (int i = 0; i < n; i++)
        // cout << sumr[i] << " \n"[i + 1 == n];
    // for (int i = 0; i < n; i++)
        // cout << sumc[i] << " \n"[i + 1 == n];
    int f1 = (*max_element(sumr, sumr + n)) - (*min_element(sumr, sumr + n));
    int f2 = (*max_element(sumc, sumc + n)) - (*min_element(sumc, sumc + n));
    cout << f1 * f1 + f2 * f2 << '\n';
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
            cout << arr[i][j];
        cout << '\n';
    }
    return 0;
}
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
   cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}