#ifdef LOCAL
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#else
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#endif
#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
#include <immintrin.h>

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

int n, m;
const int MAXN = 2e5 + 7;
unsigned arr[MAXN];
int a, b, k;
void add() {
    int i;
    for (i = 0; i + 8 <= k; i += 8) {
        __m256i cur_block_a = _mm256_lddqu_si256(reinterpret_cast<const __m256i *>(arr + a + i));
        __m256i cur_block_b = _mm256_lddqu_si256(reinterpret_cast<const __m256i *>(arr + b + i));
        _mm256_storeu_si256(reinterpret_cast<__m256i*>(arr + b + i), _mm256_add_epi32(cur_block_a, cur_block_b));
    }
    for (; i < k; i++) {
        arr[i + b] += arr[i + a];
    }
}


int solve() {
    n = readInt();
    m = readInt();
    for (int i = 0; i < n; i++)
        arr[i] = readInt<unsigned >();
    for (int i = 0; i < m; i++){
        a = readInt() - 1;
        b = readInt() - 1;
        k = readInt();
        add();
    }
    for (int i = 0; i < n; i++)
        writeInt<unsigned >(arr[i], ' ');
    writeChar('\n');
    return 1;
}

signed main() {
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
