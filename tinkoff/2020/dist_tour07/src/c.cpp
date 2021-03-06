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

const int MAXN = (1 << 20) + 7;
const int MOD = 1e9 + 7;
const int REV = 500000004;
int n;
vector<int> g[MAXN];
pair<int, int> events[MAXN];
int sums[MAXN];
int sums2[MAXN];

int add(int a, int b){
    return (1LL * a + b + MOD) % MOD;
}
int mul(int a, int b){
    return (1LL * a * b) % MOD;
}

int bin_p(int a, int b){
    int res = 1;
    while (b > 0){
        if (b & 1)
            res = mul(res, a);
        a = mul(a, a);
        b >>= 1;
    }
    return res;
}

int dfs(int v){
    int ans = v;
    for (int u : g[v])
        ans = add(ans, dfs(u));
    return ans;
}
void dfs1(int v){
    if (!SZ(g[v])){
        g[v].push_back(2 * v);
        g[v].push_back(2 * v + 1);
        return;
    }
    for (int u : g[v])
        dfs1(u);
}
void solve20(){
    for (int i = 0; i < n; i++){
        int v = events[i].second;
        if (events[i].first){
            dfs1(v);
        }
        else {
            cout << dfs(v) << '\n';
        }
    }
}
void solve_grow(){
    int cnt = 1;
    for (int i = 1; i < MAXN; i++){
        int t = bin_p(2, i - 1);
        sums[i] = add(sums[i - 1], mul(t, t));
        sums2[i] = add(sums2[i - 1], mul(REV, mul(t, t - 1)));
    }
    for (int i = 0; i < n; i++){
        int v = events[i].second;
        if (events[i].first){
            cnt++;
            continue;
        }
        int d = 31 - __builtin_clz(v);
        int m = cnt - d;
//        cout << m << '\n';
//        cout << sums[m] << '\n';
        cout << add(mul(v, sums[m]), sums2[m]) << '\n';
    }
}

void solve_sum(){

}

int solve() {
    if (!(cin >> n))
        return 1;
    bool grow = true;
    for (int i = 0; i < n; i++){
        string type;
        cin >> type;
        cin >> events[i].second;
        events[i].first = (type[0] == 'G');
        if (events[i].first)
            grow &= (events[i].second == 1);
    }
    if (grow)
        solve_grow();
    else
        solve20();
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
