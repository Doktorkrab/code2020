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
const int MAXC = 1e7 + 1;
int d[MAXC];
vector<int> primes;
 
int solve() {
    if (!(cin >> k >> n))
        return 1;
    for (int i = 2; i < MAXC; i++){
        if (d[i] == 0){
            primes.push_back(i);
            d[i] = i;
        }
        for (int j = 0; j < SZ(primes) &&  primes[j] <= d[i] && i * primes[j] < MAXC; j++)
            d[i * primes[j]] = primes[j];
    }
    //cout << SZ(primes) << '\n';
    if (k > SZ(primes) ||k > n * n){
        cout << "-1\n";
        return 0;
    }
    //assert(k >= n);
    if (k > n){
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++){
                int left = n * n - i * n - j;
                if (left > k - n)
                    cout << primes[(i * n + j + i) % n] << " \n"[j + 1 == n];
                else
                    cout << primes[n * n - i * n - j - 1 + n] << " \n"[j + 1 == n];
            }
        return 0;
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
            cout << primes[(i + j) % k] << " \n"[j + 1 == n];
    }
    return 0;
}
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("parade.in", "r", stdin);
    freopen("parade.out", "w", stdout);
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
