#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
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

const int MAXN = 1e5;
int pos[MAXN];
mt19937 rnd(1488);
int solve() {
    clock_t start = clock();
    if (!(cin >> n))
        return 1;
    vector<int> p(n), c(n), color(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
    }
    vector<int> cc(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        cc[i] = c[i];
    }
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = i;
    vector<pair<int, int>> best;
    vector<pair<int, int>> ans;
    vector<int> perm;
    bool was = false;
    while (clock() - start < 1.9 * CLOCKS_PER_SEC) {
        shuffle(ALL(arr), rnd);
        ans.clear();
        perm = p;
        color = c;
        for (int i = 0; i < n; i++)
            pos[perm[i]] = i;
        for (int x = SZ(arr) - 1; x >= 0; x--) {
            int i = arr[x];
            if (perm[i] != i) {
                if (color[i] == color[pos[i]]) {
                    for (int j : arr)
                        if (color[i] != color[j]) {
                            ans.emplace_back(j, i);
                            ans.emplace_back(i, pos[i]);
                            ans.emplace_back(pos[i], j);
                            break;
                        }
                } else
                    ans.emplace_back(i, pos[i]);
                pos[perm[i]] = pos[i];
                swap(perm[i], perm[pos[i]]);
                swap(color[i], color[pos[i]]);
                pos[i] = i;
            }
        }
        if (!was|| SZ(best) > SZ(ans)) {
            best = ans;
            was = true;
        }
    }
    cout << SZ(best) << '\n';
    for (auto[a, b] : best) {
        cout << a + 1 << ' ' << b + 1 << '\n';
    }
    return 1;
}

signed main() {
#ifdef LOCAL
    freopen("d.in", "r", stdin);
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
