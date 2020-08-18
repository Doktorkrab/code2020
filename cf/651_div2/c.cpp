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
    if (n == 1){
        cout << "FastestFinger\n";
        return 0;
    }
    if (n == 2){
        cout << "Ashishgup\n";
        return 0;
    }

    int x = n;
    while (x % 2 == 0)
        x /= 2;
    if (x == 1){
        cout << "FastestFinger\n";
        return 0;
    }
    if (n % 2 == 1){
        cout << "Ashishgup\n";
        return 0;
    }
    n /= 2;
    for (int f = 2; 1LL * f * f <= n; f++){
        if (n % f == 0){
            cout << "Ashishgup\n";
            return 0;
        }
    }
    cout << "FastestFinger\n";
    return 0;
}
 
signed main() {
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