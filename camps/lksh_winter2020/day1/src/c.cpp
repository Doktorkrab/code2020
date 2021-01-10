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
int ans = 0;

vector<int> z_function(const string &s) {
    int N = SZ(s);
    vector<int> z(N);
    int l = 0, r = 0;
//    z[0] = N;
    for (int i = 1; i < N; i++) {
        if (i < r)
            z[i] = min(r - i, z[i - l]);
        while (z[i] + i < N && s[z[i]] == s[z[i] + i])
            z[i]++;
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

void relax(const string &s_l, const string &s_r, const string &s) {
    int tm = SZ(s_l);
    int tm1 = SZ(s) - tm;
    auto rs_l = string{RALL(s_l)};
    auto rs_r = string{RALL(s_r)};
    auto z1 = z_function(rs_l);
    auto z2 = z_function(s_r + " " + s_l);
    auto z3 = z_function(rs_l + " " + rs_r);
    auto z4 = z_function(s_r);
    if (s_l + s_r == "U$U") {
        cout << rs_l << '\n';
        for (int x : z1)
            cout << x << ' ';
        cout << '\n';

        cout << s_r << " " << s_l << '\n';
        for (int x : z2)
            cout << x << ' ';
        cout << '\n';

        cout << rs_l << " " << rs_r << '\n';
        for (int x : z3)
            cout << x << ' ';
        cout << '\n';

        cout << s_r << '\n';
        for (int x : z4)
            cout << x << ' ';
        cout << '\n';
    }
    auto get_ok = [&](int i, const vector<int> &z) {
        if (0 <= i && i < SZ(z))
            return z[i];
        return 0;
    };
    for (int i = 0; i < SZ(s); i++){
        int l, k1, k2;
        if (i < tm){
            l = tm - i;
            k1 = get_ok(tm - i, z1);
            k2 = get_ok(tm1 + 1 + i, z2);
        }
        else {
            l = i - tm + 1;
            k1 = get_ok(tm + tm1 - (i - tm), z3);
            k2 = get_ok(i - tm + 1, z4);
        }
        if (k1 + k2 >= l) {
//            cout << tm << '\n';
//            cout << s_l << ' ' << s_r << ' ' << i << ' ' << l << ' ' << k1 << ' ' << k2 << '\n';
            ans = max(ans, 2 * l);
        }
    }
}

void rec(const string &s) {
    if (SZ(s) < 2)
        return;
    if (SZ(s) == 2) {
        if (s[0] == s[1])
            ans = max(ans, 2);
        return;
    }
    int tm = (SZ(s)) / 2;
    string s_l = s.substr(0, tm);
    string s_r = s.substr(tm);
    rec(s_l);
    rec(s_r);
    relax(s_l, s_r, s);
}

int solve() {
    string s;
    if (!(cin >> s))
        return 1;
    ans = 0;
    n = SZ(s);
    rec(s);
    cout << ans << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}
