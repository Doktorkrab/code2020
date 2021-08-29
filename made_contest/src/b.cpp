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

int n, k;
unordered_map<string, int> cnt;
int ans = 0;

void add(const string &s) {
    if (!cnt.count(s) || cnt[s] == 0)
        ans++;
    cnt[s]++;
}

void erase(const string &s) {
    cnt[s]--;
    if (cnt[s] == 0)
        ans--;
}

int solve() {
    if (!(cin >> n >> k))
        return 1;
    cnt.clear();
    ans = 0;
    string now;
    deque<string> buffer;
    for (int i = 0; i < k; i++) {
        cin >> now;
        add(now);
        buffer.push_back(now);
    }

    int mx = ans;
    for (int i = k; i < n; i++) {
        cin >> now;
        erase(buffer.front());
        buffer.pop_front();
        add(now);
        buffer.push_back(now);
        mx = max(mx, ans);
    }
    cout << mx << '\n';
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
