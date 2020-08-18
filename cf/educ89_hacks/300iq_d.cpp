#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define sz(X) (int)(X).size()
#define forn(i, n) for (int i = 0; i < int(n); i++)
#define fornr(i, n) for (int i = int(n) - 1; i >= 0; i--)
#define forab(i, a, b) for(int i = int(a); i < int(b); i++)
#define all(X) X.begin(), X.end()

typedef long long ll;
typedef pair<int, int> pii;
typedef double dbl;
typedef long double ld;
typedef vector<int> vi;
typedef vector<pair<ll, ll>> vpll;

const int N = 1e7;
int d[N + 1];
vector<int> p;

inline void sieve() {
    forab(i, 2, N + 1) {
        if (!d[i]) {
            d[i] = i;
            p.pb(i);
        }
        for (int x : p) {
            if (x > d[i] || x * i > N) break;
            d[i * x] = x;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    sieve();
    int n, x;
    cin >> n;
    vi ans1, ans2;
    while (n--) {
        cin >> x;
        int a = d[x], b = x / d[x];
        while (!(b % d[x])) a *= d[x], b /= d[x];
        if (x / a == 1) ans1.pb(-1), ans2.pb(-1);
        else ans1.pb(a), ans2.pb(b);
    }
    for (int v : ans1) cout << v << " ";
    cout << "\n";
    for (int v : ans2) cout << v << " ";
    cout << "\n";
    return 0;
}