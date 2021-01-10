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

const int MOD = 1e9 + 7;
//#define int ll
inline int mul(int a, int b) {
    return (1LL * a * b) % MOD;
}
//inline double mul(double a, double b){
//    return a * b;
//}

int bin_p(int a, int b) {
    int ret = 1;
    for (; b > 0; b /= 2) {
        if (b & 1)
            ret = mul(ret, a);
        a = mul(a, a);
    }
    return ret;
}

int inverse(int a) {
    return bin_p(a, MOD - 2);
}

//double inverse(double a){
//    return 1.L / a;
//}
vector<int> find_reccurent(const vector<int> &a) {
    int n = SZ(a);
    vector<int> r = {1}, q = {1};
    int d_m = 1;
    int m = -1;
    for (int i = 0; i < n; i++) {
        int d_n = 0;
        for (int j = 0; j < SZ(r); j++) {
            d_n += mul(r[j], a[i - j]);
            d_n %= MOD;
        }
//        cout << d_n << '\n';
        if (d_n == 0) {
            continue;
        } else {
            vector<int> r_prime = r;
            r.resize(max(SZ(r), SZ(q) + i - m));
            for (int &x : q)
                x = mul(x, d_n);
            int t = inverse(d_m);
            for (int &x : q)
                x = mul(x, t);
            for (int j = 0; j < SZ(q); j++)
                r[j + i - m] = (r[j + i - m] + MOD - q[j]) % MOD;
            d_m = d_n;
            q = r_prime;
            m = i;
        }
    }
    r.erase(r.begin());
//    r.pop_back();
    for (int &x : r) {
        x *= -1;
        x = (x + MOD) % MOD;
    }
    return r;
}

vector<vector<int>> get_matrix(int sz) {
    vector<vector<int>> arr(sz, vector<int>(sz));
    int x = 0, y = 0;
    vector<pair<int, int>> shift = {{0,  1},
                                    {1,  0},
                                    {0,  -1},
                                    {-1, 0}};
    int d = 0;
    for (int i = 1; i <= sz * sz; i++) {
        arr[x][y] = i;
        if (i == sz * sz)
            break;
        while (true) {
            auto[sx, sy] = shift[d];
            int nx = x + sx, ny = y + sy;
            if ((0 <= nx && nx < sz && 0 <= ny && ny < sz) && (arr[nx][ny] == 0)) {
                break;
            }
            d = (d + 1) & 3;
        }

        auto[sx, sy] = shift[d];
        x += sx;
        y += sy;
    }
    return arr;
}

int get_ans(const vector<vector<int>> &arr) {
    int ans = 0;
    int n = SZ(arr);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            for (int i1 = i; i1 < n; i1++)
                for (int j1 = j; j1 < n; j1++) {
                    for (int i2 = i; i2 <= i1; i2++)
                        for (int j2 = j; j2 <= j1; j2++)
                            ans = (ans + arr[i2][j2]) % MOD;
                }
        }
    return ans;
}

int n;
int solve() {
    while (!(cin >> n))
        return 1;
    vector<int> kek = {0, 1, 40, 528, 3784, 18393, 68832, 213504, 575200, 1388625, 3070600, 6319056, 12248040, 22566313,
                       39808384, 67627008, 111157632, 177465249, 276085800, 419674000, 624771400, 912707961, 310652633,
                       852827641, 581903570, 550591452, 823450604, 478929702, 611661744, 335031548, 784038302};
//    for (int i = 1; i <= 30; i++) {
////        cerr << "kek\n";
//        kek[i] = get_ans(get_matrix(i));
//    }
//    for (int x : kek)
//        cout << x << ", ";
//    cout << '\n';
    auto ret = find_reccurent(kek);
    kek.resize(1000007);
    for (int i = 31; i < SZ(kek); i++){
        for (int j = 0; j < SZ(ret); j++){
            kek[i] = (kek[i] + mul(kek[i - j - 1], ret[j])) % MOD;
        }
    }
    cout << kek[n] << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("berlecamp.in", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1;
//    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}