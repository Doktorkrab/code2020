#include <bits/stdc++.h>
#include <ostream>

// #define FAST_ALLOCATOR_MEMORY 5e8
using namespace std;
using ll = long long;
#ifdef FAST_ALLOCATOR_MEMORY
int allocator_pos = 0;
char allocator_memory[(int) FAST_ALLOCATOR_MEMORY];

inline void *operator new(size_t n) {
    char *res = allocator_memory + allocator_pos;
    allocator_pos += n;
    assert(allocator_pos <= (int) FAST_ALLOCATOR_MEMORY);
    return (void *) res;
}

inline void operator delete(void *) noexcept {}

#endif

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

int n, m, q;
vector<vector<int>> perms;

inline vector<int> apply(vector<int> &a, vector<int> &b) {
    vector<int> res(m);
    for (int i = 0; i < m; i++)
        res[i] = b[a[i]];
    return res;
}

inline ll find_ans(vector<int> &a) {
    ll res = 0;
    for (int i = 0; i < m; i++)
        res += 1LL * (i + 1) * (a[i] + 1);
    return res;
}

void solve_big() {
    vector<vector<int>> prefix(n + 1, vector<int>(m)), prefix1(n + 1, vector<int>(m));
    vector<int> rev(m);
    for (int i = 0; i < m; i++)
        prefix[0][i] = prefix1[0][i] = i;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            rev[perms[i][j]] = j;
        }
        prefix[i + 1] = apply(prefix[i], perms[i]);
        prefix1[i + 1] = apply(rev, prefix1[i]);
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        vector<int> res = apply(prefix1[l - 1], prefix[r]);
        cout << find_ans(res) << '\n';
    }
}

void solve_small() {
    vector<vector<ll>> precalc(n, vector<ll>(n));
    for (int i = 0; i < n; i++) {
        vector<int> tmp(ALL(perms[i]));
        precalc[i][i] = find_ans(tmp);
        for (int j = i + 1; j < n; j++) {
            tmp = apply(tmp, perms[j]);
            precalc[i][j] = find_ans(tmp);
        }
    }

    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        cout << (precalc[l - 1][r - 1]) << '\n';
    }
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    perms.assign(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cin >> perms[i][j];
            perms[i][j]--;
        }
    cin >> q;
    if (1LL * n * n >= m)
        solve_big();
    else
        solve_small();
    return 0;
}

signed main() {
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
