#include <bits/stdc++.h>

using namespace std;
using cd = uint64_t;

const int MAXLOG = 16;
const int MAXN = 1 << MAXLOG;
const int MOD = 786433;
cd W[MAXN];
int rev[MAXN];

int fast_pow(int64_t a, uint64_t b) {
    uint64_t ans = 1;
    while (b > 0) {
        if (b & 1) {
            ans *= a;
            ans %= MOD;
        }
        a *= a;
        a %= MOD;
        b /= 2;
    }
    return (int) ans;
}


void precalc() {
    int g = fast_pow(10, (MOD - 1) / MAXN);
    int last = 0;
    for (int i = 1; i < MAXN; i++) {
        if (i == (2 << last))
            last += 1;
        rev[i] = rev[i ^ (1 << last)] | (1 << (MAXLOG - 1 - last));
    }
    W[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        W[i] = (W[i - 1] * g) % MOD;
    }
}

void fft(vector<cd> &a) {
    for (int i = 0; i < MAXN; i++)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    for (int lvl = 0; lvl < MAXLOG; ++lvl) {
        int len = (1 << lvl);
        for (int st = 0; st < MAXN; st += 2 * len)
            for (int i = 0; i < len; i++) {
                cd first = a[st + i];
                cd second = (a[st + i + len] * W[i << (MAXLOG - (lvl + 1))]) % MOD;
                a[st + i] = (first + second) % MOD;
                a[st + i + len] = (first + MOD - second) % MOD;
            }
    }
}

int REVERSE_MAXN = fast_pow(MAXN, MOD - 2);

void inv_fft(vector<cd> &a) {
    fft(a);
    for (cd &el : a)
        el = (el * REVERSE_MAXN) % MOD;
    reverse(a.begin() + 1, a.end());
}


int main() {
    precalc();

    int n, h;
    cin >> n >> h;
//    --h;
    vector<vector<cd>> dp(17, vector<cd>(MAXN));
    dp[0][1] = 1;
    dp[1][2] = 2;
    dp[1][3] = 1;
    fft(dp[0]);
    fft(dp[1]);
    for (int i = 2; i <= h; i++) {
        vector<cd> tmp(MAXN), tmp1(MAXN);
        for (int j = 0; j < MAXN; j++) {
            tmp[j] = (dp[i - 2][j] * dp[i - 1][j]) % MOD;
        }
        inv_fft(tmp);
        for (int j = 0; j < MAXN; j++) {
            tmp1[j] = (dp[i - 1][j] * dp[i - 1][j]) % MOD;
        }
        inv_fft(tmp1);
        for (int j = 0; j < MAXN - 1; j++) {
            dp[i][j + 1] = (tmp1[j] + (2 * tmp[j]) % MOD) % MOD;
        }
//        cout << dp[i][n] << ' ' << i << '\n';
        fft(dp[i]);
    }
    inv_fft(dp[h]);
    cout << dp[h][n] << '\n';
}
