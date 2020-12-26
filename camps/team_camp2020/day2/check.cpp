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
const int MAXN = 1e5 + 7;
ll arr[MAXN];
bool used[MAXN];
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    string ans;
    cin >> ans;
    int x;
    cin >> x;
    assert(x != 0);
    ll sm = 0;
    for (int i = 0; i < x; i++){
        int y;
        cin >> y;
        assert(!used[y]);
        sm += abs(arr[y - 1] - arr[y % n]);
        used[y] = true;
    }
    cin >> x;
    assert(x != 0);
    for (int i = 0; i < x; i++){
        int y;
        cin >> y;
        assert(!used[y]);
        sm -= abs(arr[y - 1] - arr[y % n]);
        used[y] = true;
    }
    assert(sm == 0);
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
//#ifdef LOCAL
//        cout << "------------------------------\n";
//#endif
    }
}
