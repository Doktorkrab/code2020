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

 
int solve() {
    if (!(cin >> n))
        return 1;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    int ans = 0;
    for (int mask = 1; mask < (1 << n); mask++){
        unordered_map<int, int> have;
        vector<int> a;
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1)
                a.push_back(arr[i]);
        for (int x : a){
            int old = x;
            for(int f = 2; f * f <= old; f++){
                while (x % f == 0){
                    have[f] ^= 1;
                    x /= f;
                }
            }
            if (x > 1)
                have[x] ^= 1;
        }
        bool good = true;
        for (auto [a, b] : have)
            good &= !b;
        if (good) {
            ans++;
//            cout << bitset<5>(mask) << '\n';
        }
    }
    cout << ans << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("f.in", "r", stdin);
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
