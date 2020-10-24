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
vector<vector<int>> matrix_mul(vector<vector<int>> a, vector<vector<int>> _b){
    vector<vector<int>> b(SZ(_b[0]), vector<int>(SZ(_b)));
    for (int i = 0; i < SZ(_b[0]); i++)
        for (int j = 0; j < SZ(_b); j++)
            b[i][j] = _b[j][i];

    int n = SZ(a);
    int m = SZ(b);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0)
}

 
int solve() {
    if (!(cin >> n))
        return 1;
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
