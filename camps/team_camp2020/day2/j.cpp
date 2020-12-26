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

int n;
int a[N];

void scan() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
}

int color[N];

void solve() {
    int s = 0;
    while (s != n && a[s] == a[(s - 1 + n) % n]) {
        ++s;
    }
    if (s == n) {
        return;
    }
    bool flag = (a[s] < a[(s - 1 + n) % n]);
    for (int i = 1; i < n; ++i) {
        if (a[(i + s) % n] == a[(i + s - 1 + n) % n]) {
            color[(i + s) % n] = color[(i + s - 1 + n) % n];
        } else if ((a[(i + s) % n] < a[(i + s - 1 + n) % n]) == flag) {
            color[(i + s) % n] = color[(i + s - 1 + n) % n];
        } else {
            color[(i + s) % n] = !color[(i + s - 1 + n) % n];
            flag = !flag;
        }
    }
}

void print_ans() {
    vector<int> p, q;
    for (int i = 0; i < n; ++i) {
        if (color[(i + 1) % n] == 0) {
            p.push_back(i);
        } else {
            q.push_back(i);
        }
    }
    cout << "YES\n";
    cout << p.size() << '\n';
    for (int i : p) {
        cout << i + 1 << ' ';
    }
    cout << '\n';
    cout << q.size() << '\n';
    for (int i : q) {
        cout << i + 1 << ' ';
    }
    cout << '\n';
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