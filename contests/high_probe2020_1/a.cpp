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

ll n;

void solve(int n) {
    vector<int> cnt(10);
    for (int i = 1; i <= n; i++) {
        int t = i;
        while (t > 0) {
            cnt[t % 10]++;
            t /= 10;
        }
    }
    for (int i : cnt)
        cout << i << ' ';
    cout << '\n';
}

vector<ll> cnt_10[13];
vector<ll> cnt_101[13];
ll pow10[13];
ll ans[10];

void add(const vector<ll> &mda, ll lol) {
//    for (int i : mda)
//        cout << i << ' ';
//    cout << " | " << lol << '\n';
    for (int i = 0; i < 10; i++)
        ans[i] += mda[i] * lol;
}

int solve() {
    if (!(cin >> n))
        return 1;
    int p = 0;
    ll tenp = 1;
    cnt_10[0].resize(10);
    cnt_101[0] = cnt_10[0];
    pow10[0] = 1;
    for (int i = 1; i <= 12; i++) {
        cnt_10[i].resize(10);
        cnt_10[i][0] = (10 - tenp) / 9 + p * (1 + tenp);
        cnt_10[i][0] -= (p + 1);
        cnt_10[i][1] = (p + 1) * (tenp);
        cnt_10[i][0]++;
        pow10[i] = 10 * pow10[i - 1];
        for (int j = 2; j < 10; j++)
            cnt_10[i][j] = (p + 1) * tenp;

        cnt_101[i] = cnt_10[i];
        ll tmp = 10;
        for (int j = 1; j <= p; j++) {
            cnt_101[i][0] += tmp;
            tmp *= 10;
        }
        p++;
        tenp *= 10;
    }
    ll prefix = 0;
    string kek = to_string(n);
    vector<ll> have(10);
    int cnt = 0;
    for (int i = 0; i < SZ(kek); i++) {
        int d = kek[i] - '0';
        vector<ll> lol(10);
        ll lolo = prefix;
        while (lolo > 0) {
            lol[lolo % 10]++;
            lolo /= 10;
        }
//        cout << prefix << ' ' << i << '\n';
        for (int dd = 0; dd < d; dd++) {
            lol[dd]++;
            if (prefix * 10 + dd > 0) {
                add(lol, pow10[SZ(kek) - 1 - i]);
                add(cnt_101[SZ(kek) - 1 - i], 1);
            } else {
                if (SZ(kek) - 1 - i)
                    ans[0]--;
                add(cnt_10[SZ(kek) - 1 - i], 1);
            }
//            if (!dd)
//                add(cnt_10[SZ(kek) - 1 - i], 1);
//            else
//            add(cnt_101[SZ(kek) - 1 - i], 1);
            lol[dd]--;
        }
        prefix = prefix * 10 + d;
    }
    vector<ll> lol(10);
    while (prefix > 0) {
        lol[prefix % 10]++;
        prefix /= 10;
    }
    add(lol, 1);
//    ans[0] -= cnt;
    for (ll i : ans)
        cout << i << " ";
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
