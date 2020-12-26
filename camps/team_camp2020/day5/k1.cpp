#pragma GCC optimize("O3")


/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#define VERSION "0.1.5"

#include <cassert>
#include <cstdio>
#include <algorithm>

/** Fast allocation */
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
//#define int ll
int n, m;
int t;
const int MAXN = 3e3 + 5;
const int MAXT = 2e5 + 7;
const int MAXM = 505;
// [i;t)
// (x_a, y_a)
// d_x, d_y - shift x_0 y_0
// min j > i: x_a = dx_j-dx_i+x0, y_a = dy_j-dy_i+y0
// dx_j = x_a+dx_i-x0, dy_j = y_a+dy_i-y0
// map[{dx_j, dy_j}] = j
// dx_j = n - x_0 + dx_i || dx_j = dx_i - x0 - 1
// dy_j = n - y_0 + dy_i || dy_j = dy_i - y0 - 1
// t*#moun*log_t
// for (i = t - 1;
int pnt = 0;
pair<int, int> hills[MAXM];
unordered_map<int, unordered_map<int, int>> can;
unordered_map<int, int> can_x;
unordered_map<int, int> can_y;
int lol = t + 1;
inline int &get(int x, int y) {
    if (!can[x].count(y))
        can[x][y] = t + 1;
    return can[x][y];
}
inline int& get_x(int x){
    if (!can_x.count(x))
        can_x[x] = t + 1;
    return can_x[x];
}
inline int& get_y(int x){
    if (!can_y.count(x))
        can_y[x] = t + 1;
    return can_y[x];
}

pair<int, int> get_shift(char c) {
    if (c == 'U')
        return make_pair(-1, 0);
    if (c == 'D')
        return make_pair(1, 0);
    if (c == 'L')
        return make_pair(0, -1);
    if (c == 'R')
        return make_pair(0, 1);
    assert(0);
}

int dx[MAXT], dy[MAXT];
string s;

int solve() {
    if (!(cin >> n >> t >> s))
        return 1;
    lol = t + 1;
    int x0, y0;
    char c;
    pnt = 0;
    can.reserve(MAXT);
    can_x.reserve(MAXT);
    can_y.reserve(MAXT);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cin >> c;
            if (c == '.')
                continue;
            if (c == '#')
                hills[pnt++] = {i, j};
            if (c == '@')
                x0 = i, y0 = j;
        }
    int x = 0, y = 0;
    for (int i = 0; i < t; i++) {
        dx[i] = x, dy[i] = y;
        auto[sx, sy] = get_shift(s[i]);
        x += sx;
        y += sy;
    }
    dx[t] = x, dy[t] = y;
//    cerr << dx[t] + MAXN << ' ' << dy[t] + MAXN << '\n';
    get(dx[t], dy[t]) = t;
    get_x(dx[t]) = t;
    get_y(dy[t]) = t;
    ll ans = 0;
    for (int i = t - 1; i >= 0; i--) {
        int mn = t;
        for (int j = 0; j < pnt; j++)
            // dx_j = x_a+dx_i-x0, dy_j = y_a+dy_i-y0
            mn = min(mn, get(hills[j].first + dx[i] - x0, hills[j].second + dy[i] - y0) - 1);

        // dx_j = n - x_0 + dx_i || dx_j = dx_i - x0 - 1
        // dy_j = n - y_0 + dy_i || dy_j = dy_i - y0 - 1
        mn = min(mn, get_x(n - x0 + dx[i]) - 1);
        mn = min(mn, get_x(-1 - x0 + dx[i]) - 1);
        mn = min(mn, get_y(n - y0 + dy[i]) - 1);
        mn = min(mn, get_y(-1 - y0 + dy[i]) - 1);
        get(dx[i], dy[i]) = i;
        get_x(dx[i]) = get_y(dy[i]) = i;
//        cout << i << ' ' << mn << '\n';
        ans += mn - i;
    }
    cout << ans << '\n';
    return 0;
}

signed main() {
    freopen("robot.in", "r", stdin);
    freopen("robot.out", "w", stdout);
//    ios::sync_with_stdio(0);
//    cin.tie(0);
//    cout.tie(0);
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