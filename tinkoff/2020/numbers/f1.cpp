
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
string s;

int solve() {
    if (!(cin >> s))
        return 1;
    n = SZ(s);
    pair<int, int> ans = {-1, 0};
    for (int a = 1; a <= n; a++)
        for (int b = 0; a + b <= n; b++){
            bool good = true;
            for (int i = 0; i < n; i += a + b){
               for (int j = 0; j < a && i + j < n; j++)
                   good &= (s[i + j] != '1'); 
               for (int j = 0; j < b && i + j + a < n; j++)
                   good &= (s[i + j + a] != '0');
            }
            if (good)
                ans = max(ans, make_pair(b, a));
        }
    if (ans.first == -1){
        cout << "-1\n";
        return 0;
    }
    auto [b, a] = ans;
    for (int i = 0; i < n; i += a + b){
        for (int j = 0; j < a && i + j < n; j++)
            cout << "0";
        for (int j = 0; j < b && i + a + j < n; j++)
            cout << "1";
    }
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
