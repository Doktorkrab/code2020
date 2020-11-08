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
const int MAXN = 1e8 + 7;
int euler[MAXN];
vector<int> primes;

int solve() {
    if (!(cin >> n))
        return 1;
    fill(euler, euler + n + 1, -1);
    ll sum = 1;
    ll cnt1 = 1;
    for (int i = 2; i <= n; i++) {
        if (euler[i] == -1) {
            primes.push_back(i);
            euler[i] = i - 1;
        }
        sum += euler[i];
        cnt1++;
        if (cnt1 == 100) {
            cout << sum << ' ';
            sum = cnt1 = 0;
        }
        for (int j = 0; j < SZ(primes) && i * primes[j] <= n; j++) {
            if (i % primes[j] == 0) {
                int t = i;
                int a = 0;
                while (t % primes[j] == 0) {
                    a++;
                    t /= primes[j];
                }
                int b = 1;
                for (int k = 0; k < a; k++)
                    b *= primes[j];
                euler[i * primes[j]] = euler[i] / (b - b / primes[j]) * (b * primes[j] - b);
                break;
            } else {
                euler[i * primes[j]] = euler[i] * (primes[j] - 1);
            }
        }
    }
    if (cnt1 > 0)
        cout << sum << '\n';
    else
        cout << '\n';
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
