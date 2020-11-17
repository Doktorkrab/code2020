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
#define int ll

int n;
const int MAXN = 1e6 + 7;
const int MOD = 998244353;
int tree_2[MAXN];
int tree_i[MAXN];
int tree[MAXN];

void add(int *fenwick, int x, int y) {
    for (int i = x; i < MAXN; i |= i + 1) {
        fenwick[i] += y;
        fenwick[i] %= MOD;
    }
}

int get(int *fenwick, int r) {
    int res = 0;
    for (int i = r; i >= 0; i = (i & (i + 1)) - 1) {
        res += fenwick[i];
        res %= MOD;
    }
    return res;
}

int get(int *fenwick, int l, int r) {
    return (get(fenwick, r) - get(fenwick, l - 1) + MOD) % MOD;
}

int arr[MAXN];
const int REV = 499122177;

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    for (int i = 0; i < n; i++) {
        tree[i] = arr[i] + (i ? tree[i] - 1);
        add(tree_i, i, (i * arr[i]) % MOD);
        add(tree_2, i, (i * (i + 1) / 2) % MOD * arr[i] % MOD);
    }
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int l, r;
        cin >> l >> r;
        --l;
        int m = (l + r - 1) / 2;
        --l;
//        cout << get(tree_2, l + 1, m) << ' ' << get(tree_2, m + 1, r - 1) << '\n';
        int l_sum = get(tree_2, l + 1, m) - (get(tree_i, l + 1, m) * (l) % MOD) % MOD +
                    (get(tree, l + 1, m) * (l * l % MOD + MOD - l) % MOD * REV) % MOD;
        int r_sum = get(tree_2, m + 1, r - 1) - (get(tree_i, m + 1, r - 1) * (1 + r)) % MOD +
                    (get(tree, m + 1, r - 1) * (r * r % MOD + r) % MOD * REV % MOD);
//        cout << get(tree_2, l + 1, m) << ' ' << (get(tree_i, l + 1, m) * (2 * l - 1) % MOD * REV) % MOD << ' ' << (get(tree, l + 1, m) * (l * l % MOD + MOD - l) % MOD * REV) % MOD << '\n';
        cout << (l_sum + r_sum) % MOD << '\n';
    }
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
