#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <ostream>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <vector>

using namespace std;

const int N = 1e5;

int n, m;
int a[4 * N];

void scan() {
    cin >> n >> m;
    for (int i = 0; i < 2 * (n + m); ++i) {
        cin >> a[i];
        if (i < n + m) {
            a[i] = n + m - (a[i] - n - m) + n + m;
        } else {
            --a[i];
        }
    }
}

int b[4 * N];

vector<pair<int, int>> mr;

void add_mirror(int i, int j) {
    if (i >= n + m + m) {
        i -= n + m + m;
    }
    if (j >= n + m) {
        j -= n + m;
    }
    mr.push_back({i, j});
}

void rec(int i) {
    if (b[i] == a[i]) {
        return;
    }
    int j = b[a[i]];
    if (a[i] < n + m + m) {
        add_mirror(i, a[i]);
    } else {
        add_mirror(a[i], b[i]);
    }
    swap(b[i], b[b[a[i]]]);
    swap(b[b[i]], b[b[b[a[i]]]]);
    rec(j);
}

void solve() {
    for (int i = 0; i < n; ++i) {
        b[i] = n + m + m + i;
        b[n + m + m + i] = i;
    }
    for (int j = 0; j < m; ++j) {
        b[j + n] = j + n + m;
        b[j + n + m] = j + n;
    }
    for (int j = m - 1; j >= 0; --j) {
        rec(j + n);
    }
}

void print_ans() {
    cout << mr.size() << '\n';
    for (auto e : mr) {
        cout << e.first + 1 << ' ' << e.second + 1 << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    scan();
    solve();
    print_ans();
    return 0;
}