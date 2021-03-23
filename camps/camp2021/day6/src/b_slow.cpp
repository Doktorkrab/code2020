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
 
int n, q;
const int MAXN = 1e5;
vector<int> have[MAXN];
 
int solve() {
    if (!(cin >> n >> q))
        return 1;
    for (int i = 0; i < n; i++)
        have[i].clear();
    for (int i = 0; i < q; i++){
        int type, l, r;
        cin >> type >> l >> r;
        --l;
        if(type == 1){
            int x;
            cin >> x;
            for (int j = l; j < r; j++)
                have[j].push_back(x);
        }
        if (type == 2){
            for (int j = l; j < r; j++)
                sort(ALL(have[j]));
            bool good = true;
            for (int j = l + 1; j < r; j++)
                good &= (have[l] == have[j]);
            cout << good << '\n';
        }
    }
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
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
