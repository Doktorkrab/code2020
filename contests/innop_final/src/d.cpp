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
 
int n, l;
enum {
    NONE, IN, OUT
};
struct Puzzle{
    int l, left, right;
};

int get(const string& x){
    if (x == "out")
        return OUT;
    if (x == "in")
        return IN;
    return NONE;
}

const int MAXN = 305;
const int MOD = 1e9 + 7;
Puzzle arr[MAXN];
int dp[MAXN];
int solve() {
    if (!(cin >> n >> l))
        return 1;
    for (int i = 0; i < n; i++){
        int x;
        string a, b;
        cin >> x >> a >> b;
        arr[i].l = x;
        arr[i].left = get(a);
        arr[i].right = get(b);
        if (arr[i].right != NONE)
            arr[i].right = 3 - arr[i].right;
    }
    vector<int> none, lft, rgt;
    int ans = 0;
    for (int i = 0; i < n; i++){
        if (arr[i].left == NONE && arr[i].right == NONE)
            ans += (arr[i].l == l);
        else if (arr[i].left == NONE)
            lft.push_back(arr[i].l);
        else if (arr[i].right == NONE)
            rgt.push_back(arr[i].l);
        else
            none.push_back(arr[i].l);
    }
    fill(dp, dp + MAXN, 0);
    dp[0] = 1;
    for (int i = 0; i < SZ(none); i++){
        for (int j = l; j >= none[i]; j--)
            dp[j] = (dp[j] + dp[j - none[i]]) % MOD;
    }
    for (int x : lft){
        for (int y : rgt){
            if (l - x - y >= 0)
                ans = (ans + dp[l - x - y]) % MOD;
        }
    }
    cout << ans << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("d.in", "r", stdin);
#endif
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
