#include <bits/stdc++.h>
#include <ostream>

#define FAST_ALLOCATOR_MEMORY 5e8
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
    deque<int> a;
    deque<int> b;
    int pnt = 1;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        if (c == 'a')
            a.push_back(pnt++);
        if (c == 'b')
            b.push_back(pnt++);
        if (c == 'A') {
            cout << a.front() % 10;
            a.pop_front();
        }2
        if (c == 'B') {
            cout << b.front() % 10;
            b.pop_front();
        }
        if (c == '>') {
            while (SZ(a)) {
                b.push_back(a.back());
                a.pop_back();
            }
        }
        if (c == ']') {
            while (SZ(b)) {
                a.push_back(b.back());
                b.pop_back();
            }
        }
        if (c == '<') {
            while (SZ(b) && SZ(a) + 1 < SZ(b)) {
                a.push_back(b.back());
                b.pop_back();
            }
        }
        if (c == '[') {
            while (SZ(a) && SZ(b) + 1 < SZ(a)) {
                b.push_back(a.back());
                a.pop_back();
            }
        }
    }
    cout << '\n';
    return 0;
}

signed main() {
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
