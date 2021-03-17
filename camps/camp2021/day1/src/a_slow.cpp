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
int dir[MAXN];
int enters[MAXN];
vector<int> kek;

int find_ans(int x) {
    vector<pair<int, int>> have;
    bool was = false;
    for (int i = x; !was || i != x; i = (i + 1) % n) {
        was = true;
//        cout << dir[i] << " ";
        if (!SZ(have) || have.back().first != dir[i])
        have.emplace_back(dir[i], 0);
        have.back().second++;
    }
//    cout << '\n';
    vector<int> prefix0(SZ(have) + 1), prefix1(SZ(have) + 1);
    for (int i = 0; i < SZ(have); i++) {
        prefix0[i + 1] = prefix0[i];
        prefix1[i + 1] = prefix1[i];
        if (have[i].first == 0)
            prefix0[i + 1] += have[i].second;
        else
            prefix1[i + 1] += have[i].second;
    }
    int best = TMAX(int);
    for (int i = 0; i <= SZ(have); i++) {
//        cout << i << ' ' << prefix1[i] + (prefix0[SZ(have)] - prefix0[i]) << '\n';
        best = min(best, prefix1[i] + (prefix0[SZ(have)] - prefix0[i]));
//        best = min(best, prefix0[SZ(have)] - i + 2 * prefix1[i]);
    }

    return best;
}

int solve() {
    if (!(cin >> n))
        return 1;
    kek.clear();
    fill(enters, enters + n, 0);
    for (int i = 0; i < n; i++) {
        cin >> dir[i];
        int v = i, u = (i + 1) % n;
        if (dir[i])
            enters[u]++;
        else
            enters[v]++;
    }
//    find_ans(1);
//    return 0;
    int best = find_ans(0);
    int where = 0;
    for (int i = 0; i < n; i++) {
        if (dir[(i - 1 + n) % n] == dir[i])
            continue;
        int now = find_ans(i);
        if (best > now) {
            best = now;
            where = i;
        }
    }
    cout << best << "\n" << where + 1 << '\n';
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