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
 
int n, m, q;

const int MAXN = 1e5 + 7;
int arr[MAXN];
pair<int, int> queries[MAXN];
int prefix[MAXN];
int ans[MAXN];

int mod(int a, int b){
    if (a < 0){
        int tmp = (abs(a) + b - 1) / b * b;
        a = tmp + a;
    }
    return a % b;
}
 
int solve() {
    if (!(cin >> n >> m >> q))
        return 1;
    for (int i = 0; i < q; i++){
        cin >> queries[i].first >> queries[i].second;
        queries[i].second *= -1;
    }
    reverse(queries, queries + q);
    
    int have = 0;
    for (int i = 0; i < q; i++){
        if (queries[i].first == 1){
            have += queries[i].second;
            have = mod(have, m);
            continue;
        }
        int zero_pos = mod(m - have, m);
        int start = (queries[i].second - mod(queries[i].second, m)) / m;
        int nxt = (zero_pos + m - mod(queries[i].second, m)) % m;
        prefix[0] += start;
        if (mod(queries[i].second, m) != 0){
            prefix[nxt]++;
            prefix[zero_pos]--;
            if (nxt >= zero_pos){
                prefix[0]++;
            }
        }
        have += queries[i].second;
        have = mod(have, m);
    }
    for (int i = 1; i < m; i++)
        prefix[i] += prefix[i - 1];
    for (int i = 0; i < m; i++){
        prefix[i] = mod(prefix[i], n / m);
    }
    for(int i = 0; i < n; i++){
        int x, b = mod(prefix[i % m] + i / m, n / m);
        cin >> x;
        ans[b * m + mod(have + i % m, m)] = x;
    }
    for (int i = 0; i < n; i++)
        cout << ans[i] << " \n"[i + 1 == n];
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
