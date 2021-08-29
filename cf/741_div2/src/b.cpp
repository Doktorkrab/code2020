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

int k;
string n;

const int MAXC = 1e4 + 7;
bool is_p[MAXC];
void find_primes(){
    fill(is_p, is_p + MAXC, true);
    is_p[0] = is_p[1] = false;
    for (ll i = 2; i < MAXC; i++){
        if (!is_p[i])
            continue;
        for (ll j = i * i; j < MAXC; j += i)
            is_p[j] = false;
    }
}
 
int solve() {
    if (!(cin >> k >> n))
        return 1;
    int ans = TMAX(int);
    string best;
    for (int i = 1; i <= 2000; i++){
        if (is_p[i])
            continue;
        vector<int> have1(10);
        string t = to_string(i);
        int sum = SZ(t);
        int pnt = 0;
        for (char c : n){
            if (t[pnt] == c){
                pnt++;
            }
            if (pnt == SZ(t))
                break;
        }
        if (pnt == SZ(t) && sum < ans){
            ans = sum;
            best = t;
        }
    }
    cout << ans << '\n';
    cout << best << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
#endif
    find_primes();
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}
