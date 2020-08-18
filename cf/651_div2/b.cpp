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
const int MAXN = 1e3 + 7;
 
int solve() {
    if (!(cin >> n))
        return 1;
    vector<int> pos[2];
    n *= 2;
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        pos[x % 2].push_back(i);
    }
    if (pos[1].size() % 2 == 1){
        pos[1].pop_back();
        pos[0].pop_back();
    }
    else if (pos[1].size()){
        pos[1].pop_back();
        pos[1].pop_back();
    }
    else {
        pos[0].pop_back();
        pos[0].pop_back();
    }
    for (int gg = 0; gg < 2; gg++)
        for (int i = 0; i < SZ(pos[gg]); i += 2)
            cout << pos[gg][i] + 1 << ' ' << pos[gg][i + 1] + 1 << '\n';
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