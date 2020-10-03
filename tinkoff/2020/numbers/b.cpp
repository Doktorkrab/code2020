#include <bits/stdc++.h>
#include <ostream>
 
using namespace std;
using ll = long long;
//#define int ll

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
#define int unsigned long long 
int n;
const int MAXC = 1e6 + 7;
int cnt[MAXC];
int cnt1[MAXC];
int ans[MAXC];

const int MOD = 1e9 + 7;

int bin_p(int a, int b){
    int r = 1;
    //cerr << a << ' ' << b << '\n';
    while (b > 0){
        if (b & 1)
            r = (1ULL * r * a) % MOD;
        a = (1ULL * a * a) % MOD;
        b /= 2;
    }
    return r;
}

inline int mul(int a, int b){
    return (1ULL * a * b) % MOD;
}

inline int add(int a, int b){
    return (a + MOD + b) % MOD;
}

int solve() {
    if (!(cin >> n))
        return 1;
    fill(cnt, cnt + MAXC, 0);
    fill(cnt1, cnt1 + MAXC, 0);
    fill(ans, ans + MAXC, 0);
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        cnt[x]++;
    }

    for (int i = 1; i < MAXC; i++)
        for (int j = 1; 1ULL * i * j < MAXC; j++)
            cnt1[i] += cnt[i * j];
    int aa = 0;
    for (int i = MAXC - 1; i > 1; i--){
        ans[i] = mul(cnt1[i], bin_p(2, cnt1[i] - 1));
        for (int j = 2; 1ULL * i * j < MAXC; j++)
            ans[i] = add(ans[i], -ans[i * j]);
        //cout << i << ' ' << i * ans[i] << ' ' << cnt1[i] << '\n';
        aa = add(aa, mul(i, ans[i]));
    } 
    cout << aa << '\n';
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
