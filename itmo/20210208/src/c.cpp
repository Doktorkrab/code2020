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
    if (count(ALL(s), '8')){
        cout << "YES\n";
        cout << "8\n";
        return 0;
    }
    vector<string> to_check;
    for (int i = 0; i < 1000; i++){
        if (i % 8 == 0)
            to_check.push_back(to_string(i));
    }
    for (string& now : to_check){
        int pnt = 0;
        for (char c : s){
            if (c == now[pnt]){
                pnt++;
                if (pnt == SZ(now))
                    break;
            }
        }
        if (pnt == SZ(now)){
            cout << "YES\n";
            cout << now << '\n';
            return 0;
        }
    }
    cout << "NO\n";
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
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
