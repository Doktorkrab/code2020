#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;
using ld = long double;

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

struct Fraction {
    ll a = 0, b = 1;

    Fraction() = default;

    Fraction(ll _a, ll _b) : a(_a), b(_b) {}

    Fraction(ll _a) : a(_a), b(1) {}

    bool operator<(const Fraction &oth) const {
        return (__int128) a * oth.b < (__int128) oth.a * b;
    }

    Fraction operator+(const Fraction &oth) const {
        ll a1 = a * oth.b + oth.a * b;
        ll b1 = b * oth.b;
        ll g = gcd(a1, b1);
        return {a1 / g, b1 / g};
    }

    Fraction operator-(const Fraction &oth) const {
        return (*this) + Fraction(-oth.a, oth.b);
    }

    Fraction operator*(const Fraction &oth) const {
        ll a1 = a * oth.a;
        ll b1 = b * oth.b;
        ll g = gcd(a1, b1);
        return Fraction(a1 / g, b1 / g);
    }
};

int n, k;
const int MAXN = 5e4 + 7;
const int MAXK = 155;
const ll INF = 1e16;

ld dp[MAXN][MAXK];
int opt[MAXN][MAXK];
ll pref[MAXN];
ll pref2[MAXN];
ll arr[MAXN];

ll cost(int l, int r) {
    return pref[r] - pref[l];
}

ll cost2(int l, int r) {
    return pref2[r] - pref2[l];
}

int solve() {
    if (!(cin >> n >> k))
        return 1;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(arr, arr + n);

    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + arr[i];
        pref2[i + 1] = pref2[i] + arr[i] * arr[i];
    }
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= k; j++) {
            dp[i][j] = INF;
//            opt[i][j] = n;
        }
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i - 1; j >= 0; j--)
            for (int level = 1; level <= k; level++) {
                if (dp[j][level - 1] >= INF)
                    continue;
                ld now = dp[j][level - 1] + cost2(j, i) - 1.L * cost(j, i) * cost(j, i) / (i - j);
                if (now < dp[i][level]) {
                    dp[i][level] = now;
                    opt[i][level] = j;
                }
            }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= k; j++)
            ass(opt[i - 1][j] <= opt[i][j]);
//    for (int i = 0; i <= n; i++)
//        for (int j = 0; j <= k; j++)
//            cout << 1.L * dp[i][j].a / dp[i][j].b << " \n"[j == k];
    cout << setprecision(20) << fixed << 1.L * dp[n][k] << '\n';
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
