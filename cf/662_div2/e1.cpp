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
const int MAXN = 1e3 + 7;
const int MAXL = 2e4 + 1e3 + 7;
const ull BASE = 239;
const ull MOD = 1e9  + 7;
string have[MAXN];
vector<ull> hashes[MAXN];
ull bases[MAXL];
vector<pair<int, int>> order;
vector<ll> dp[MAXN];
vector<int> pos[MAXN];

inline ull get_hash(vector<ull>& hashes, int without, int len){
    if (len <= without)
        return hashes[len];
    ull lft = hashes[without];
    ull rgt = (hashes[len + 1] + MOD - (hashes[without + 1] * bases[len - without]) % MOD) % MOD;
    return ((lft * bases[len - without]) % MOD + rgt) % MOD;
}

inline char get_let(string& s, int index, int without){
    // cerr << SZ(s) << ' ' << index << ' ' << without << "?\n";
    if (index < without)
        return s[index];
    // cerr << SZ(s) << ' ' << index + 1 << ' ' << without << "!\n";
    // cerr << (index + 1 == SZ(s)) << '\n';
    if (index + 1 == SZ(s))
        return 0;
    // cerr << "here\n";
    return s[index + 1];
}
void add(ll& a, ll b){
    a = ( a + b) % MOD;
}
bool cmp(const pair<int, int>& a, const pair<int, int>& b){
    auto [index1, without1] = a;
    auto [index2, without2] = b;
    int len1 = SZ(have[index1]);
    if (len1 != without1)
        len1--;
    int len2 = SZ(have[index2]);
    if (len2 != without2)
        len2--;
    int l = 0, r = min(len1, len2) + 1;
    while (r - l > 1){
        int m = (l + r) / 2;
        // cerr << m << " " << len1 << ' ' << len2 << '\n';
        if (get_hash(hashes[index1], without1, m) == get_hash(hashes[index2], without2, m))
            l = m;
        else
            r = m;
    }
    if (l == min(len1, len2)){
        if (len1 == len2)
            return a < b;
        return len1 < len2;
    }
    return get_let(have[index1], l, without1) < get_let(have[index2], l, without2);
}
 
int solve() {
    if (!(cin >> n))
        return 1;
    int s = 0;
    for (int i = 0; i < n; i++){
        cin >> have[i];
        s += SZ(have[i]);
        hashes[i].resize(SZ(have[i]) + 1);
        dp[i].resize(SZ(have[i]) + 1);
        pos[i].resize(SZ(have[i]) + 1);
        auto& now = hashes[i];
        now[0] = 0;
        bases[0] = 1;
        for (int j = 0; j < SZ(have[i]); j++){
            now[j + 1] = ((now[j] * BASE) % MOD + have[i][j]) % MOD;
            bases[j + 1] = (bases[j] * BASE) % MOD;
        }
        // cerr << "ok\n";
    }
    order.resize(s + n);
    int pnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= SZ(have[i]); j++)
            order[pnt++] = {i, j};
    // cerr << "here\n";
    sort(ALL(order), cmp);
    // cerr << "OK\n";
    // for (auto [i, j] : order){
    //     if (j == SZ(have[i]))
    //         cout << have[i] << '\n';
    //     else
    //         cout << have[i].substr(0, j) + have[i].substr(j + 1) << '\n';
    // }
    for (int i = 0; i < SZ(order); i++)
        pos[order[i].first][order[i].second] = i;
    vector<ll> carry(SZ(order));
    for (int i = 0; i < n; i++){
        ll now = 0;
        for (int j = 0; j < SZ(order); j++){
            add(now, carry[j]);
            carry[j] = 0;
            if (order[j].first == i)
                dp[i][order[j].second] = (now + (i == 0)) % MOD;
        }
        for (int j = 0; j <= SZ(have[i]); j++)
            add(carry[pos[i][j]], dp[i][j]);
    }
    ll ans = 0;
    for (int i : dp[n - 1])
        add(ans, i);
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