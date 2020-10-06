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

int k;
string x;
 
int solve() {
    if (!(cin >> k >> x))
        return 1;
    int cnt = 0;
    while (SZ(x) > 1 && x.back() != '0' && cnt < k) {
        x.pop_back();
        cnt++;
    }
    if (SZ(x) == 1 && x.back() == '0') {
        cout << (cnt == k ? 0 : -1) << '\n';
        return 0;
    }
    if (cnt == k && x.back() != '0') {
        cout << "-1\n";
        return 0;
    }
    x.pop_back();
    while (SZ(x) > 2 && x.back() != '0' && cnt < k) {
        x.pop_back();
        cnt++;
    }
    x.push_back('0');
    if (SZ(x) == 2){
        cout << (cnt + 1 == k ? "0\n" : "-1\n");
        return 0;
    }
    if (cnt == k && x[SZ(x) - 2] != '0'){
        cout << "-1\n";
        return 0;
    }
    if (k - cnt == SZ(x) - 1){
        cout << "0\n";
        return 0;
    }
//    cout << x << '\n';
    if (1 + k - cnt > SZ(x) - 2){
        cout << "-1\n";
        return 0;
    }
    cout << x[0];
    for (int i = 1 + k - cnt; i < SZ(x); i++)
        cout << x[i];
    cout << '\n';

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