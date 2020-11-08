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
const int MAXN = 20;
int a[MAXN];
int b[MAXN];
 
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cin >> m;
    for (int i = 0; i < m; i++)
        cin >> b[i];
    int max_len = 0;
    set<vector<int>> have1;
    for (int mask = 0; mask < (1LL << m); mask++){
        vector<int> have;
        bool good = 1;
        int pnt = 0;
        for (int i = 0; i < m; i++){
            if (!((mask >> i) & 1))
                continue;
            while (pnt < n && a[pnt] != b[i])
                pnt++;
            if (pnt == n){
                good = false;
                break;
            }
            have.push_back(a[pnt++]);
        }
        for (int i = 1; i < SZ(have); i += 2)
            good &= (have[i] > have[i - 1] && have[i] > have[i + 1]);
        if (good && SZ(have)){
            if (max_len == SZ(have))
                have1.insert(have);
            if (max_len < SZ(have)){
                max_len = SZ(have);
                have1.clear();
                have1.insert(have);
            }
        }
    }
    cout << max_len << ' ' << SZ(have1) << '\n';
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
