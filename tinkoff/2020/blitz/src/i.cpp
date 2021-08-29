#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;
#define int ll

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
int arr[MAXN];
int tree1[MAXN], tree2[MAXN];

void add(int pos, int x, int *tree) {
    for (int i = pos; i < MAXN; i |= i + 1)
        tree[i] += x;
}

int get(int r, const int *tree) {
    int ans = 0;
    for (int i = r; i >= 0; i = (i & (i + 1)) - 1)
        ans += tree[i];
    return ans;
}

int get(int l, int r, const int *tree) {
    return get(r, tree) - get(l - 1, tree);
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int now = get(arr[i] + 1, n, tree1);
        ans += get(arr[i] + 1, n, tree2);
        add(arr[i], 1, tree1);
        add(arr[i], now, tree2);
    }
    cout << ans << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("i.in", "r", stdin);
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
