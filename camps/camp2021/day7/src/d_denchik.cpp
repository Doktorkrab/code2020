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

// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2")

using namespace std;

#ifdef _DEBUG
#define DEB 1
#else
#define DEB 0
#endif
#define MTEST() \
  int _t;       \
  cin >> _t;    \
  for (int _tn = 0; _tn < _t; ++_tn)
#define ALL(c) c.begin(), c.end()
#define SZ(c) (int)c.size()

const int N = 1e6;
const int K = 7;
const int DEG[K + 1] = {1, 10, 100, 1000, 10000, 100000, 1000000};
const int MEM = 5;

vector<int> mem[MEM + 1][100000];

vector<int> rec(int k, int x) {
    if (k <= MEM && !mem[k][x].empty()) {
        return mem[k][x];
    }
    vector<int> cur;
    if (x >= DEG[k - 1] || k == 1) {
        cur.push_back(x);
    }
    for (int i = 1; i < k; ++i) {
        int y = x / DEG[k - i];
        int z = x % DEG[k - i];
        vector<int> left = rec(i, y);
        vector<int> right = rec(k - i, z);
        for (int a : left) {
            for (int b : right) {
                cur.push_back(a + b);
                if (-a + b >= 0) {
                    cur.push_back(-a + b);
                }
                if (a - b >= 0) {
                    cur.push_back(a - b);
                }
                cur.push_back(a * b);
                if (b != 0 && a % b == 0) {
                    cur.push_back(a / b);
                }
            }
        }
    }
    sort(ALL(cur));
    cur.erase(unique(ALL(cur)), cur.end());
    if (k <= MEM) {
        mem[k][x] = cur;
    }
    return cur;
}

void print_ans(int k, int x, int base) {
    if (x >= DEG[k - 1] || k == 1) {
        if (x == base) {
            cout << x;
            return;
        } else if (x == -base) {
            cout << -x;
            return;
        }
    }
    for (int i = 1; i < k; ++i) {
        int y = x / DEG[k - i];
        int z = x % DEG[k - i];
        vector<int> left = rec(i, y);
        vector<int> right = rec(k - i, z);
        for (int a : left) {
            for (int b : right) {
                if (a + b == base) {
                    cout << '(';
                    print_ans(i, y, a);
                    cout << ')';
                    cout << '+';
                    cout << '(';
                    print_ans(k - i, z, b);
                    cout << ')';
                    return;
                } else if (-a + b == base) {
                    cout << '-';
                    cout << '(';
                    print_ans(i, y, a);
                    cout << ')';
                    cout << '+';
                    cout << '(';
                    print_ans(k - i, z, b);
                    cout << ')';
                    return;
                } else if (a - b == base) {
                    cout << '(';
                    print_ans(i, y, a);
                    cout << ')';
                    cout << '-';
                    cout << '(';
                    print_ans(k - i, z, b);
                    cout << ')';
                    return;
                } else if (a * b == base) {
                    cout << '(';
                    print_ans(i, y, a);
                    cout << ')';
                    cout << '*';
                    cout << '(';
                    print_ans(k - i, z, b);
                    cout << ')';
                    return;
                } else if (b != 0 && a == base * b) {
                    cout << '(';
                    print_ans(i, y, a);
                    cout << ')';
                    cout << '/';
                    cout << '(';
                    print_ans(k - i, z, b);
                    cout << ')';
                    return;
                }
            }
        }
    }
    cout << "No solution";
}

signed main() {
#if !DEB
    /*freopen("codes.in", "r", stdin);
    freopen("codes.out", "w", stdout);*/
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    /*int r;
    cin >> r;
    if (r != 0) {
      return 0;
    }*/
    for (int x = 0; x < N; ++x) {
        if (DEB) {
            cout << x << ": ";
        }
        print_ans(K - 1, x, 100);
        cout << '\n';
    }
    return 0;
}