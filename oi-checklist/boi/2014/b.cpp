#include <bits/stdc++.h>
#include <ostream>
 
using namespace std;
using ll = long long;
using ull = unsigned long long;


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
string s;
const int MAXN = 2e6 + 7;
const ull BASE = 239;
const ull MOD = 1e9 + 7;
ull hashes[MAXN];
ull bases[MAXN];

ull get(int l, int r){
    return (hashes[r] + MOD - (hashes[l] * bases[r - l]) % MOD) % MOD;
}
int solve() {
    if (!(cin >> n >> s))
        return 1;
    if (n % 2 == 0 || n == 1){
        cout << "NOT POSSIBLE\n";
        return 0;
    }
    int len = n / 2;
    bases[0] = 1; 
    for (int i = 0; i < n; i++){
        hashes[i + 1] = ((hashes[i] * BASE) % MOD + s[i]) % MOD;
        bases[i + 1] = (bases[i] * BASE) % MOD;
    }
    set<ull> ans;
    int l, r;
    // cout << get(4, 7) << '\n';
    for (int i = 0; i < n; i++){
        if (i < len){
            ull frst = ((get(0, i) * bases[len - i]) % MOD + get(i + 1, len + 1)) % MOD;
            ull sec = get(len + 1, n);
            // cout << i << ' ' << frst << ' ' << sec << '\n';
            if (frst == sec){
                l = len + 1;
                ans.insert(frst);
            }
        }
        else {
            ull frst = get(0, len);
            ull sec = ((get(len, i) * bases[n - i - 1]) % MOD + get(i + 1, n)) % MOD;
            // cout << i << ' ' << frst << ' ' << sec << '\n';
            if (frst == sec){
                l = 0;
                ans.insert(frst);
            }
        }
    }
    if (SZ(ans) < 1)
        cout << "NOT POSSIBLE\n";
    else if (SZ(ans) == 1)
        cout << s.substr(l, len) << '\n';
    else
        cout << "NOT UNIQUE\n";
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