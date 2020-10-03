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
const int MAXN = 3e5 + 7;
int prefix0[MAXN], prefix1[MAXN];
int rgt1[MAXN];
int lft0[MAXN];
string s;

int solve() {
    if (!(cin >> s))
        return 1;
    n = SZ(s);
    rgt1[0] = -1;
    for (int i = 0; i < n; i++){
        prefix1[i + 1] = prefix1[i] + (s[i] == '1');
        prefix0[i + 1] = prefix0[i] + (s[i] == '0');
        rgt1[i + 1] = (s[i] == '0' ? i : rgt1[i]);
    }
    lft0[n] = n;
    for (int i = n - 1; i >= 0; i--){
        lft0[i] = (s[i] == '1' ? i : lft0[i + 1]);
        //cout << i << ' ' << lft0[i] << '\n';
    }

    //for (int i = 0; i <= n; i++)
        //cout << rgt1[i] << " \n"[i == n];
    //for (int i = 0; i < n; i++)
        //cout << lft0[i] << " \n"[i + 1 == n];
    pair<int, int> ans = {-1, 0};
    int ans_c = -1;
    auto get = [&](int l, int r, int* pr){ return pr[r] - pr[l]; };
    for (int len = 1; len <= n; len++){
       //cout << l << ' ' << a << '\n';
        int lft = 1, rgt = len;
        for (int i = 0; i < n; i += len){
            int l = i;
            int r = min(i + len - 1, n - 1);
            if (rgt1[r + 1] >= i && rgt1[r + 1] >= 0)
                lft = max(lft, rgt1[r + 1] - i + 1);
            if (lft0[l] - i < l && lft0[l] < n)
                rgt = min(rgt, lft0[l] - i);
            //cout << (rgt1[r + 1] - i + 1) << ' ' << lft0[l] - i << '\n';
            //cout << '\t' << lft << ' ' << rgt << '\n';
        }
        if (lft > rgt)
            continue;
        bool good = true;
        int now = 0;
        for (int i = 0; i < n; i += len){
            int l = i;
            int r1 = min(i + lft, n);
            int r2 = min(i + len, n);
            if (get(l, r1, prefix1) != 0)
                good = false;
            if (get(r1, r2, prefix0) != 0)
                good = false;
            now += r2 - r1;
        }
        if (good && now > ans_c){
            ans = make_pair(len - lft, lft);
            ans_c = now;
        }
        
    }
    if (ans.first == -1){
        cout << "-1\n";
        return 0;
    }
    auto [b, a] = ans;
    for (int i = 0; i < n; i += a + b){
        for (int j = 0; j < a && i + j < n; j++)
            cout << "0";
        for (int j = 0; j < b && i + a + j < n; j++)
            cout << "1";
    }
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
