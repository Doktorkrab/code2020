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
int arr[MAXN][MAXN];

inline bool check(int a, int b) {
    return a != b && a > 0 && b > 0;
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            if (i == 0 && j == 0)
                continue;
            if (!check(i, j))
                continue;
            unordered_set<int> have;
            for (int k = 1; k < MAXN; k++) {
                if (check(i - k, j))
                    have.insert(arr[i - k][j]);
                if (check(i, j - k))
                    have.insert(arr[i][j - k]);
                if (check(i - k, j - k))
                    have.insert(arr[i - k][j - k]);
            }
            arr[i][j] = 0;
            while (have.count(arr[i][j]))
                arr[i][j]++;
        }
    }
    int ans = 0;
    bool was_good = false;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        assert(a < MAXN && b < MAXN);
        if (a == 0 || b == 0 || a == b)
            was_good = true;
        else
            ans ^= arr[a][b];
    }
    cout << "NY"[ans != 0 || was_good] << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("g_1.in", "r", stdin);
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
