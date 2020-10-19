#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;
#define FAST_ALLOCATOR_MEMORY 1e8
#ifdef FAST_ALLOCATOR_MEMORY
int allocator_pos = 0;
	char allocator_memory[(int)FAST_ALLOCATOR_MEMORY];
	inline void * operator new ( size_t n ) {
		char *res = allocator_memory + allocator_pos;
		allocator_pos += n;
		assert(allocator_pos <= (int)FAST_ALLOCATOR_MEMORY);
		return (void *)res;
	}
	inline void operator delete ( void * ) noexcept { }
	//inline void * operator new [] ( size_t ) { assert(0); }
	//inline void operator delete [] ( void * ) { assert(0); }
#endif
#define int ll
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
int k;
const int MAXN = 1e5 + 7;
const int MAXC = 2e8 + 7;
int fenwick[3 * MAXN];

void add(int pos, int x) {
    for (int i = pos; i < 3 * MAXN; i |= i + 1)
        fenwick[i] += x;
}

int get(int r) {
    int ans = 0;
    for (int i = r; i >= 0; i = (i & (i + 1)) - 1)
        ans += fenwick[i];
    return ans;
}

const int INSERT = 0, OPEN = -1, CLOSE = 1;

struct Query {
    int x, type, l, r;

    bool operator<(const Query &oth) const {
        return tie(x, type, l, r) < tie(oth.x, oth.type, oth.l, oth.r);
    }
};

int get(int l, int r) {
    return get(r) - get(l - 1);
}

Query queries[3 * MAXN];
pair<int, int> points[MAXN];

bool check(int to_check) {
    int pnt = 0;
    vector<int> to_sort;
    to_sort.reserve(3 * n);
    for (int i = 0; i < n; i++) {
        auto[x, y] = points[i];
        to_sort.push_back(y + to_check);
        to_sort.push_back(y - to_check);
        to_sort.push_back(y);
        queries[pnt++] = {x - to_check, OPEN, y - to_check, y + to_check};
        queries[pnt++] = {x, INSERT, y, y};
        queries[pnt++] = {x + to_check, CLOSE, y - to_check, y + to_check};
    }
    sort(ALL(to_sort));
    to_sort.erase(unique(ALL(to_sort)), to_sort.end());
    for (int i = 0; i < pnt; i++) {
        queries[i].l = lower_bound(ALL(to_sort), queries[i].l) - to_sort.begin();
        queries[i].r = lower_bound(ALL(to_sort), queries[i].r) - to_sort.begin();
    }
    sort(queries, queries + pnt);
//    for (int i = 0; i < n; i++) {
//        auto[x, y] = points[i];
//        cout << x << ' ' << y << '\n';
//    }
    int m = pnt;
    int ret = 0;
    for (int i = 0; i < m; i++) {
        auto q = queries[i];
        if (q.type == INSERT) {
//            cout << "INSERT " << q.x  << ' ' << q.l << '\n';
            add(q.l, 1);
        }
        if (q.type == OPEN) {
//            cout << "OPEN " << q.x + to_check << ' ' << q.l << ' ' << q.r << ' ' << get(q.l, q.r) << '\n';
            ret -= get(q.l, q.r);
        }
        if (q.type == CLOSE) {
//            cout << "CLOSE " << q.x - to_check << ' ' << q.l << ' ' << q.r << ' ' << get(q.l, q.r) << '\n';
            ret += get(q.l, q.r);
        }
    }
//    cout << to_check << ' ' << ret << ' ' << k << '\n';
    fill(fenwick, fenwick + 3 * MAXN, 0);
    return (ret - n) / 2 < k;
}

int solve() {
    if (!(cin >> n >> k))
        return 1;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        points[i] = {x - y, x + y};
    }
    int l = 0, r = 5e8;
//    check(2);
//    return 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
//        cout << m << ' ' << check(m) << '\n';
        if (check(m))
            l = m;
        else
            r = m;
    }
    cout << r << '\n';
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
