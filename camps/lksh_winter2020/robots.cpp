#include <bits/stdc++.h>

using namespace std;
using cd = complex<double>;

const int MAXLOG = 18;
const int MAXN = 1 << MAXLOG;
const double pi = acos(-1);
cd W[MAXN];
int rev[MAXN];

void precalc() {
    int last = 0;
    for (int i = 1; i < MAXN; i++) {
        if (i == (2 << last))
            last += 1;
        rev[i] = rev[i ^ (1 << last)] | (1 << (MAXLOG - 1 - last));
    }

    for (int i = 0; i < MAXN; i++)
        W[i] = {cos(2 * pi * i / MAXN), sin(2 * pi * i / MAXN)};
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
                cd second = a[st + i + len] * W[i << (MAXLOG - (lvl + 1))];

                a[st + i] = first + second;
                a[st + i + len] = first - second;
            }
    }
}

void inv_fft(vector<cd> &a) {
    fft(a);
    for (cd &el : a)
        el /= MAXN;
    reverse(a.begin() + 1, a.end());
}

int32_t main() {
    freopen("robots.in", "r", stdin);
    freopen("robots.out", "w", stdout);
    precalc();
    string s, t;
    int n;
    cin >> n;
    cin >> s >> t;
    reverse(t.begin(), t.end());
    s += s;
    vector<char> letters = {'A', 'C', 'G', 'T'};
    vector<vector<cd>> polynom(4, vector<cd>(MAXN)), polynom1(4, vector<cd>(MAXN));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2 * n; j++)
            polynom[i][j] = (s[j] == letters[i]);
        for (int j = 0; j < n; j++)
            polynom1[i][j] = (t[j] == letters[i]);
        fft(polynom[i]);
        fft(polynom1[i]);
        for (int j = 0; j < MAXN; j++)
            polynom[i][j] *= polynom1[i][j];
        inv_fft(polynom[i]);
    }
    int shift = 0;
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        int64_t sum = 0;
        for (int j = 0; j < 4; j++) {
            sum += round(polynom[j][n + i].real());
//            cout << round(polynom[j][n + i].real()) << ' ' << j << ' ' << i << '\n';
        }
//        cout << i << ' ' << sum << '\n';
        if (sum > ans) {
            ans = sum;
            shift = i;
        }
    }
    cout << ans << ' ' << shift + 1 << '\n';
}
