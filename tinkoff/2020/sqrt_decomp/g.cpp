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

const int MAXN = 1e5 + 7;
int n, q;
const int INSERT = 2, GET = 1;
struct Query {
    int l, r, t, index;
};

Query queries[MAXN];
vector<int> prv[MAXN];
int arr[MAXN];  // cur arr
int ans[MAXN];

struct Mex_SQRT {
    const int BLOCK_SIZE = 322;
    int blocks[MAXN]{};
    int arr[MAXN * 2]{};

    void insert(int x, int what) {
        x = min(MAXN - 1, x);
        assert(x >= 0);
        if (arr[x] > 0 && arr[x] + what == 0)
            blocks[x]--;
        if (arr[x] == 0 && arr[x] + what > 0)
            blocks[x]++;
        arr[x] += what;
    }

    int get() {
//        for (int i = 0; i <= 5; i++)
//            cout << arr[i] << " \n"[i == 5];
        for (int block = 0; block < MAXN; block++)
            for (int i = 0; i < BLOCK_SIZE && i + BLOCK_SIZE * block < MAXN; i++)
                if (arr[i + block * BLOCK_SIZE] == 0)
                    return i + block * BLOCK_SIZE;
        assert(0);
    }
};

struct Hist {
    int hist[MAXN]{};
    Mex_SQRT have{};

    explicit Hist(int mx) {
        hist[0] = mx + 1;
        have.insert(0, mx + 1);
    }

    void insert(int x, int who) {
//        cerr << hist[x] << ' ' << who << ' ' << x << '\n';
        have.insert(hist[x], -1);
        hist[x] += who;
        have.insert(hist[x], 1);
    }

    int get() {
        return have.get();
    }
};

pair<int, int> inserts[MAXN];

int solve() {
    if (!(cin >> n >> q))
        return 1;
    vector<int> to_sort;
    to_sort.reserve(n + q + 1);
    to_sort.push_back(0);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        to_sort.push_back(arr[i]);
    }
    int cnt = 0, cnt1 = 0;
    for (int i = 0; i < q; i++) {
        int type, l, r;
        cin >> type >> l >> r;
        l--;
        if (type == INSERT) {
            inserts[cnt++] = {l, r};
            to_sort.push_back(r);
        } else {
            queries[cnt1] = {l, r, cnt, cnt1};
            cnt1++;
        }
    }
    q = cnt1;
    sort(ALL(to_sort));
    to_sort.erase(unique(ALL(to_sort)), to_sort.end());

    for (int i = 0; i < n; i++)
        arr[i] = (int) (lower_bound(ALL(to_sort), arr[i]) - to_sort.begin());
    for (int i = 0; i < cnt; i++)
        inserts[i].second = (int) (lower_bound(ALL(to_sort), inserts[i].second) - to_sort.begin());

    const int BLOCK_SIZE = cbrtl(1LL * n * n);
    sort(queries, queries + cnt1, [&](const Query &a, const Query &b) {
        if (a.t / BLOCK_SIZE != b.t / BLOCK_SIZE)
            return a.t / BLOCK_SIZE < b.t / BLOCK_SIZE;
        if (a.l / BLOCK_SIZE != b.l / BLOCK_SIZE)
            return a.l / BLOCK_SIZE < b.l / BLOCK_SIZE;
        return a.r < b.r;
    });

    int l = 0, r = 0;
    int t = 0;
    Hist histogram(SZ(to_sort));
    for (int i = 0; i < cnt1; i++) {
        auto &qr = queries[i];
        while (t < qr.t) {
            auto[pos, x] = inserts[t];
            if (l <= pos && pos < r) {
                histogram.insert(arr[pos], -1);
                histogram.insert(x, 1);
            }
            prv[pos].push_back(arr[pos]);
            arr[pos] = x;
            t++;
        }
        while (t > qr.t) {
            --t;
            auto[pos, x] = inserts[t];
            int p = prv[pos].back();
            prv[pos].pop_back();
            if (l <= pos && pos < r) {
                histogram.insert(x, -1);
                histogram.insert(p, 1);
            }
            arr[pos] = p;
        }
//        cerr << "t complete\n";
//        cerr << l << ' ' << r << ' ' << t << '\n';
//        cerr << qr.l << ' ' << qr.r << ' ' << qr.t << '\n';

        while (r < qr.r)
            histogram.insert(arr[r++], 1);
        while (l > qr.l)
            histogram.insert(arr[--l], 1);

        while (l < qr.l)
            histogram.insert(arr[l++], -1);
        while (r > qr.r)
            histogram.insert(arr[--r], -1);

        ans[qr.index] = histogram.get();
    }
    for (int i = 0; i < cnt1; i++) {
        cout << ans[i] << '\n';
    }
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
