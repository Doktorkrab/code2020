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

int n, a;
const int MAXN = 105;
const int MAXA = 2e6 + 7;
const ll INF = 1e18 + 7;
const ll COST = 1e9;


int p[MAXA];
int sz[MAXA];
int min_val[MAXA];
int l[MAXN];
int r[MAXN];
int c[MAXN];
ll dp[MAXA];
vector<int> st;

int get(int v) {
    if (p[v] == v)
        return v;
    return p[v] = get(p[v]);
}

void un(int a, int b) {
    a = get(a);
    b = get(b);
    if (sz[a] > sz[b])
        swap(a, b);
    p[a] = b;
    if (dp[min_val[a]] < dp[min_val[b]])
        min_val[b] = min_val[a];
    sz[b] += sz[a];
}

void add(int pos) {
    min_val[pos] = pos;
    while (SZ(st) && dp[st.back()] > dp[pos]) {
        un(pos, st.back());
        st.pop_back();
    }
    st.push_back(pos);
}

inline ll get_min(int x) {
    assert(min_val[get(x)] != -1);
    return dp[min_val[get(x)]];
}

int solve() {
    if (!(cin >> n >> a))
        return 1;
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i] >> c[i];
    }
    for (int i = 0; i <= a; i++) {
        dp[i] = i * COST;
        sz[i] = 1;
        p[i] = i;
        min_val[i] = -1;  // uninit
    }
    for (int i = a; i >= 0; i--) {
        add(i);
        for (int j = 0; j < n; j++) {
            if (i - l[j] < 0)
                continue;
            ll st = i - l[j];
            if (st + r[j] > a)
                continue;
            dp[st] = max(dp[st], get_min(st + r[j]) - c[j]);
        }
    }
    cout << dp[0] << '\n';
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
