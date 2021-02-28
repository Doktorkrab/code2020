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
const int MAXN = 1e4;
int dp[MAXN];
bool used[MAXN];
 
int solve() {
    if (!(cin >> n))
        return 1;
//    fill(dp, dp + MAXN, (int)1e9);
//    fill(used, used + MAXN, false);
//    deque<int> q = {1};
//    dp[1] = 0;
//    while (!q.empty()){
//        int v = q.front();
//        q.pop_front();
//        if (used[v])
//            continue;
//        used[v] = true;
//        string s = to_string(v);
//        vector<int> perm(SZ(s));
//        iota(ALL(perm), 0);
//        do {
//            string t;
//            for (int x : perm)
//                t += s[x];
//            int tt = stoi(t);
//            if (tt < MAXN && dp[tt] > dp[v] + 1){
//                dp[tt] = dp[v] + 1;
//                q.push_back(tt);
//            }
//        } while (next_permutation(ALL(perm)));
//        if (v + 1 < MAXN && dp[v + 1] > dp[v] + 1){
//            dp[v + 1] = dp[v] + 1;
//            q.push_back(v + 1);
//        }
//    }
    string st = to_string(n);
    int sum = 0;
    for (char c : st)
        sum += c - '0';
    int cnt0 = 0;
    int cnt1 = 0;
    for (int i = 0; i + 1 < SZ(st); i++) {
        cnt0 += (st[i] != '0');
        cnt1 |= (st[i] == '1');
    }
    ll need = (5LL * SZ(st) - 1) * (SZ(st) * 1LL - 1);
//    cout << need << ' ' << sum << " " << cnt0 << " " << cnt1 << " " << sum - (st[0] - '0') << '\n';
    ll ans = need;

    if (sum - (st[0] - '0') > 0)
        ans = need + sum + cnt0 - cnt1 - 1;
    else if (sum != 1){
//        cout << "here\n";
        int t = n - 1;
        st = to_string(t);
        sum = 0;
        for (char c : st)
            sum += c - '0';
        cnt0 = 0;
        cnt1 = 0;
        for (int i = 0; i + 1 < SZ(st); i++) {
            cnt0 += (st[i] != '0');
            cnt1 |= (st[i] == '1');
        }
        ans = need + sum + cnt0 - cnt1;
    }
    else
        ans = need;
//    cout << ans << ' ' << dp[n] << ' ' << n << endl;
//    assert(dp[n] == ans);
    cout << ans << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
#endif
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
