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
 
ll N, K;
//const int MAXN = 1e9 + 7;
//int euler[MAXN];
//int cnt[MAXN];
vector<int> primes;
const int MOD = 1e8 + 7;
ll e(ll x){
    ll stop = ((ll)sqrtl(x + 0.5)) + 3;
    ll result = x;
    for (ll f = 2; f <= stop; f++){
        if (x % f == 0)
            result -= result / f;
        while (x % f == 0)
            x /= f;
    }
    if (x > 1)
        result -= result / x;
    return result % MOD;
}
int solve() {
    if (!(cin >> N >> K))
        return 1;
    int n = (int)(1e9 + 7);
    vector<int> euler(n + 1, -1);
    //ll sum = 1;
    //ll cnt1 = 1;
    for (int i = 2; i <= n; i++){
        if (euler[i] == -1){
            primes.push_back(i);
            euler[i] = i - 1;
            //cnt[i] = i;
        }
        //sum += euler[i];
        //cnt1++;
        //if (cnt1 == 100){
            //cout << sum << ' ';
            //sum = cnt1 = 0;
        //}
        //cout << euler[i] << ' ' << i << '\n';
        for (int j = 0; j < SZ(primes) && i * primes[j] <= n; j++){
            //d[i * primes[j]] = primes[j];
            if (i % primes[j] == 0){
                //cnt[i * primes[j]] = cnt[i] * primes[j];
                //euler[i * primes[j]] = euler[i] / (cnt[i] - cnt[i] / primes[j]) * (cnt[i] * primes[j] - cnt[i]);
                int t = i;
                int a = 0;
                while (t % primes[j] == 0){
                    a++;
                    t /= primes[j];
                }
                int b = 1;
                for (int k = 0; k < a; k++)
                    b *= primes[j];
                euler[i * primes[j]] = euler[i] / (b - b / primes[j]) * (b * primes[j] - b);
                break;
            }
            else {
                //cnt[i * primes[j]] = primes[j];
                euler[i * primes[j]] = euler[i] * (primes[j] - 1);
            }
        }
    }
    //if (cnt1 > 0)
        //cout << sum << '\n';
    //else
        //cout << '\n';
    euler[1] = 1;
    for (int i = 1; i <= n; i++)
        euler[i] %= MOD;
    ll c = (K + 1) / 2;
    N = e(N);
    //cerr << N << '\n';
    for (int i = 1; N != euler[N] && i < c; i++){
        //cerr << N << ' ' << euler[N] << '\n';
        assert(N >= 0);
        N = euler[N];
    }
    cout << N << '\n';
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
