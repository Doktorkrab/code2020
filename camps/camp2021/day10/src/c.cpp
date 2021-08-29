#pragma GCC optimize("O3,Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,abm,mmx,popcnt,avx,avx2")
#include <bits/stdc++.h>
#include <ostream>
/** Fast input-output */

template <class T = int> inline T readInt();
inline double readDouble();
inline int readUInt();
inline int readChar(); // first non-blank character
inline void readWord( char *s );
inline bool readLine( char *s ); // do not save '\n'
inline bool isEof();
inline int getChar();
inline int peekChar();
inline bool seekEof();
inline void skipBlanks();

template <class T> inline void writeInt( T x, char end = 0, int len = -1 );
inline void writeChar( int x );
inline void writeWord( const char *s );
inline void writeDouble( double x, int len = 0 );
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

template <class T>
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

inline void readWord( char *s ) {
    int c = readChar();
    while (c > 32)
        *s++ = c, c = getChar();
    *s = 0;
}

inline bool readLine( char *s ) {
    int c = getChar();
    while (c != '\n' && c != -1)
        *s++ = c, c = getChar();
    *s = 0;
    return c != -1;
}

/** Write */

static int write_buf_pos = 0;
static char write_buf[buf_size];

inline void writeChar( int x ) {
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

template <class T>
inline void writeInt( T x, char end, int output_len ) {
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

inline void writeWord( const char *s ) {
    while (*s)
        writeChar(*s++);
}

inline void writeDouble( double x, int output_len ) {
    if (x < 0)
        writeChar('-'), x = -x;
    assert(x <= (1LLU << 63) - 1);
    long long t = (long long)x;
    writeInt(t), x -= t;
    writeChar('.');
    for (int i = output_len - 1; i > 0; i--) {
        x *= 10;
        t = std::min(9, (int)x);
        writeChar('0' + t), x -= t;
    }
    x *= 10;
    t = std::min(9, (int)(x + 0.5));
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

int n, m, d;
const int MAXN = 2e6 + 7;
const int INF = 1e9;
struct Edge {
    int v, u, t;
};

vector<int> g[MAXN];
vector<pair<int, int>> g1[MAXN];
int dist[MAXN];
bool used[MAXN];
int pnt = 0;

void add_edge(int v, int u, int w) {
    g1[v].emplace_back(u, w);
}

struct SegmentTree {
    struct Node {
        int vertex;
    };
    vector<Node> nodes;
    int N;

    SegmentTree() = default;

    SegmentTree(int sz, vector<int> &x) {
        N = 1;
        while (N < sz)
            N *= 2;
        nodes.resize(2 * N);
        for (int i = 1; i < N; i++)
            nodes[i].vertex = pnt++;
        for (int i = 0; i < sz; i++)
            nodes[i + N].vertex = x[i];
        for (int i = sz; i < N; i++)
            nodes[i + N].vertex = pnt++;

        for (int i = 1; i < N; i++) {
            add_edge(nodes[i].vertex, nodes[2 * i].vertex, 0);
            add_edge(nodes[i].vertex, nodes[2 * i + 1].vertex, 0);
        }
    }

    void push(int v, int tl, int tr, int l, int r, int x) {
        if (r <= tl || tr <= l)
            return;
        if (l <= tl && tr <= r) {
            add_edge(x, nodes[v].vertex, 1);
            return;
        }
        int tm = (tl + tr) / 2;
        push(v * 2, tl, tm, l, r, x);
        push(v * 2 + 1, tm, tr, l, r, x);
    }

    void push(int l, int r, int x) {
        push(1, 0, N, l, r, x);
    }
};


Edge edges[MAXN];
SegmentTree sts[MAXN];

deque<int> q;

void bfs(int v) {
    fill(dist, dist + pnt, INF);
    fill(used, used + pnt, false);
    for (int i = 0; i < 2 * m; i++)
        if (edges[i].v == v)
            q.push_back(i), dist[i] = 1;
    while (SZ(q)) {
        int v = q.front();
        q.pop_front();
        if (used[v])
            continue;
        used[v] = true;
        for (auto[u, w] : g1[v]) {
            if (dist[u] > dist[v] + w) {
                dist[u] = dist[v] + w;
                if (w == 0)
                    q.push_front(u);
                else
                    q.push_back(u);
            }
        }
    }
}

int solve() {
    n = readInt();
    m = readInt();
    d = readInt();
    for (int i = 0; i < n; i++)
        g[i].clear();
    for (int i = 0; i < m; i++) {
        int v, u, t;
        v = readInt();
        u = readInt();
        t = readInt();
        edges[2 * i] = {--v, --u, t};
        edges[2 * i + 1] = {u, v, t};
        g[v].push_back(2 * i);
        g[u].push_back(2 * i + 1);
    }
    pnt = 2 * m;
    for (int i = 0; i < n; i++) {
        sort(ALL(g[i]), [&](int a, int b) {
            return edges[a].t < edges[b].t;
        });
        sts[i] = SegmentTree(SZ(g[i]), g[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int x : g[i]) {
            int &t = edges[x].t;
            t -= d;
            int beg = (int) (lower_bound(ALL(g[edges[x].u]), x, [&](int a, int b) {
                return edges[a].t < edges[b].t;
            }) - g[edges[x].u].begin());
            t += 2 * d;
            int lst = (int) (upper_bound(ALL(g[edges[x].u]), x, [&](int a, int b) {
                return edges[a].t < edges[b].t;
            }) - g[edges[x].u].begin());
            t -= d;
            sts[edges[x].u].push(beg, lst, x);
        }
    }
    int q = readInt();
    while (q--) {
        int v, u;
        cin >> v >> u;
        v = readInt() - 1;
        u = readInt() - 1;
        bfs(v);
        int best = TMAX(int);
        for (int i = 0; i < 2 * m; i++)
            if (edges[i].u == u)
                best = min(best, dist[i]);
        if (best >= INF)
            writeInt(-1, '\n');
        else
            writeInt(best, '\n');
    }
    return 1;
}

signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
#endif
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