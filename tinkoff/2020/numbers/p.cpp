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
const int MAXN = 1e8 + 7;
const int BLOCK = 1e4;
int blocks[BLOCK + 1];
int val[BLOCK + 1];
int ans[BLOCK + 1];
int solve() {
    if (!(cin >> n))
        return 1;
    int sz = sqrtl(n + 0.5);
    blocks[0] = n - 1;
    val[0] = n - 1;
    int pnt = 1, cnt = 1;
    int facc = n - 1;
    for (int i = n - 2; i >= 1; i--){
        facc = (1LL * facc * (i + 1)) % n;
        cnt++;
        if (cnt == sz){
            blocks[pnt] = facc;
            val[pnt++] = i;
            cnt = 0;
        }
    }
    blocks[pnt] = 0;
    val[pnt++] = 0;
    reverse(blocks, blocks + pnt);
    reverse(val, val + pnt);
    int sum = 0;
    int fac = 1;
    cnt = 0;
    for (int i = 1; i < pnt; i++){
        int nn = val[i];
        int stop = val[i - 1];
        int len = nn - stop;
        ans[len - 1] = blocks[i];
        for (int j = nn - 1; j > stop; j--){
            int ind = len - (nn - j) - 1;
            ans[ind] = 1LL * ans[ind + 1] * (j + 1) % n;
        }
        int now = stop + 1;
        for (int j = 0; j < len; j++){
            ans[j] = (1LL * fac * ans[j]) % n;
            fac = (1LL * fac * now++) % n;
        }
        for (int j = 0; j < len; j++){
            sum += ans[j];
            sum %= n;
            cnt++;
            if (cnt == 100){
                cout << sum << ' ';
                cnt = sum = 0;
            }
        }
    }
    if (cnt != 0)
        cout << sum << '\n';
    else
        cout << '\n';
    

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
 
