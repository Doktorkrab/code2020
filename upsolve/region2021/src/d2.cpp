#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>

using namespace std;
using ll = long long;
string a, b, c;
int n;

int super_slow() {
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    int ans = 0;
    do {
        int carry = 0;
        bool good = a[perm.back()] != '0' && b[perm.back()] != '0' && c[perm.back()] != '0';
        for (int i = 0; i < n; i++) {
            int aa = a[perm[i]] - '0';
            int bb = b[perm[i]] - '0';
            int cc = c[perm[i]] - '0';
            if ((aa + bb + carry) % 10 != cc) {
                good = false;
                break;
            }
            carry = (aa + bb + carry) / 10;
        }
        good &= carry == 0;
        ans += good;
    } while (next_permutation(perm.begin(), perm.end()));
    return ans;
}

const int MAXN = 18;
const int MOD = 1e9 + 7;
int dp[3][1 << MAXN];

int slow() {
    dp[0][0] = 1;
    int lst = (1 << n);
    lst--;
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if ((mask >> i) & 1) {
                if (lst == mask && (a[i] == '0' || b[i] == '0' || c[i] == '0'))
                    continue;
                int new_m = mask ^(1 << i);
                int have = (a[i] - '0') + (b[i] - '0');
                int d = have % 10, car = have / 10;
                if (d == c[i] - '0')
                    dp[car][mask] = (dp[car][mask] + dp[0][new_m]) % MOD;
                else if ((d + 1) % 10 == c[i] - '0')
                    dp[((a[i] - '0') + (b[i] - '0') + 1) / 10][mask] =
                            (dp[((a[i] - '0') + (b[i] - '0') + 1) / 10][mask] + dp[1][new_m]) % MOD;
            }
        }
    }
    return dp[0][lst];
}

int maybe() {
    vector<int> types(4);
    vector<int> zero_types(4);
    for (int i = 0; i < n; i++) {
        int have = (a[i] - '0') + (b[i] - '0');
        int d = have % 10, car = have / 10;
        if (d == c[i] - '0') {
            types[car]++;
            if (a[i] == '0' || b[i] == '0' || c[i] == '0')
                zero_types[car]++;
        } else if ((d + 1) % 10 == c[i] - '0') {
            have++;
            d = have % 10, car = have / 10;
            types[2 + car]++;
            if (a[i] == '0' || b[i] == '0' || c[i] == '0')
                zero_types[2 + car]++;
        } else
            return 0;
    }
    int &t1 = types[0];
    int &t2 = types[1];
    int &t3 = types[2];
    int &t4 = types[3];
    if (t2 != t3)
        return 0;
    int &zt1 = zero_types[0];
    int &zt2 = zero_types[1];
    int &zt3 = zero_types[2];
    int &zt4 = zero_types[3];
    vector<vector<vector<vector<vector<int>>>>> dp(2, vector<vector<vector<vector<int>>>>(t1 + 1,
                                                                                          vector<vector<vector<int>>>(
                                                                                                  t2 + 1,
                                                                                                  vector<vector<int>>(
                                                                                                          t3 + 1,
                                                                                                          vector<int>(
                                                                                                                  t4 +
                                                                                                                  1)))));
    dp[0][0][0][0][0] = 1;
    for (int i = 0; i <= t1; i++) {
        for (int j = 0; j <= t2; j++) {
            for (int k = 0; k <= t3; k++) {
                for (int x = 0; x <= t4; x++) {
                    if (i + j + k + x == 0)
                        continue;
                    if (i > 0)
                        dp[0][i][j][k][x] = dp[0][i - 1][j][k][x];
                    if (k > 0)
                        dp[0][i][j][k][x] = (dp[0][i][j][k][x] + dp[1][i][j][k - 1][x]) % MOD;

                    if (j > 0)
                        dp[1][i][j][k][x] = dp[0][i][j - 1][k][x];
                    if (x > 0)
                        dp[1][i][j][k][x] = (dp[1][i][j][k][x] + dp[1][i][j][k][x - 1]) % MOD;
                }
            }
        }
    }
    int f1 = 1;
    int f2 = 1;
    int f3 = 1;
    int f4 = 1;
    for (int i = 1; i < t1; i++)
        f1 = (1LL * i * f1) % MOD;
//    f1 = (f1 * (t1 - zt1)) % MOD;
    for (int i = 1; i <= t2; i++)
        f2 = (1LL * i * f2) % MOD;
    for (int i = 1; i < t3; i++)
        f3 = (1LL * i * f3) % MOD;
//    f3 = (f3 * (t3 - zt3)) % MOD;
    for (int i = 1; i <= t4; i++)
        f4 = (1LL * i * f4) % MOD;
//    f1 = (1LL * f2 * f1) % MOD * f4 % MOD;
//    f3 = (1LL * f2 * f3) % MOD * f4 % MOD;
    int ans = 0;
    if (t1 > 0)
        ans = 1LL * dp[0][t1 - 1][t2][t3][t4] * f3 % MOD * max(t3, 1) % MOD * f1 % MOD * (t1 - zt1) % MOD * f2 % MOD * f4 % MOD;
    if (t3 > 0) {
        int t = dp[1][t1][t2][t3 - 1][t4];
        t = 1LL * t * f3 % MOD;
        t = 1LL * t * (t3 - zt3) % MOD;
        t = 1LL * t * f1 % MOD;
        t = 1LL * t * max(1, t1) % MOD;
        t = 1LL * t * f2 % MOD;
        t = 1LL * t * f4 % MOD;
        ans = (ans + t) % MOD;
    }
    return ans;
}
int get_fact(int x){
    int ans = 1;
    for (int i = 1; i <= x; i++)
        ans = 1LL * ans * i % MOD;
    return ans;
}
int bin_p(int a, int b){
    int ret = 1;
    for (; b > 0; b /= 2){
        if (b & 1)
            ret = 1LL * ret * a % MOD;
        a = 1LL * a * a % MOD;
    }
    return ret;
}
int inv(int x){
    return bin_p(x, MOD - 2);
}
int full(){
    vector<int> types(4);
    vector<int> zero_types(4);
//    cerr << "here\n";
    for (int i = 0; i < n; i++) {
        int have = (a[i] - '0') + (b[i] - '0');
//        cout << a[i] << ' ' << b[i] << ' ' << c[i] << '\n';
        int d = have % 10, car = have / 10;
        if (d == c[i] - '0') {
            types[car]++;
            if (a[i] == '0' || b[i] == '0' || c[i] == '0')
                zero_types[car]++;
        } else if ((d + 1) % 10 == c[i] - '0') {
            have++;
            d = have % 10, car = have / 10;
            types[2 + car]++;
            if (a[i] == '0' || b[i] == '0' || c[i] == '0')
                zero_types[2 + car]++;
        } else
            return 0;
    }
    int &t1 = types[0]; // a
    int &t2 = types[1]; // c
    int &t3 = types[2]; // b
    int &t4 = types[3]; // d

    int &zt1 = zero_types[0];
    int &zt2 = zero_types[1];
    int &zt3 = zero_types[2];
    int &zt4 = zero_types[3];

    if (t2 != t3)
        return 0;
    if (t2 == 0 && t4 == 0){
        int ans = 1;
        for (int i = 1; i < t1; i++)
            ans = (1LL * ans * i) % MOD;
        return 1LL * ans * (t1 - zt1) % MOD;
    }
    int ans_b = 1LL * get_fact(t1 + t3 - 1) * get_fact(t3 + t4 - 1) % MOD;
    int t = 1LL * t3 * t3 % MOD;
    ans_b = 1LL * ans_b * t % MOD;
    int ans_a = 1LL * get_fact(t1 + t3) * get_fact(t4 + t3 - 1) % MOD;
    ans_a = 1LL * ans_a * t3 % MOD;
    ans_a = (ans_a + MOD - ans_b) % MOD;
    ans_a = 1LL * ans_a * (t1 - zt1) % MOD;
    ans_a = 1LL * ans_a * inv(t1) % MOD;
    ans_b = 1LL * ans_b * (t3 - zt3) % MOD;
    ans_b = 1LL * ans_b * inv(t3) % MOD;
    return (ans_a + ans_b) % MOD;
}

void stress() {
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    while (true) {
        n = 3;
        a.resize(5);
        b.resize(5);
        c.resize(5);
        for (int i = 0; i < n; i++) {
            a[i] = rnd() % 9 + '1';
            b[i] = rnd() % 9 + '1';
            c[i] = rnd() % 9 + '1';
        }
        int ans = super_slow();
        int btr = maybe();
        if (ans != btr) {
            cout << a << '\n' << b << '\n' << c << '\n';
            cout << ans << ' ' << btr << '\n';
            exit(1);
        }
    }
}

signed main() {
#ifdef LOCAL
    freopen("d2.in", "r", stdin);
#endif
//    stress();
    cin >> a >> b >> c;
    n = a.size();
    cout << full() << '\n';
//    cout << slow() << '\n';
}