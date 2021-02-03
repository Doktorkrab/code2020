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
ll matrix[MAXN];
ll matrix1[MAXN];

inline ll get_bit(ll mask, int pos) {
    return (mask >> pos) & 1;
}

ll gauss() {
    int now = 0;
    for (int i = 63; i >= 0; i--) {
        int sel = now;
        for (int j = now; j < n; j++) {
            if (get_bit(matrix[j], i)) {
                sel = j;
                break;
            }
        }
        if (!get_bit(matrix[sel], i))
            continue;
        swap(matrix[sel], matrix[now]);
        for (int j = 0; j < n; j++)
            if (j != now && get_bit(matrix[j], i)) {
                matrix[j] ^= matrix[now];
            }
        now++;
    }
    ll ans = 0;
    for (int i = 0; i < n; i++)
        ans ^= matrix[i];
    return ans;
}

ll slow() {
    ll best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        ll now = 0;
        for (int i = 0; i < n; i++)
            if (get_bit(mask, i))
                now ^= matrix[i];
        best = max(best, now);
    }
    return best;
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

void gen() {
    n = rnd() % 5 + 1;
    for (int i = 0; i < n; i++)
        matrix1[i] = matrix[i] = rnd() % 32;
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++) {
        cin >> matrix[i];
        matrix1[i] = matrix[i];
    }
//    while (1) {
//        gen();
//        ll ans = slow();
//        ll ans1 = gauss();
//        if (ans != ans1){
//            cout << n << '\n';
//            for (int i = 0; i < n; i++)
//                cout << matrix1[i] << '\n';
//            return 1;
//        }
//    }
//    cout << slow() << '\n';
    cout << gauss() << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("n.in", "r", stdin);
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
