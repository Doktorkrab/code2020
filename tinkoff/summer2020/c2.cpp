#include <bits/stdc++.h>
#include <ostream>
 
using namespace std;
using ll = long long;

#define int ll

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
 
const int MAXN = 5e4 + 7;
const int MOD = 1e9 + 7;
int n;
string ta, tb;
int a[MAXN], b[MAXN], c[MAXN];
int dp_prefix[2][MAXN];
int dp_suffix[2][MAXN];
int ten[MAXN];

int add(int x, int y){
    return (x + MOD + y) % MOD;
}

int mul(int x, int y){
    return (x * y) % MOD;
}

void calc_dp(int prefix[MAXN], int suffix[MAXN], int a[MAXN]){
    for (int i = 0; i < n; i++){
        prefix[i + 1] = add(a[i], mul(10, prefix[i]));
    }
    //suffix[n] = 1;
    for (int i = n - 1; i >= 0; i--){
        suffix[i] = mul(a[i], add(ten[n - i - 1], 0)) + suffix[i + 1];
    }
}
int get_cnt(int pos, int x, int prefix[MAXN], int suffix[MAXN], int num[MAXN]){
    if (x < num[pos])
        return mul(add(prefix[pos], 1), add(ten[n - pos - 1], -0));
    if (x == num[pos])
        return add(mul(prefix[pos], add(ten[n - pos - 1], -0)), suffix[pos + 1]);
    return mul(prefix[pos], add(ten[n - pos - 1], -0));
}
int solve() {
    if (!(cin >> ta >> tb))
        return 1;
    reverse(ALL(ta));
    ten[0] = 1;
    for (int i = 1; i < MAXN; i++)
        ten[i] = mul(ten[i - 1], 10);
    while (SZ(ta) < SZ(tb))
        ta += '0';
    reverse(ALL(ta));
    n = SZ(tb);
    for (int i = 0; i < n; i++){
        a[i + 1] = ta[i] - '0';
        b[i + 1] = tb[i] - '0';
        c[i + 1] = b[i + 1];
    }
    n++;
    c[n - 1]++;
    for (int i = n - 1; i >= 1; i--){
        c[i - 1] += c[i] / 10;
        c[i] %= 10;
    }
    calc_dp(dp_prefix[0], dp_suffix[0], c);
    calc_dp(dp_prefix[1], dp_suffix[1], a);
    //for (int j = 0; j < 2; j++)
        //for (int i = 0; i <= n; i++)
            //cout << dp_prefix[j][i] << " \n"[i == n];
    //for (int j = 0; j < 2; j++)
        //for (int i = 0; i <= n; i++)
            //cout << dp_suffix[j][i] << " \n"[i == n];
    int ans = 0;
    for (int i = 0; i < n; i++){
        for (int x = 0; x < 10; x++){
            int cnt_x = add(-get_cnt(i, x, dp_prefix[1], dp_suffix[1], a), get_cnt(i, x, dp_prefix[0], dp_suffix[0], c));
            //cout << i << ' ' << x << ' ' << get_cnt(i, x, dp_prefix[1], dp_suffix[1], a) << ' ' <<  get_cnt(i, x, dp_prefix[0], dp_suffix[0], c) << '\n';
            for (int y = 0; y < 10; y++){
                int to_ans = abs(x - y);
                int cnt_y = add(-get_cnt(i, y, dp_prefix[1], dp_suffix[1], a), get_cnt(i, y, dp_prefix[0], dp_suffix[0], c));
                ans = add(ans, mul(to_ans, mul(cnt_y, cnt_x)));
            }
        }
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
