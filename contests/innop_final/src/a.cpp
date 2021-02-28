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
multiset<int> have[2];
string s;
string t;

bool rec(int pos, int d) {
//    cout << s << ' ' << pos << ' ' << d << '\n';
    bool good = false;
    for (int i = 0; i + 1 < n; i++) {
        if (s[i] == '.' && s[i + 1] == '.') {
            good = true;
            break;
        }
    }
    if (!good)
        return false;
    if (pos == d)
        return true;
    if (t[pos] == 'M') {
        for (int i = 0; i < n; i++) {
            if (s[i] == '.') {
                s[i] = 'X';
                if (!rec(pos + 1, d)) {
                    s[i] = '.';
                    return false;
                }
                s[i] = '.';
            }
        }
    } else {
        for (int i = 0; i + 1 < n; i++) {
            if (s[i] == '.' && s[i + 1] == '.') {
                s[i] = s[i + 1] = 'X';
                auto ans = rec(pos + 1, d);
                s[i] = s[i + 1] = '.';
                if (!ans)
                    return false;
            }
        }
    }
    return true;
}

string solve_fast() {
    int now = 0;
    have[0].clear();
    have[1].clear();
    ll sum = 0;
    for (char c : s) {
        if (c == 'X') {
            if (now > 1) {
                have[now % 2 + (now == 2)].insert(now);
                sum += now / 2;
            }
            now = 0;
        } else
            now++;
    }
    if (now > 1) {
        have[now % 2 + (now == 2)].insert(now);
        sum += now / 2;
    }
    string ans;
    auto check = [&]() {
        return sum == 0;
    };
    bool was = check();
    ans += "YN"[was];
    int cnt = 0;
    for (char c : t){
        if (was){
            ans += "N";
            continue;
        }
        if (c == 'M')
            cnt++;
        else {
            if (SZ(have[0])){
                auto top = prev(have[0].end());
                int now = (*top);
                have[0].erase(top);
                sum -= 2;
                have[1].insert(now - 3);
            }
            else if (SZ(have[1])){
                auto top = prev(have[1].end());
                int now = (*top);
                have[1].erase(top);
                sum -= now / 2;
                if (now - 3 > 2){
                    have[0].insert(now - 3);
                }
                else
                    have[1].insert(now - 3);
                sum += (now - 3) / 2;
            }
        }
//        cout << sum << ' ' << cnt << '\n';
//        for (int x : have[0])
//            cout << x << ' ';
//
//        for (int x : have[1])
//            cout << x << ' ';
//        cout << '\n';
        if (sum <= cnt)
            was = true;
        ans += "YN"[was];
    }
    return ans;
}

string solve_slow() {
    string ans;
    for (int i = 0; i <= SZ(t); i++) {
        if (SZ(ans) && ans.back() == 'N')
            ans += 'N';
        else
            ans += "NY"[rec(0, i)];
    }
    return ans;
}

int solve() {
    if (!(cin >> s >> t))
        return 1;
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    if (0) {
        while (true) {
//        n = SZ(s);
            n = rnd() % 15 + 1;
            int m = rnd() % 8 + 1;
            s.clear();
            t.clear();
            s = string(n, '.');
            s[rnd() % n] = 'X';
            for (int i = 0; i < m; i++)
                t += "MC"[rnd() % 2];

            string a1 = solve_slow();
            string a2 = solve_fast();
            if (a1 != a2) {
                cout << s << '\n' << t << '\n' << a1 << '\n' << a2 << '\n';
                return 1;
            }
            cout << "Ok" << endl;
        }
    }
//    n = SZ(s);
//    cout << solve_slow() << '\n';
    cout << solve_fast() << '\n';
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
    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}
