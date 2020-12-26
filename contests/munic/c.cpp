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
bool divs[3];
int mn[3] = {1901, 1601, 0};
int mx[3] = {TMAX(int), 1900, 1600};
string have;
int solve() {
    if (!(cin >> n >> have))
        return 1;
    for (char c : have)
        divs[c - '1'] = 1;
    int base = -1;
    for (int i = 0; i < 3; i++){
        if (divs[i] && mn[i] <= n && n <= mx[i])
            base = i;
    }
    if (base != -1){
        cout << base + 1 << '\n';
        return 0;
    }
    for (int i = 0; i < 3; i++){
        if (!divs[i])
            continue;
        cout << i + 1;
        if (mx[i] < n)
            cout << '*';
        cout << '\n';
    }
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
