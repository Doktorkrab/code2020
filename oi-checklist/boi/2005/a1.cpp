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
int ve, vc, ce, cc;
string vowels = "aeiou";
const int MAXN = 20;
int dp[MAXN][MAXN][MAXN][MAXN][MAXN];
bool kek(char c){
    for (char cc : vowels)
        if (c == cc)
            return true;
    return false;
}

string s;

int solve() {
    if (!(cin >> ve >> vc >> ce >> cc >> s))
        return 1;
    n = SZ(s);

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