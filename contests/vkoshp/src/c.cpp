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

const int N = 2e5;

int n;
int a[N], b[N];
 
int solve() {
    if (!(cin >> n))
        return 1;
    long long sa = 0, sb = 0;
    for (int i = 0; i < n; ++i){
        cin >> a[i];
        sa += a[i];
    }
    for (int i = 0; i < n; ++i){
        cin >> b[i];
        sb += b[i];
    }
    vector<int> bad;
    for (int i = 0; i < n; ++i){
        if (b[i] > sa - a[i]){
            bad.push_back(i);
        }
    }
    if (bad.size() >= 2){
        cout << "NO\n";
    } else{
        int i = (bad.empty() ? max_element(b, b + n) - b : bad[0]);
        cout << (sa >= sb - b[i] ? "YES\n" : "NO\n");
    }
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
#endif
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
