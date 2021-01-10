#include<bits/stdc++.h>

using namespace std;
#define int long long
#define ii pair <int, int>
#define app push_back
#define all(a) a.begin(), a.end()
#define bp __builtin_popcountll
#define ll long long
#define mp make_pair
#define x first
#define y second
#define Time (double)clock()/CLOCKS_PER_SEC
#define debug(x) std::cerr << #x << ": " << x << '\n';
#define FOR(i, n) for (int i = 0; i < n; ++i)
#define pb push_back
#define trav(a, x) for (auto& a : x)
using vi = vector<int>;

template<typename T>
std::ostream &operator<<(std::ostream &output, const pair<T, T> &data) {
    output << "(" << data.x << "," << data.y << ")";
    return output;
}

template<typename T>
std::ostream &operator<<(std::ostream &output, const std::vector<T> &data) {
    for (const T &x : data)
        output << x << " ";
    return output;
}
//ll div_up(ll a, ll b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up
//ll div_down(ll a, ll b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down 
#define tcT template<class T
#define tcTU tcT, class U
tcT> using V = vector<T>;

tcT> void re(V<T> &x) {
    trav(a, x)cin >> a;
}

tcT> bool ckmin(T &a, const T &b) {
    return b < a ? a = b, 1 : 0;
} // set a = min(a,b)
tcT> bool ckmax(T &a, const T &b) {
    return a < b ? a = b, 1 : 0;
}

//const int N = 1e8+7;
//int phi[N];
//int primes[5761456];

int phi_slow(int n) {
    int result = n;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    if (n > 1)
        result -= result / n;
    return result;
}

int t(int n) {
    assert(n >= 0);
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return phi_slow(n) + 1;
}

signed main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#else
#define endl '\n'
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("ans", "w", stdout);
#endif

    /*
    int pnt = 0;
    phi[1] = 1;
    for (int i = 2; i < N; i++) {
        if (phi[i] == 0) {
            primes[pnt++] = i;
            phi[i] = i - 1;
        }
        for (int j = 0; j < pnt && i * primes[j] < N; j++) {
            if (i % primes[j] == 0) {
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
            phi[i * primes[j]] = phi[i] * (primes[j] - 1);
        }
    }
    */

    vi A = {1894607624, 1927505134, 1861486949, 2052221263, 1953703270, 1772249212, 1704106159, 98304, 1829198849};

    sort(all(A));

    FOR (i, 4) {
        A[i + 5] ^= t(A[i + 1] - A[0]) >> 7;
    }

    int z = max(t(A[0]) - 1, A[0] + 1 - t(A[0]));

    int len = A.size();
    int s = z % (int) len;
    vi na;
    FOR (i, len) {
        na.app(A[(s + i) % len]);
    }
    A = na;

    FOR (i, z) {
        int l = A[0];
        A.erase(A.begin());
        A.app(l);
    }

    //for i in range(z): A = A[1:] + A[:1]
    A.insert(A.begin() + 1, z);

    for (int x = 8; x < 1000 * 1000 * 10; ++x) {
        int y = A[x / 4] >> (18 - 6 * (x % 4)) & 63;
        if (y) {

            if (y < 60) {
                cout << (char) (31 + y);
            } else {
                assert(y - 60 < A.size());
                cout << A[y - 60];
            }

            //print( chr(31+y) if y<60 else A[y-60], end='')
        } else {
            break;
        }
    }

    /*
for x in range(8,10**7):
    y = A[x//4]>>(18-6*(x%4))&63
    if y: print( chr(31+y) if y<60 else A[y-60], end='')
    else: break
    */
    return 0;
}







































