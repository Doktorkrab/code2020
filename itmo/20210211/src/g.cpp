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

int n;

bool check(const string& x) {
    int mod = 0;
    for (char c : x)
        mod = ((mod * 10 % 7) + (c - '0')) % 7;
    if (mod == 0) {
//        cout << x << '\n';
        return true;
    }
    return false;
}

int solve() {
    string x;
    cin >> x;
    x.erase(find(ALL(x), '1'));
    x.erase(find(ALL(x), '6'));
    x.erase(find(ALL(x), '8'));
    x.erase(find(ALL(x), '9'));
    x = "1689" + x;
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    while (true){
        shuffle(x.begin(), x.begin() + 4, rnd);
        for (int i = 0; i < 1000; i++){
            shuffle(x.begin() + 4, x.end(), rnd);
            if (check(x)){
                cout << x << '\n';
                return 1;
            }
        }
    }
    return 1;
}

signed main() {
#ifdef LOCAL
    freopen("g.in", "r", stdin);
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
