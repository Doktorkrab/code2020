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

string arr[] = {"solve", "this", "problem", "and", "you", "will", "be", "the", "best"};
 
int solve() {
    for (ll i = 0; i <= 362879; i++){
        cout << ' ' << (1LL) * i * i << ' ';
        for (int j = 0; j < 9; j++) {
            cout << arr[j];
            if (j + 1 != 9)
                cout << ' ';
        }
        if ((i + 1) % 20 == 0){
            ll x = ((i + 1) / 20) * ((i + 1) / 20);
            ll y = sqrtl(x);
            if (y * y == x)
                cout << '\n';
        }
        for (auto& j : arr)
            rotate(j.begin(), j.begin() + 1, j.end());
    }
    cout << "\nSolved? Cool!\n";
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("d.in", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1;
//    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
    }
}
