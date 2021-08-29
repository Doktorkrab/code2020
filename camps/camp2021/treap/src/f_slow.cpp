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
const int MAXN = 2e6;
int arr[MAXN];

void insert(int a, int b){
    if (arr[a] != 0)
        insert(a + 1, arr[a]);
    arr[a] = b;
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        insert(x - 1, i + 1);
    }
    int mx = 0;
    for (int i = 0; i < 4 * (n + m); i++){
        if (arr[i] != 0)
            mx = i;
    }
    cout << mx + 1 << '\n';
    for (int i = 0; i <= mx; i++)
        cout << arr[i] << " ";
    cout << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("f.in", "r", stdin);
#else
    freopen("key.in", "r", stdin);
    freopen("key.out", "w", stdout);
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
