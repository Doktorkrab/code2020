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
const int MAXN = 22;
vector<int> arr;
vector<int> res;
int solve() {
    if (!(cin >> n))
        return 1;
    arr.resize(n);
    res.resize(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    res = arr;
    for (int mask = 0; mask < (1 << (n - 1)); mask++){
        vector<int> cur = arr;
        for (int i = 0; i + 1 < n; i++){
            if (!((mask >> i) & 1))
                continue;
            int num = (i + 2);
            int a = num - 1;
            int b = num / 2 - 1;
            swap(cur[a], cur[b]);
        }
        res = min(res, cur);
    }
    for (int i : res)
        cout << i << ' ';
    cout << '\n';
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
