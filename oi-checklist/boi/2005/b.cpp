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
 
int n, m;
string s;
 
int solve() {
    if (!(cin >> n >> m))
        return 1;
    string line;
    while (SZ(s) != n){
        cin >> line;
        s += line;
    }

    int bal = 0;
    for (char c : s){
        if (c == '(')
            bal++;
        else
            bal--;
        if (bal < 0){
            cout << "0\n";
            return 0;
        }
    }
    if (bal == 0){
        cout << "1\n";
        for (int i = 0; i < m; i++)
            cout << "1\n";
        return 0;
    }
    if (m == 0){
        cout << "0\n";
    }
    vector<int> ans(m, 1), pos(m);
    int pnt = 0;
    for (int i = 0; i < n; i++)
        if (s[i] == ']')
            pos[pnt++] = i;
    vector<int> stack;
    for (int i = 0; i < n; i++){
        if (s[i] == '(')
            stack.push_back(i);
        else
            stack.pop_back();
    }
    for (int x : stack){
        int have = lower_bound(ALL(pos), x) - pos.begin();
        if (have == m){
            cout << "0\n";
            return 0;
        }
        ans[have]++;
    }
    cout << "1\n";
    for (int x : ans)
        cout << x << '\n';
    return 0;
}
 
signed main() {
// #ifndef LOCAL
//     freopen("LISP.IN", "r", stdin);
//     freopen("LISP.OUT", "w", stdout);
// #endif
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