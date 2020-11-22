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

using cd = complex<long double>;

void fft(vector<cd> &s, vector<cd> &res, cd x, int n, int bs = 0, int step = 1, int rs = 0) {
    if (n == 1) {
        res[rs] = s[bs];
        return;
    }
    fft(s, res, x * x, n / 2, bs, step * 2, rs);
    fft(s, res, x * x, n / 2, bs + step, step * 2, rs + n / 2);
    cd c = 1;
    for (int i = rs; i < rs + n / 2; i++) {
        auto a = res[i];
        auto b = res[i + n / 2];
        res[i] = a + b * c;
        res[i + n / 2] = a - b * c;
        c *= x;
    }
}

int n;
const unsigned MAXLOG = 19;  // for 250'000
const int MAXN = 1U << MAXLOG;
const int BASE = 1e4;
const int BASE_LEN = 4;
const long double pi = acos(-1.L);

vector<cd> get_number(string s, bool &sign) {
    if (s[0] == '-')
        sign = 1;
    if (s[0] == '-' || s[0] == '+')
        s.erase(s.begin());

    vector<cd> res(MAXN);
    reverse(ALL(s));
    ll x = 1;
    int pnt = 0;
    for (char c : s) {
        res[pnt] += x * (c - '0');
        x *= 10;
        if (x == BASE) {
            x = 1;
            pnt++;
        }
    }
    return res;
}

int solve() {
    string a, b;
    if (!(cin >> a >> b))
        return 1;
    bool sign_a = 0;
    bool sign_b = 0;
    vector<cd> have_a = get_number(a, sign_a);
    vector<cd> have_b = get_number(b, sign_b);
    vector<cd> fa(MAXN), fb(MAXN), ans(MAXN);
    fft(have_a, fa, cd(cos(2 * pi / MAXN), sin(2 * pi / MAXN)), MAXN);
    fft(have_b, fb, cd(cos(2 * pi / MAXN), sin(2 * pi / MAXN)), MAXN);
    for (int i = 0; i < MAXN; i++)
        fa[i] *= fb[i];
    fft(fa, ans, cd(cos(-2 * pi / MAXN), sin(-2 * pi / MAXN)), MAXN);
    vector<ll> ans1(MAXN);
    for (int i = 0; i < MAXN; i++) {
        ans1[i] = round(ans[i].real() / MAXN);
    }
    for (int i = 0; i + 1 < MAXN; i++) {
        ans1[i + 1] += ans1[i] / BASE;
        ans1[i] %= BASE;
    }
    int pnt = MAXN - 1;
    while (pnt >= 0 && ans1[pnt] == 0)
        pnt--;
    if (pnt < 0) {
        cout << "0\n";
        return 0;
    }
    if (sign_a ^ sign_b)
        cout << "-";
    cout << ans1[pnt--];
    for (; pnt >= 0; pnt--)
        cout << setw(BASE_LEN) << setfill('0') << ans1[pnt];
    cout << '\n';
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
