//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <ostream>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <vector>

/** Fast input-output */

template<class T = int>
inline T readInt();

inline double readDouble();

inline int readUInt();

inline int readChar(); // first non-blank character
inline void readWord(char *s);

inline bool readLine(char *s); // do not save '\n'
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
//#define int long long

const int N = 1e6 + 7;

int n;
int a[N];

void scan() {
    n = readInt();
    for (int i = 0; i < n; ++i) {
        a[i] = readInt();
    }
}

const ll INF = 1e18 + 7;

ll d[N];
ll t1[4 * N];

void build1(int pos, int l, int r) {
    if (r - l == 1) {
        t1[pos] = d[l];
    } else {
        build1(2 * pos + 1, l, l + r >> 1);
        build1(2 * pos + 2, l + r >> 1, r);
        t1[pos] = min(t1[2 * pos + 1], t1[2 * pos + 2]);
    }
}

void upd1(int pos, int l, int r, int i, ll x) {
    if (i < l || i >= r) {
        return;
    } else if (r - l == 1) {
        t1[pos] += x;
    } else {
        upd1(2 * pos + 1, l, l + r >> 1, i, x);
        upd1(2 * pos + 2, l + r >> 1, r, i, x);
        t1[pos] = min(t1[2 * pos + 1], t1[2 * pos + 2]);
    }
}

ll get1(int pos, int l, int r, int ql, int qr) {
    if (r <= ql || qr <= l) {
        return INF;
    } else if (ql <= l && r <= qr) {
        return t1[pos];
    } else {
        return min(get1(2 * pos + 1, l, l + r >> 1, ql, qr),
                   get1(2 * pos + 2, l + r >> 1, r, ql, qr));
    }
}

ll t2[4 * N], d2[4 * N];

void build2(int pos, int l, int r) {
    if (r - l == 1) {
        t2[pos] = a[l];
    } else {
        build2(2 * pos + 1, l, l + r >> 1);
        build2(2 * pos + 2, l + r >> 1, r);
    }
}

void push(int pos, int l, int r) {
    if (d2[pos]) {
        if (r - l > 1) {
            d2[2 * pos + 1] += d2[pos];
            d2[2 * pos + 2] += d2[pos];
        }
        t2[pos] += d2[pos];
        d2[pos] = 0;
    }
}

void upd2(int pos, int l, int r, int ql, int qr, ll x) {
    push(pos, l, r);
    if (r <= ql || qr <= l) {
        return;
    } else if (ql <= l && r <= qr) {
        d2[pos] += x;
        push(pos, l, r);
    } else {
        upd2(2 * pos + 1, l, l + r >> 1, ql, qr, x);
        upd2(2 * pos + 2, l + r >> 1, r, ql, qr, x);
    }
}

void upd_v2(int pos, int l, int r, int i, ll x) {
    push(pos, l, r);
    if (i < l || i >= r) {
        return;
    } else if (r - l == 1) {
        d2[pos] += x;
        push(pos, l, r);
    } else {
        upd_v2(2 * pos + 1, l, l + r >> 1, i, x);
        upd_v2(2 * pos + 2, l + r >> 1, r, i, x);
    }
}

ll get2(int pos, int l, int r, int i) {
    push(pos, l, r);
    if (i < l || i >= r) {
        return 0;
    } else if (r - l == 1) {
        return t2[pos];
    } else {
        return get2(2 * pos + 1, l, l + r >> 1, i) +
               get2(2 * pos + 2, l + r >> 1, r, i);
    }
}

void prepare() {
    d[0] = INF;
    for (int i = 1; i < n; ++i) {
        d[i] = a[i] - a[i - 1];
    }
    build1(0, 0, n);
    build2(0, 0, n);
}

void mainloop() {
    int m = readInt();
    while (m--) {
        int type = readInt();
        if (type == 1) {
            int l, r, x;
            l = readInt() - 1;
            r = readInt();
            x = readInt();
            if (l != 0) {
                upd1(0, 0, n, l, x);
                d[l] += x;
            }
            if (r != n) {
                upd1(0, 0, n, r, -x);
                d[r] -= x;
            }
            upd2(0, 0, n, l, r, x);
        } else if (type == 2) {
            int i, j;
            i = readInt() - 1;
            j = readInt() - 1;
            ll x = get2(0, 0, n, i);
            ll y = get2(0, 0, n, j);
            upd1(0, 0, n, i, y - x);
            if (i + 1 != n) {
                upd1(0, 0, n, i + 1, x - y);
            }
            upd1(0, 0, n, j, x - y);
            if (j + 1 != n) {
                upd1(0, 0, n, j + 1, y - x);
            }
            upd_v2(0, 0, n, i, -x + y);
            upd_v2(0, 0, n, j, -y + x);
        } else {
            int l, r;
            l = readInt() - 1;
            r = readInt();
            if (get1(0, 0, n, l + 1, r) >= 0)
                writeWord("YES\n");
            else
                writeWord("NO\n");
        }
    }
}

signed main() {
    scan();
    prepare();
    mainloop();
    return 0;
}