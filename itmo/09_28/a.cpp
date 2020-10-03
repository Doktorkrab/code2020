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
 
int n, k;
const int MAXN = 1e5 + 7;

int arr[MAXN];
 
int solve() {
    if (!(cin >> n >> k))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    unordered_map<int, int> ans;
    for (int i = 0; i < n; i++)
        ans[arr[i]]++;
    vector<int> ans1;
    while (1){
        for (auto& [a, b] : ans){
            if (b != 0){
                ans1.push_back(a);
                b--;
                if (SZ(ans1) == k)
                    break;
            }
        }
        if (SZ(ans1) == k)
            break;
    }
    for (int i : ans1)
        cout << i << ' ';
    cout << '\n';
    return 0;
}
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("colors.in", "r", stdin);
    freopen("colors.out", "w", stdout);
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
