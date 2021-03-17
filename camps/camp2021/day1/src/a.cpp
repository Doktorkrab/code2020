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
const int MAXN = 5e6 + 7;
int dir[2 * MAXN];
int prefix[2 * MAXN];
int solve() {
    if (!(cin >> n))
        return 1;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> dir[i];
        if (dir[i] == 0)
            dir[i] = -1;
        dir[n + i] = dir[i];
    }
    for (int i = 0; i < 2 * n; i++){
        prefix[i + 1] = prefix[i] + dir[i];
    }
    int best = TMAX(int);
    int where = 0;
    deque<pair<int, int>> have;
    auto add = [&](int i, int x){
        while (SZ(have) && have.back().second >= x)
            have.pop_back();
        have.emplace_back(i, x);
    };
    for (int i = 0; i < n; i++)
        add(i, prefix[i]);
    for (int i = 0; i <= n; i++){
        add(i + n, prefix[i + n]);
        int now = have.begin()->second - prefix[i];
        if (best > now){
            best = now;
            where = i;
        }
        if (have.front().first == i)
            have.pop_front();
    }
    cout << best + count(dir, dir + n, -1) << '\n' << where + 1 << '\n';
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