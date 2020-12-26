#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ostream>

template<class T = int>
inline T readInt();

inline double readDouble();

inline int readUInt();

inline int readChar();  // first non-blank character
inline void readWord(char *s);

inline bool readLine(char *s);  // do not save '\n'
inline bool isEof();

inline int getChar();

inline int peekChar();

inline bool seekEof();

inline void skipBlanks();

template<class T>
inline void writeInt(T x, char end = 0, int len = -1);

inline void writeChar(int x);

inline void writeWord(const char *s);

inline void writeDouble(double x, int len = 0);

inline void flush();

static struct buffer_flusher_t {
    ~buffer_flusher_t() {
        flush();
    }
} buffer_flusher;

/** Read */

static const int buf_size = 4096;

static unsigned char buf[buf_size];
static int buf_len = 0, buf_pos = 0;

inline bool isEof() {
    if (buf_pos == buf_len) {
        buf_pos = 0, buf_len = fread(buf, 1, buf_size, stdin);
        if (buf_pos == buf_len)
            return 1;
    }
    return 0;
}

inline int getChar() {
    return isEof() ? -1 : buf[buf_pos++];
}

inline int peekChar() {
    return isEof() ? -1 : buf[buf_pos];
}

inline bool seekEof() {
    int c;
    while ((c = peekChar()) != -1 && c <= 32)
        buf_pos++;
    return c == -1;
}

inline void skipBlanks() {
    while (!isEof() && buf[buf_pos] <= 32U)
        buf_pos++;
}

inline int readChar() {
    int c = getChar();
    while (c != -1 && c <= 32)
        c = getChar();
    return c;
}

inline int readUInt() {
    int c = readChar(), x = 0;
    while ('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = getChar();
    return x;
}

template<class T>
inline T readInt() {
    int s = 1, c = readChar();
    T x = 0;
    if (c == '-')
        s = -1, c = getChar();
    else if (c == '+')
        c = getChar();
    while ('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = getChar();
    return s == 1 ? x : -x;
}

inline double readDouble() {
    int s = 1, c = readChar();
    double x = 0;
    if (c == '-')
        s = -1, c = getChar();
    while ('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = getChar();
    if (c == '.') {
        c = getChar();
        double coef = 1;
        while ('0' <= c && c <= '9')
            x += (c - '0') * (coef *= 1e-1), c = getChar();
    }
    return s == 1 ? x : -x;
}

inline void readWord(char *s) {
    int c = readChar();
    while (c > 32)
        *s++ = c, c = getChar();
    *s = 0;
}

inline bool readLine(char *s) {
    int c = getChar();
    while (c != '\n' && c != -1)
        *s++ = c, c = getChar();
    *s = 0;
    return c != -1;
}

/** Write */

static int write_buf_pos = 0;
static char write_buf[buf_size];

inline void writeChar(int x) {
    if (write_buf_pos == buf_size)
        fwrite(write_buf, 1, buf_size, stdout), write_buf_pos = 0;
    write_buf[write_buf_pos++] = x;
}

inline void flush() {
    if (write_buf_pos) {
        fwrite(write_buf, 1, write_buf_pos, stdout), write_buf_pos = 0;
        fflush(stdout);
    }
}

template<class T>
inline void writeInt(T x, char end, int output_len) {
    if (x < 0)
        writeChar('-'), x = -x;

    char s[24];
    int n = 0;
    while (x || !n)
        s[n++] = '0' + x % 10, x /= 10;
    while (n < output_len)
        s[n++] = '0';
    while (n--)
        writeChar(s[n]);
    if (end)
        writeChar(end);
}

inline void writeWord(const char *s) {
    while (*s)
        writeChar(*s++);
}

inline void writeDouble(double x, int output_len) {
    if (x < 0)
        writeChar('-'), x = -x;
    assert(x <= (1LLU << 63) - 1);
    long long t = (long long) x;
    writeInt(t), x -= t;
    writeChar('.');
    for (int i = output_len - 1; i > 0; i--) {
        x *= 10;
        t = std::min(9, (int) x);
        writeChar('0' + t), x -= t;
    }
    x *= 10;
    t = std::min(9, (int) (x + 0.5));
    writeChar('0' + t);
}


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

const ll INF = 1e18;
const int NOT_FOUND = 1e9;
const int MAXN = 5e5 + 7;
struct Event {
    int index, l, r;  // [l;r)
};

struct SegmentTree {
    struct Node {
        ll mx = INF;
        ll val = INF;
        ll bare_val = INF;
        ll push_val = 0, push_min = -1;

        Node() = default;

        Node(ll x, ll y) {
            mx = x;
            val = bare_val = y;
        }

        Node(const Node &a, const Node &b) {
            mx = max(a.mx, b.mx);
            val = min(a.val, b.val);
            bare_val = min(a.bare_val, b.bare_val);
        }
    };

    Node *nodes;
    int N;

    explicit SegmentTree(int sz) {
        N = 1;
        while (N < sz)
            N *= 2;
        nodes = new Node[2 * N];
    }

    void clear() {
        fill(nodes, nodes + 2 * N, Node());
    }

    void push(int v) {
        if (nodes[v].push_min == -1)
            return;
        nodes[v].val = nodes[v].bare_val + nodes[v].push_val;
        nodes[v].mx = nodes[v].push_min;
        if (v >= N)
            return;
        nodes[2 * v].push_val = nodes[2 * v + 1].push_val = nodes[v].push_val;
        nodes[2 * v].push_min = nodes[2 * v + 1].push_min = nodes[v].push_min;
        nodes[v].push_val = 0;
        nodes[v].push_min = -1;
    }

    ll get(int v, int tl, int tr, int l, int r) {
        push(v);
        if (r <= tl || tr <= l)
            return INF;
        if (l <= tl && tr <= r)
            return nodes[v].val;
        int tm = (tl + tr) / 2;
        ll ret = min(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
        nodes[v] = Node(nodes[2 * v], nodes[2 * v + 1]);
        return ret;
    }

    ll get(int l, int r) {
        return get(1, 0, N, l, r);
    }

    int get_first_greater(int v, int tl, int tr, int l, int r, int x) {
        push(v);
        if (r <= tl || tr <= l || nodes[v].mx <= x)
            return NOT_FOUND;
        if (tr - tl == 1)
            return tl;
        int tm = (tl + tr) / 2;
        int ret = get_first_greater(v * 2, tl, tm, l, r, x);
        if (ret != NOT_FOUND) {
            push(2 * v + 1);
            nodes[v] = Node(nodes[2 * v], nodes[2 * v + 1]);
            return ret;
        }
        ret = get_first_greater(v * 2 + 1, tm, tr, l, r, x);
        nodes[v] = Node(nodes[2 * v], nodes[2 * v + 1]);
        return ret;
    }

    int get_first_greater(int l, int r, int x) {
        return get_first_greater(1, 0, N, l, r, x);
    }


    void push_val(int v, int tl, int tr, int l, int r, ll mn, ll val) {
        push(v);
        if (r <= tl || tr <= l)
            return;
        if (l <= tl && tr <= r) {
            nodes[v].push_min = mn;
            nodes[v].push_val = val;
            push(v);
            return;
        }
        int tm = (tl + tr) / 2;
        push_val(v * 2, tl, tm, l, r, mn, val);
        push_val(v * 2 + 1, tm, tr, l, r, mn, val);
        nodes[v] = Node(nodes[2 * v], nodes[2 * v + 1]);
    }

    void push_val(int l, int r, ll mn, ll val) {
        push_val(1, 0, N, l, r, mn, val);
    }

    void upd(int v, int tl, int tr, int pos, ll mx, ll bare) {
        push(v);
        if (pos < tl || tr <= pos)
            return;
        if (tr - tl == 1) {
            nodes[v] = Node(mx, bare);
            return;
        }
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, pos, mx, bare);
        upd(v * 2 + 1, tm, tr, pos, mx, bare);
        nodes[v] = Node(nodes[2 * v], nodes[2 * v + 1]);
    }

    void upd(int pos, ll mx, ll bare) {
        upd(1, 0, N, pos, mx, bare);
    }
};

int n, q;
int euler[2 * MAXN];
vector<pair<int, ll>> g[MAXN];
ll prefix[MAXN];
int d[MAXN];
int id[MAXN];
int id_lst[MAXN];
int pnt = 0;
vector<Event> events[2 * MAXN];
vector<Event> events_rev[2 * MAXN];
ll ans[MAXN];

void prepare_euler(int v, int p = -1, int dd = 0) {
    id[v] = pnt;
    euler[pnt++] = v;
    d[v] = dd;
    for (auto[u, w] : g[v]) {
        if (u == p)
            continue;
        prefix[u] = prefix[v] + w;
        prepare_euler(u, v, dd + 1);
        euler[pnt++] = v;
    }
    id_lst[v] = pnt - 1;
}

int solve() {
    n = readInt();
    q = readInt();
    for (int i = 1; i < n; i++) {
        int p = readInt();
        int w = readInt();
        g[i].emplace_back(--p, w);
        g[p].emplace_back(i, w);
    }
    for (int i = 0; i < n; i++)
        sort(ALL(g[i]));
    fill(ans, ans + q, INF);
    pnt = 0;
    prefix[0] = 0;
    prepare_euler(0);

    for (int i = 0; i < q; i++) {
        int v = readInt();
        int l = readInt();
        int r = readInt();
        --v, --l, --r;
        int orig = v;
        v = id[v];
        l = id[l];
        r = id[r] + 1;
        if (r - 1 <= v)
            events[v].push_back({i, l, r});
        if (v <= l)
            events_rev[pnt - v - 1].push_back({i, pnt - r, pnt - l});
        if (l <= v && v < r) {
            if (SZ(g[orig]) == 1)
                ans[i] = 0;
            events[v].push_back({i, l, v});
            events_rev[pnt - v - 1].push_back({i, pnt - r, pnt - v});
        }
    }

    SegmentTree st(pnt);
    for (int iter = 0; iter < 2; iter++) {
        for (int i = 0; i < pnt; i++) {
            ll val_now = prefix[euler[i]];
            ll d_now = d[euler[i]];
            int pos = min(st.get_first_greater(0, i, d_now), i);
            if (SZ(g[euler[i]]) != 1)
                val_now = INF;
            st.upd(i, d_now, val_now);
            st.push_val(pos, i + 1, d_now, -2 * prefix[euler[i]]);
            for (auto[index, l, r] : events[i]) {
                ans[index] = min(ans[index], st.get(l, r) + prefix[euler[i]]);
            }
        }
        copy(events_rev, events_rev + pnt, events);
        reverse(euler, euler + pnt);
        st.clear();
    }
    for (int i = 0; i < q; i++)
        writeInt(ans[i], '\n');
    return 1;
}

signed main() {
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
