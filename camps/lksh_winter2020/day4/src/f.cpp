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
const int MAXN = 1005;
const int MOD = 1e9 + 7;
bitset<MAXN> matrix[MAXN];
vector<pair<int, bool>> fact[MAXN];
vector<int> to_compress;

void factorize(int x, int index) {
    fact[index].clear();
    int old = x;
    for (int f = 2; 1LL * f * f <= old; f++) {
        if (x % f != 0)
            continue;
        fact[index].emplace_back(f, 0);
        while (x % f == 0) {
            fact[index].back().second ^= 1;
            x /= f;
        }
    }
    if (x > 1)
        fact[index].emplace_back(x, 1);
    for (auto[a, _] : fact[index])
        to_compress.push_back(a);
    sort(ALL(fact[index]));
}

int gauss() {
    int now = 0;
    for (int i = 0; i < n; i++) {
        int sel = now;
        for (int j = now; j < SZ(to_compress); j++) {
            if (matrix[j][i]) {
                sel = j;
                break;
            }
        }
        if (!matrix[sel][i])
            continue;
//        cerr << now << ' ' << sel << '\n';
        swap(matrix[sel], matrix[now]);
        for (int j = 0; j < SZ(to_compress); j++)
            if (j != now && matrix[j][i])
                matrix[j] ^= matrix[now];
        now++;
//        for (int j = 0; j < SZ(to_compress); j++) {
//            string x = matrix[j].to_string();
//            reverse(ALL(x));
//            cout << x.substr(0, n) << '\n';
//        }
//        cout << '\n';
    }
//    for (int i = 0; i < SZ(to_compress); i++) {
//        string x = matrix[i].to_string();
//        reverse(ALL(x));
//        cout << x.substr(0, n) << '\n';
//    }
    int cnt = 0;
    for (int i = 0; i < SZ(to_compress); i++)
        if (!matrix[i].none())
            cnt++;
    int have = n - cnt;
    int ans = 1;
    for (int i = 0; i < have; i++)
        ans = (1LL * ans * 2) % MOD;
    return ans;
}

int solve() {
    if (!(cin >> n))
        return 1;
    int x;
    for (int i = 0; i < n; i++) {
        cin >> x;
        factorize(x, i);
    }
    sort(ALL(to_compress));
    assert(SZ(to_compress) < MAXN);
    to_compress.resize(unique(ALL(to_compress)) - to_compress.begin());
    for (int i = 0; i < n; i++) {
        for (auto[a, b] : fact[i]) {
            int pos = (int) (lower_bound(ALL(to_compress), a) - to_compress.begin());
            matrix[pos][i] = b;
        }
    }
//    for (int i = 0; i < SZ(to_compress); i++) {
//        string x = matrix[i].to_string();
//        reverse(ALL(x));
//        cout << x.substr(0, n) << '\n';
//    }
//    cout << '\n';
    cout << max(gauss() - 1, 0) % MOD << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("f.in", "r", stdin);
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
