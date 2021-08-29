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
string s;
string ans1;

int check(int x) {
    int was = 0;
    int cnt = 0;
    int ans = 0;
    ans1.clear();
    string zeroes;
    for (int i = 0; i < x; i++)
        zeroes += '0';

    for (int i = 0; i < n; i++) {
        if (s[i] == '0')
            was++;
        if (s[i] == '1') {
            if (was >= x)
                was = 0, cnt++, ans += x + 1, ans1.append(zeroes).append("1");
        }
    }
    if (was < x)
        cnt--, ans--, ans1.pop_back();
    else
        ans += x, ans1.append(zeroes);
    return (cnt > 0 ? ans : -1);

}
vector<int> zeroes;
vector<int> nxt;
int check1(int x, bool restore = false){
    if (SZ(zeroes) < x)
        return -1;
    ans1.clear();
    string zeroes1;
    if (restore) {
        for (int i = 0; i < x; i++)
            zeroes1 += '0';
    }
    int cnt = 0;
    for (int i = x - 1; i < SZ(zeroes); i += x){
        cnt++;
        if (nxt[i] == -1)
            break;
        i = nxt[i];
    }
    if (restore) {
        for (int i = 0; i + 1 < cnt; i++)
            ans1.append(zeroes1).append("1");
        ans1.append(zeroes1);
    }
    if (cnt < 2)
        return -1;
    return cnt * x + cnt - 1;
}

int solve() {
    if (!(cin >> n >> s))
        return 1;
    zeroes.clear();
    for (int i = 0; i < n; i++)
        if (s[i] == '0')
            zeroes.push_back(i);
    nxt.resize(SZ(zeroes) + 1);
    nxt.back() = -1;
    for (int i = SZ(zeroes) - 1; i >= 0; i--){
        nxt[i] = nxt[i + 1];
        if (zeroes[i] + 1 < n && s[zeroes[i] + 1] == '1')
            nxt[i] = i;
    }
    int best = count(ALL(s), '1'), where = -1;
    for (int i = n; i > 0; i--)
        if (check1(i) > best) {
            best = check1(i);
            where = i;
        }
    if (where == -1){
        cout << best << '\n';
        for (int i = 0; i < best; i++)
            cout << "1";
        cout << '\n';
        return 0;
    }
    check1(where, true);
    cout << best << '\n';
    cout << ans1 << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
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
