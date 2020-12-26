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
const int MAXP = 6e6 + 7;
const int D = 10;
vector<int> primes;
bool is_prime[MAXP];
int pnt[D];
vector<int> have[D];
void init(){
    fill(is_prime, is_prime + MAXP, 1);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i < MAXP; i++){
        if (!is_prime[i])
            continue;
        primes.push_back(i);
        for (ll j = 1LL * i * i; j <= MAXP; j += i)
            is_prime[j] = false;
    }
}
int solve() {
    if (!(cin >> n >> k))
        return 1;
    for (int i = 0; i < D; i++)
        have[i].clear();
    int pos = 0;
    for (int i = 0; i < n; i++){
        int tmp = 0;
        int x = primes[i];
        while (x > 0)
            tmp = tmp * 10 + (x % 10), x /= 10;
        while (tmp > 0){
            have[tmp % 10].push_back(pos++);
            tmp /= 10;
        }
    }
//    for (int i = 0; i < D; i++) {
//        cout << i << ": ";
//       for (int j : have[i])
//           cout << j << ' ';
//       cout << '\n';
//    }
    string ans;
    fill(pnt, pnt + D, 0);
    int used = 0;
    int now = 0;
    for (int i = 0; i < pos - k; i++){
        bool was = false;
        for (int d = D - 1; d >= 0; d--){
            while (pnt[d] < SZ(have[d]) && have[d][pnt[d]] < now)
                pnt[d]++;
            if (pnt[d] == SZ(have[d]))
                continue;
            if (used + (have[d][pnt[d]] - now) > k)
                continue;
            was = true;
            ans += (char)('0' + d);
            used += have[d][pnt[d]] - now;
            now = have[d][pnt[d]++] + 1;
            break;
        }
        assert(was);
    }
    cout << ans << '\n';
    return 0;
}
 
signed main() {
    freopen("primeseq.in", "r", stdin);
    freopen("primeseq.out", "w", stdout);
    init();
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
