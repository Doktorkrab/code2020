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

bool check(const vector<pair<pair<char, char>, int>> &v) {
    for (auto[x, _] : v) {
        if (x.first != x.second)
            return false;
    }
    return true;
}

bool solve_n2_plus() {
    vector<pair<pair<char, char>, int>> blocks;
    for (int i = 0; i < n; i++) {
        char c = s[i];
        char v = t[i];
        if (blocks.empty() || blocks.back().first != make_pair(c, v)) {
            blocks.emplace_back(make_pair(c, v), 0);
        }
        blocks.back().second++;
    }
    while (!check(blocks)) {
        bool was = false;
        for (int i = 0; i < SZ(blocks); i++) {
            if (i - 1 >= 0 && blocks[i - 1].second < blocks[i].second &&
                blocks[i - 1].first.second == blocks[i].first.first && blocks[i - 1].first.first != blocks[i].first.first) {
                blocks[i - 1].first.first = blocks[i].first.first;
                was = true;
                break;
            }
            if (i + 1 < SZ(blocks) && blocks[i + 1].second < blocks[i].second &&
                blocks[i + 1].first.second == blocks[i].first.first) {
                blocks[i + 1].first.first = blocks[i].first.first;
                was = true;
                break;
            }
        }
        if (!was) {
            return false;
        }
        vector<pair<pair<char, char>, int>> new_blocks;
        for (auto[a, b] : blocks) {
            if (new_blocks.empty() || new_blocks.back().first != a)
                new_blocks.emplace_back(a, 0);
            new_blocks.back().second += b;
        }
        swap(blocks, new_blocks);
        for (auto[a, b] :blocks)
            for (int i = 0; i < b; i++)
                cout << a.first;
        cout << '\n';

        for (auto[a, b] :blocks)
            for (int i = 0; i < b; i++)
                cout << a.second;
        cout << '\n';
        cout << "xxxxxx" << endl;
    }
    return true;
}

int solve() {
    if (!(cin >> s >> t))
        return 1;
    n = SZ(s);
    if (solve_n2_plus())
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
        cout << "------------------------------\n";
#endif
    }
}
