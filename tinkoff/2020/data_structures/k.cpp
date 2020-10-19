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
const int MAXN = 2e5 + 7;
const int MAXLOG = 25;
int arr[MAXN];
int tree[MAXN];

inline void add(int i, int what) {
    for (int x = i; x < MAXN; x |= x + 1)
        tree[x] += what;
}

inline int get(int r) {
    int res = 0;
    for (int i = r; i >= 0; i = (i & (i + 1)) - 1)
        res += tree[i];
    return res;
}

inline int get(int l, int r) { return get(r) - get(l - 1); }

inline void solve() {
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        add(i, arr[i] == 0);
    }

    cin >> m;
    for (int i = 0; i < m; i++) {
        char type;
        cin >> type;

        if (type == 'u') {
            int pos, next;
            cin >> pos >> next;
            --pos;
            if (arr[pos] == 0)
                add(pos, -1);
            if (next == 0)
                add(pos, 1);
            arr[pos] = next;
        }
        if (type == 's') {
            int l, r, k;
            cin >> l >> r >> k;
            k += get(--l - 1);

            int ans = 0;
            for (int i = MAXLOG - 1; i >= 0; i--) {
                int now = ans + (1 << i) - 1;
                if (now >= n)
                    continue;
                // cerr << now << ' ' << ans << ' ' << tree[now] << ' ' << k <<
                // ' ' << i << '\n';
                if (tree[now] < k) {
                    k -= tree[now];
                    ans += (1 << i);
                }
            }
            // cerr << get(l, ans)
            if (ans >= r)
                cout << "-1\n";
            else
                cout << ans + 1 << '\n';
            // cerr << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    while (cin >> n)
        solve();
}
