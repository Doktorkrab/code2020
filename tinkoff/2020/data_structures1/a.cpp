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
const int MAXN = 150;
int tree[MAXN][MAXN][MAXN];

void upd(int x, int y, int z, int w) {
    for (int i = x; i < MAXN; i = (i | (i + 1)))
        for (int j = y; j < MAXN; j = (j | (j + 1)))
            for (int k = z; k < MAXN; k = (k | (k + 1)))
                tree[i][j][k] += w;
}

int get(int x, int y, int z) {
    int ans = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
        for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
            for (int k = z; k >= 0; k = (k & (k + 1)) - 1)
                ans += tree[i][j][k];
    return ans;
}

int get(int x, int y, int z, int x1, int y1, int z1) {
//    cout << get(x1, y1, z1) << "!\n";
//    cout << get(x, y, z) << "!\n";
    return get(x1, y1, z1) - get(x, y1, z1) - get(x1, y, z1) - get(x1, y1, z) + get(x, y, z1) + get(x, y1, z) +
           get(x1, y, z) - get(x, y, z);
}

int solve() {
    if (!(cin >> n))
        return 1;
    int m;
    cin >> m;
    while (m != 3) {
        if (m == 1) {
            int x, y, z, w;
            cin >> x >> y >> z >> w;
            upd(x + 1, y + 1, z + 1, w);
        }
        if (m == 2) {
            int x, y, z, x1, y1, z1;
            cin >> x >> y >> z >> x1 >> y1 >> z1;
            x1++, y1++, z1++;
            cout << get(x, y, z, x1, y1, z1) << '\n';
        }
        cin >> m;
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
