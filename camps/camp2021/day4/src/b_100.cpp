#pragma GCC optimize("O3,unroll-loops")

#include <iostream>
#include <vector>
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
const int MAXN = 150;
const int MAXQ = 1e5;
const int MOD = 1e9 + 33;
int arr[MAXN][MAXN];
vector<int> dist[MAXN][MAXN]; // dist to interesting points
vector<unsigned short> enters[MAXQ], blocked[MAXQ];
int stops[MAXQ];
int dp[MAXN][MAXN];

inline int add(int a, int b) {
    int t = (a + b);
    if (t >= MOD)
        t -= MOD;
    return t;
}

inline bool check(int x, int y) {
    return x < n && y < m && arr[x][y] == '.';
}

void precalc(int xs, int ys) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            dp[i][j] = 0;
    dp[xs][ys] = 1;
    for (int i = xs; i < n; i++) {
        for (int j = ys; j < m; j++) {
            if (check(i + 1, j))
                dp[i + 1][j] = add(dp[i + 1][j], dp[i][j]);
            if (check(i, j + 1))
                dp[i][j + 1] = add(dp[i][j], dp[i][j + 1]);
        }
    }
    for (auto &a: dist[xs][ys]) {
        int x = a / m;
        int y = a % m;
        a = dp[x][y];
    }
}

inline int mul(int a, int b) {
    return (1LL * a * b) % MOD;
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    char c;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cin >> c;
            arr[i][j] = c;
        }
    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        int a;
        cin >> a;
        enters[i].resize(a);
        for (int j = 0; j < a; j++) {
            int x, y;
            cin >> x >> y;
            --x, --y;
            enters[i][j] = (x * m + y);
        }
        cin >> a;
        blocked[i].resize(a);
        for (int j = 0; j < a; j++) {
            int x, y;
            cin >> x >> y;
            --x, --y;
            blocked[i][j] = (x * m + y);
        }
        cin >> a;
        for (int j = 0; j < a; j++) {
            int x, y;
            cin >> x >> y;
            --x, --y;
            stops[i]++;
            int c = x * m + y;
            for (int a : enters[i])
                for (int b : blocked[i]) {
                    int xa = a / m, ya = a % m;
                    int xb = b / m, yb = b % m;
                    dist[xa][ya].push_back(b);
                    dist[xb][yb].push_back(c);
                    dist[xa][ya].push_back(c);
                }
        }

    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (SZ(dist[i][j]))
                precalc(i, j);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            arr[i][j] = 0;
    for (int i = 0; i < q; i++) {
        int ans = 0;
        for (int z = 0; z < stops[i]; z++)
            for (int a : enters[i])
                for (int b : blocked[i]) {
                    int xa = a / m, ya = a % m;
                    int xb = b / m, yb = b % m;
                    int kek = dist[xa][ya][arr[xa][ya]++];
                    int lol = dist[xb][yb][arr[xb][yb]++];
                    int arbidol = dist[xa][ya][arr[xa][ya]++];
                    if (mul(kek, lol) != arbidol)
                        ans++;
                }
        cout << ans << '\n';
    }
//    cout << sizeof(vector<unsigned short>) << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
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
