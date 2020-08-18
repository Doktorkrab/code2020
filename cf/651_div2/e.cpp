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
string s, t;
 
int solve() {
    if (!(cin >> n >> s >> t))
        return 1;
    if (count(ALL(s), '0') != count(ALL(t), '0')){
        cout << "-1\n";
        return 0;
    }
    vector<int> have;
    for (int i = 0; i < n; i++)
        if (s[i] != t[i])
            have.push_back(s[i] - '0');
    int cnt0 = 0, cnt1 = 0;
    for (int i = 0; i < SZ(have); i++){
        if (have[i] == 0){
            if (cnt1)
                cnt1--;
            cnt0++;
        }
        else {
            if (cnt0)
                cnt0--;
            cnt1++;
        }
    }
    cout << cnt0 + cnt1 << '\n';
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