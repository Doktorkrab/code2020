#include <bits/stdc++.h>
#include <ostream>
 
using namespace std;
using ll = long long;

#define int ll
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

const int MAXN = 1e5 + 7;
bool used[MAXN];
bool used1[MAXN];
int euler[MAXN];
int d[MAXN];
int cnt[MAXN];
vector<int> primes;
int solve() {
    if (!(cin >> n))
        return 1;
    n++;

    fill(used, used + MAXN, 0);
    fill(used1, used1 + MAXN, 0);
    fill(euler, euler + MAXN, -1);
    primes.clear();
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        used1[x] = true;
    }
    
    for (int i = 2; i < MAXN; i++){
        for (int j = 1; i * j < MAXN; j++){
            used[i] |= used1[i * j];
            if (used[i])
                break;
        }
    }
    for (int i = 2; i < MAXN; i++){
        if (euler[i] == -1){
            primes.push_back(i);
            euler[i] = i - 1;
            cnt[i] = i;
        }
        //cout << euler[i] << ' ' << i << '\n';
        for (int j = 0; j < SZ(primes) && i * primes[j] <= MAXN; j++){
            //d[i * primes[j]] = primes[j];
            if (i % primes[j] == 0){
                cnt[i * primes[j]] = cnt[i] * primes[j];
                euler[i * primes[j]] = euler[i] / (cnt[i] - cnt[i] / primes[j]) * (cnt[i] * primes[j] - cnt[i]);
                break;
            }
            else {
                cnt[i * primes[j]] = primes[j];
                euler[i * primes[j]] = euler[i] * (primes[j] - 1);
            }
        }
    }
    int ans = 0;
    //for (int i = 2; i < MAXN; i++)
        //if (used[i])
            //cout << euler[i] << ' ';
    //cout << '\n';
    for (int i = 2; i < MAXN; i++)
        ans += euler[i] * used[i];
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
