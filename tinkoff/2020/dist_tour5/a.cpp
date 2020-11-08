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
const int MAXN = 105;
int arr[MAXN];
vector<pair<int, int>> ans;
void solve(vector<int> arr, int n){
    if (n == 1)
        return;
    int m = n / 2;
    vector<int> l(arr.begin(), arr.begin() + m);
    vector<int> r(arr.begin() + m, arr.end());
    solve(l, m);
    solve(r, m);
    for (int i = 0; i < m; i++)
        ans.emplace_back(l[i], r[i]);
}
int solve() {
    if (!(cin >> n))
        return 1;
    if (n == 2){
        cout << "1\n1 2\n";
        return 1;
    }
    if (n == 4){
        cout << "4\n1 2\n3 4\n1 4\n2 3\n";
        return 1;
    }

    if (__builtin_popcount(n) != 1){
        if (n == 6){
            cout << "6\n"
                    "3 4\n"
                    "2 6\n"
                    "5 6\n"
                    "4 5\n"
                    "3 6\n"
                    "1 2\n";
            return 1;
        }
        set<int> have;
        for (int i = 0; i < n; i++){
            int x;
            cin >> x;
            have.insert(x);
        }
        if (SZ(have) == 1) {
            cout << 0 << '\n';
            return 1;
        }
        assert(SZ(have) != n);
        return 1;

    }
    vector<int> have(n);
    iota(ALL(have), 1);
    solve(have, n);
    assert(SZ(ans) <= 5000);
    cout << SZ(ans) << '\n';
    for (const auto& [a, b] : ans)
        cout << a << ' ' << b << '\n';
    return 1;
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
