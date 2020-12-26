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
 
long long l, r;

int how_many(string s) {
    int max_ans = 1;
    int cur = 1;
    for (int i = 1; i < s.length(); ++i) {
        if (s[i] != s[i - 1]) cur = 0;
        cur++;
        max_ans = max(max_ans, cur);
    }
    return max_ans;
}

int solve() {
    if (!(cin >> l))
        return 1;
    cin >> r;
    map<int, int> trolling;
    for (long long i = l; i <= r; ++i) {
        trolling[how_many(to_string(i))]++;
    }
    int kek_ans = 0;
    int num = 0;
    for (auto e: trolling) {
        kek_ans = e.second;
        num = e.first;
    }
    cout << num << ' ' << kek_ans << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("h.in", "r", stdin);
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
