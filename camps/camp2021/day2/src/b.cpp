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
string s, t;

bool solve_n2_plus() {
    assert(count(ALL(t), '0') == 0);
    vector<pair<char, int>> blocks;
    for (char c : s) {
        if (blocks.empty() || blocks.back().first != c)
            blocks.emplace_back(c, 0);
        blocks.back().second++;
    }
    while (SZ(blocks) != 1) {
        bool was = false;
        for (int i = 0; i < SZ(blocks); i++) {
            if (blocks[i].first == '-')
                continue;
            if (i - 1 >= 0 && blocks[i - 1].second < blocks[i].second) {
                blocks[i - 1].first = '+';
                was = true;
                break;
            }
            if (i + 1 < SZ(blocks) && blocks[i + 1].second < blocks[i].second) {
                blocks[i + 1].first = '+';
                was = true;
                break;
            }
        }
        if (!was) {
            return false;
        }
        vector<pair<char, int>> new_blocks;
        for (auto[a, b] : blocks) {
            if (new_blocks.empty() || new_blocks.back().first != a)
                new_blocks.emplace_back(a, 0);
            new_blocks.back().second += b;
        }
        swap(blocks, new_blocks);
    }
    return blocks[0].first != '-';
}

const int MAXN = 1e6 + 7;
int sz[MAXN];
int p[MAXN];
int lft[MAXN];
int rgt[MAXN];
char sign[MAXN];

int find(int x) {
    if (p[x] == x)
        return x;
    return p[x] = find(p[x]);
}

void un(int a, int b, char c) {
    a = find(a);
    b = find(b);
    if (a == b)
        return;
    if (sz[a] > sz[b])
        swap(a, b);
    sz[b] += sz[a];
    p[a] = b;
    lft[b] = min(lft[b], lft[a]);
    rgt[b] = max(rgt[b], rgt[a]);
    sign[b] = c;
}

bool solve_plus() {
    fill(sz, sz + n, 1);
    iota(p, p + n, 0);
    iota(lft, lft + n, 0);
    iota(rgt, rgt + n, 0);
    sign[0] = s[0];
    for (int i = 1; i < n; i++) {
        sign[i] = s[i];
        if (s[i] == s[i - 1]) {
            un(i - 1, i, s[i]);
        }
    }
//    for (int i = 0; i < n; i++)
//        cout << p[i] << " \n"[i + 1 == n];
//    for (int i = 0; i < n; i++)
//        cout << sz[i] << " \n"[i + 1 == n];
//    for (int i = 0; i < n; i++)
//        cout << lft[i] << " \n"[i + 1 == n];
//    for (int i = 0; i < n; i++)
//        cout << rgt[i] << " \n"[i + 1 == n];
//    for (int i = 0; i < n; i++)
//        cout << sign[find(i)] << " \n"[i + 1 == n];
    vector<int> aval;
    for (int i = 0; i < n; i++) {
        if (s[i] != t[i])
            continue;
        bool can = false;
        int x = find(i);
        if (s[lft[x]] != t[lft[x]] || s[rgt[x]] != s[rgt[x]])
            continue;
        if (i - 1 >= 0 && t[i - 1] == s[i] && s[i - 1] != s[i] && sz[find(i - 1)] < sz[find(i)])
            can = true;
        if (i + 1 < n && t[i + 1] == s[i] && s[i + 1] != s[i] && sz[find(i + 1)] < sz[find(i)])
            can = true;
        if (can)
            aval.push_back(find(i));
    }
    while (SZ(aval)) {
        int x = aval.back();
        aval.pop_back();
//        cout << x << endl;
        bool was = true;
        if (x != find(x))
            continue;
        while (was) {
            was = false;
            x = find(x);
            if (lft[x] != 0 &&
                (sign[find(lft[x] - 1)] == sign[x] || (sz[find(lft[x] - 1)] < sz[x] && t[lft[x] - 1] == sign[x])))
                un(lft[x] - 1, x, sign[x]), was = true;
            if (rgt[x] + 1 != n &&
                (sign[find(rgt[x] + 1)] == sign[x] || (sz[find(rgt[x] + 1)] < sz[x] && t[rgt[x] + 1] == sign[x])))
                un(rgt[x] + 1, x, sign[x]), was = true;
        }
    }
    for (int i = 0; i < n; i++) {
        if (sign[find(i)] != t[i])
            return false;
    }
    return true;
}

int solve() {
    if (!(cin >> s >> t))
        return 1;
    n = SZ(s);
    if (solve_plus())
        cout << "Yes\n";
    else
        cout << "No\n";
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
    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------" << endl;
#endif
    }
}
