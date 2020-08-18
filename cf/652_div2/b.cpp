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
const int MAXN = 1e5 + 7;
bool used[MAXN];
int solve() {
    if (!(cin >> n >> s))
        return 1;
    vector<pair<char, int>> have;
    for (char c : s){
        if (SZ(have) == 0 || have.back().first != c)
            have.push_back({c, 0});
        have.back().second++;
    }
    n = SZ(have);
    for (int i = 0; i < n; i++)
        used[i] = false;

    for (int i = 0; i < n; i++){
        if (have[i].first == '0' && i > 1)
            used[i] = 1;
        if (have[i].first == '1' && i + 1 < n && have[i + 1].first == '0')
            used[i] = 1;
    }
    for (int i = 0; i < n; i++){
        if (have[i].first == '0'){
            // if (used[i])
            //     continue;
            if (i == 0)
                for (int j = 0; j < have[i].second; j++)
                    cout << '0';
            else if (i + 1 == n || !used[i + 1])
                cout << '0';
        }
        if (have[i].first == '1'){
            if (used[i])
                continue;
            // if (i > 0)
            //     cout << '0';
            for (int j = 0; j < have[i].second; j++)
                cout << '1';
        }
    }
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