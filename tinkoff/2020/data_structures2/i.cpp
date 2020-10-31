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
struct Node {
    int x = 0;
    ll sum = 0;
    int head = -1;
};
int n;
const int MAXN = 2e5 + 7;
Node nodes[MAXN];
int pnt = 0;

int new_node(int x) {
    nodes[pnt].x = x;
    return pnt++;
}

int versions[MAXN];

int solve() {
    if (!(cin >> n))
        return 1;
    versions[0] = new_node(0);
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        int t, x;
        cin >> t >> x;
        if (x > 0) {
            int node = new_node(x);
            nodes[node].head = versions[t];
            nodes[node].sum = nodes[versions[t]].sum + x;
            versions[i + 1] = node;
        } else {
            versions[i + 1] = nodes[versions[t]].head;
        }
        sum += nodes[versions[i + 1]].sum;
    }
    cout << sum << '\n';
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
