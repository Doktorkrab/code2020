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
 
int n, m;
const int MAXN = 105;
char arr[MAXN][MAXN];

int solve() {
    if (!(cin >> n >> m))
        return 1;
    int x = min(n, m);
    int fnd = 0;
    for (int i = 2; i <= x; i++){
//        cout << i << ' ' << n % i << ' ' << m % i << '\n';
        if (n % i == 0 && m % i == 0){
            fnd = i;
            break;
        }
    }
    if (fnd == 0){
        cout << "NO\n";
        return 0;
    }
    string kek="BX";
    int pnt = 0;
    for (int i = 0; i < n; i += fnd){
        for (int j = 0; j < m; j += fnd){
            for (int i1 = 0; i1 < fnd; i1++)
                for (int j1 = 0; j1 < fnd; j1++)
                    arr[i + i1][j + j1] = kek[(i / fnd + j / fnd) % 2];
            pnt ^= 1;
        }
    }
    cout << "YES\n";
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++)
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
//    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}
