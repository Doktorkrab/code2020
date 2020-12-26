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

const int MOD = 1e9 + 7;
int add(int a, int b){
    return (1LL * a + b) % MOD;
}
int mul(int a, int b){
    return (1LL * a * b) % MOD;
}
int h, w, n;
const int MAXN = 1e3;
int fld[MAXN][MAXN];
int a[4][MAXN];
string s;
int solve() {
    if (!(cin >> h >> w >> n))
        return 1;
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            fld[i][j] = (i * w + j);
    cin >> s;
    for (int i = 0; i < 4; i++){
        int x;
        cin >> x;
        for (int j = 0; j < x; j++)
            cin >> a[i][j];
    }
    for (int i = 0; i < n; i++){
        if (s[i] == 'c'){
            cout << 'c' << ' ' << a[1][i] << ' ' << a[3][i] << '\n';
            for (int j = 0; j < h; j++)
                swap(fld[j][a[1][i]], fld[j][a[3][i]]);
        }
        if (s[i] == 'r'){
            cout << 'r' << ' ' << a[0][i] << ' ' << a[2][i] << '\n';

            for (int j = 0; j < w; j++)
                swap(fld[a[0][i]][j], fld[a[2][i]][j]);
        }
        if (s[i] == 'f'){
            cout << 'f' << ' ' << a[0][i] << ' ' << a[1][i] << ' ' << a[2][i] << ' ' << a[3][i] << '\n';
            swap(fld[a[0][i]][a[1][i]], fld[a[2][i]][a[3][i]]);
        }
    }
    int ans = 0;
    int seven = 1;
    for (int i = 0; i < h; i++) {
        int nine = 1;
        for (int j = 0; j < w; j++){
            cout << fld[i][j] << " \n"[j + 1 == w];
            ans = add(ans, mul(fld[i][j], mul(seven, nine)));
            nine = mul(nine, 19);
        }
        seven = mul(seven, 17);
    }
    cout << ans << '\n';
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

