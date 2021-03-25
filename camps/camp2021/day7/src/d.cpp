//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")
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

int n;

bool is_digit(const string& s){
    if (SZ(s) == 1)
        return true;
    if (s[0] == '0')
        return false;
    return true;
}
const int MAXMEM = 5;
const int MAXN = 1e5;
const int powers10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};
vector<int> values[MAXMEM + 1][MAXN];

vector<int> get_values(int len, int x){
    if (len <= MAXMEM && SZ(values[len][x]))
        return values[len][x];
    vector<int> cur;
    if (x >= powers10[len - 1] || len == 1)
        cur.push_back(x);
    for (int i = 1; i < len; i++){
        int lft = x / powers10[len - i];
        int rgt = x % powers10[len - i];
        vector<int> calc_l = get_values(i, lft);
        vector<int> calc_r = get_values(len - i, rgt);
        for (int a : calc_l)
            for (int b : calc_r){
                cur.push_back(a + b);
                cur.push_back(a * b);
                if (a - b >= 0)
                    cur.push_back(a - b);
                if (-a + b >= 0)
                    cur.push_back(-a + b);
                if (b != 0 && a % b == 0)
                    cur.push_back(a / b);
            }
    }
    sort(ALL(cur));
    cur.resize(unique(ALL(cur)) - cur.begin());
    if (len <= MAXMEM)
        values[len][x] = cur;
    return cur;
}

void print_ans(int len, int x, int need){
    if (x >= powers10[len - 1] || len == 1){
        if (x == need){
            writeInt(x);
            return;
        }
        if (x == -need){
            writeInt(x);
            return;
        }
    }
    for (int i = 1; i < len; i++){
        int lft = x / powers10[len - i];
        int rgt = x % powers10[len - i];
        vector<int> val_l = get_values(i, lft);
        vector<int> val_r = get_values(len - i, rgt);
        for (int a : val_l)
            for (int b : val_r){
                if (a + b == need){
                    writeChar('(');
                    print_ans(i, lft, a);
                    writeWord(")+(");
                    print_ans(len - i, rgt, b);
                    writeChar(')');
                    return;
                }
                if (a * b == need){
                    writeChar('(');
                    print_ans(i, lft, a);
                    writeWord(")*(");
                    print_ans(len - i, rgt, b);
                    writeChar(')');
                    return;
                }
                if (a - b == need){
                    writeChar('(');
                    print_ans(i, lft, a);
                    writeWord(")-(");
                    print_ans(len - i, rgt, b);
                    writeChar(')');
                    return;
                }
                if (-a + b == need){
                    writeChar('-');
                    writeChar('(');
                    print_ans(i, lft, a);
                    writeWord(")+(");
                    print_ans(len - i, rgt, b);
                    writeChar(')');
                    return;
                }
                if (b != 0 && a % b == 0 && a / b == need){
                    writeChar('(');
                    print_ans(i, lft, a);
                    writeWord(")/(");
                    print_ans(len - i, rgt, b);
                    writeChar(')');
                    return;
                }
            }
    }
    writeWord("No solution");
}

int solve() {
    clock_t start = clock();
    int i = 0;
    for (; i <= 999999; i++) {
//        writeInt(i);
//        writeWord(": ");
        print_ans(6, i, 100);
        writeChar('\n');
    }
    return 1;
}

signed main() {
#ifdef LOCAL
    freopen("d.in", "r", stdin);
    freopen("d.out", "w", stdout);
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