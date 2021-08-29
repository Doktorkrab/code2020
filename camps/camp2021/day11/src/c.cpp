#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
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

int n, k;
const int MAXN = 6e4 + 7;
int l[MAXN], r[MAXN], s[MAXN];
bool was[MAXN];
vector<int> g[MAXN];
bool ok[MAXN];
bool used[MAXN];
int dfs(int v, int p, int parity){
    if (used[v])
        return 0;
    used[v] = true;
    int now = 0;
    for (auto e: g[v]){
        if (e == p)
            continue;
        now = parity * s[e] + dfs((v ^ l[e] ^ (r[e])), e, -parity);
        if (p == -1)
            break;
    }
    return now;
}

bool good = true;

int check_placed(int v){
    int cnt = 0;
    for (int e : g[v]){
        int nxt = (v ^ l[e] ^ (r[e]));
        if (!used[nxt])
            cnt++;
    }
    if (cnt == 0){
        good = false;
        return 0;
    }
    if (cnt == 1){
        used[v] = true;
        for (int e : g[v]){
            int nxt = (v ^ l[e] ^ (r[e]));
            if (!used[e])
                return (v < n / 2 ? 1 : -1) * s[e] + check_placed(nxt);
        }
    }
    return 0;
}

bitset<20 * MAXN> sums;
int solve() {
    if (!(cin >> n >> k))
        return 1;
    n *= 2;
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i] >> s[i];
        l[i]--, r[i]--;
        r[i] += n / 2;
        g[l[i]].push_back(i);
        g[r[i]].push_back(i);
    }
    for (int i = 0; i < n; i++){
        if (SZ(g[i]))
    }
    vector<int> weights;
    for (int i = 0; i < n; i++)
        if (!used[i]) {
            weights.push_back(abs(dfs(i, -1, 1)));
//            cout << '\t' << weights.back() << '\n';
        }
    int offs = 10 * n;
    sums[offs] = true;
    for (int x : weights) {
        sums = (sums << x) | (sums >> x);
//        cout << x << '\n';
    }

    for (int i = 0; i <= k; i++){
        if (sums[offs - i] || sums[offs + i]){
            cout << "YES\n";
            return 0;
        }
    }
    cout << "NO\n";
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
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