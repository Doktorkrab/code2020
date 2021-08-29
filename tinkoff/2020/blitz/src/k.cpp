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
vector<int> have;
 
int solve() {
    if (!(cin >> n))
        return 1;
    have.clear();
    vector<int> ans;
    int now = 1;
    for (int i = 0; i < n; i++){
        while (SZ(have) && have.back() == now){
            ans.push_back(2);
            have.pop_back();
            now++;
        }
        int x;
        cin >> x;
        have.push_back(x);
        ans.push_back(1);
    }
    while (SZ(have) && have.back() == now){
        ans.push_back(2);
        have.pop_back();
        now++;
    }
    if (now != n + 1){
        cout << "0\n";
        return 0;
    }
//    cout << SZ(ans) << '\n';
    for (int x : ans)
        cout << x << " 1\n";
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("k.in", "r", stdin);
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
