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

int solve() {
    if (!(cin >> n))
        return 1;
    long long max_all_pow = 0;
    while (((1 << (max_all_pow + 1)) < 20) && ((1 << (max_all_pow + 1)) * (1 << (1 << (max_all_pow + 1))) <= (1 << n))) max_all_pow++;
    if (((1LL << max_all_pow) * (1LL << (1LL << max_all_pow))) == (1LL << n)) {
        for (int mask = 0; mask < (1 << (1 << (max_all_pow))); ++mask) {
            ll cnt = (1 << max_all_pow);
            ll cp = mask;
            while (cp > 0) {
                cp /= 2;
                cnt--;
            }
            for (int ots = 0; ots < cnt; ++ots) {
                cout << 0;
            }
            cp = mask;
            string fuckers;
            while (cp > 0) {
                fuckers += (char) ('0' +  cp % 2);
                cp /= 2;
            }
            reverse(ALL(fuckers));
            cout << fuckers;
        }
        cout << '\n';
        return 0;
    }
    string line;
    for (int mask = 0; mask < (1 << (1 << (max_all_pow))); ++mask) {
        int cnt = (1 << max_all_pow);
        int cp = mask;
        while (cp > 0) {
            cp /= 2;
            cnt--;
        }
        for (int ots = 0; ots < cnt; ++ots) {
            line += '0';
        }
        cp = mask;
        string fuckers;
        while (cp > 0) {
            fuckers += (char) ('0' +  cp % 2);
            cp /= 2;
        }
        reverse(ALL(fuckers));
        line += fuckers;
    }
    set<int> nums_was;
    for (int i = 0; i < line.length(); i += (1 << (max_all_pow + 1))) {
        int curr = 0;
        ll x = 0;
        string tmp = line.substr(i, (1 << (max_all_pow + 1)));
        reverse(ALL(tmp));
        while (SZ(tmp)) {
            x = x * 2 + (tmp.back() - '0');
            tmp.pop_back();
        }
        nums_was.insert(x);
    }
    for (int mask = 0; line.length() < (1 << n); ++mask) {
        if (nums_was.count(mask) != 0) continue;
        int cnt = (1 << (max_all_pow + 1));
        int cp = mask;
        while (cp > 0) {
            cp /= 2;
            cnt--;
        }
        for (int ots = 0; ots < cnt; ++ots) {
            line += '0';
        }
        cp = mask;
        string fuckers;
        while (cp > 0) {
            fuckers += (char) ('0' +  cp % 2);
            cp /= 2;
        }
        reverse(ALL(fuckers));
        line += fuckers;
    }
//    cout << SZ(line);
    cout << line << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
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
