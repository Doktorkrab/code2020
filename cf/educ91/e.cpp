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
 
int m, n;
const int MAXN = 2e5 + 7;
int p[MAXN];
int who[MAXN];
vector<int> have[MAXN];


int get(int v){
    if (p[v] == v)
        return v;
    return (p[v] = get(p[v]));
}
 
int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < m; i++)
        p[i] = i;
    int ans = n - 1;
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        --x;
        who[i] = x;
        have[x].push_back(i);
    }
    for (int i = 1; i < n; i++)
        ans -= (who[i] == who[i - 1]);
    cout << ans << '\n';
    for (int i = 1; i < m; i++){
        int a, b;
        cin >> a >> b;
        --a, --b;
        a = get(a), b = get(b);
        if (SZ(have[a]) > SZ(have[b]))
            swap(a, b);
        for (int x : have[a]){
            // cout << x + 1 << " " << a + 1 << "->" << b + 1 << '\n';
            if (x > 0)
                ans -= (who[x - 1] == b);
            if (x + 1 < n)
                ans -= (b == who[x + 1]);
        }
        for (int x : have[a]){
            who[x] = b;
            have[b].push_back(x);
        }
        p[a] = b;
        cout << ans << '\n';
    }
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