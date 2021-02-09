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
 
int a, b;
const int MAXN = 5e6 + 10;
int d[MAXN];
int cnt[MAXN];
vector<int> primes;
ll prefix_sum[MAXN + 100];

void precalc(){
    fill(d, d + MAXN, -1);
    for (int i = 2; i < MAXN; i++){
        if (d[i] == -1){
            d[i] = i;
            cnt[i] = 1;
            primes.push_back(i);
        }
        for (int x : primes){
            if (x > d[i] || 1LL * x * i >= MAXN)
                break;
            d[x * i] = x;
            cnt[i * x] = cnt[i] + 1;
        }
    }

    for (int i = 0; i < MAXN; i++)
        prefix_sum[i + 1] = prefix_sum[i] + cnt[i];
}
int solve() {
    if (!(cin >> a >> b))
        return 1;
    ll ans = 0;
    cout << prefix_sum[a + 1] - prefix_sum[b + 1] << '\n';
    return 0;
}
 
signed main() {
    precalc();
#ifdef LOCAL
    freopen("d.in", "r", stdin);
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
