#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
//#define int ll
#define SZ(X) (int)(X).size()
#define ALL(X) (X).begin(), (X).end()
#define RALL(X) (X).rbegin(), (X).rend()
#define TMAX(X) numeric_limits<X>::max();
#define TMIN(X) numeric_limits<X>::min();

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

const int MOD = 1e9 + 7;
int add(int a, int b){
    return ((a + b) % MOD + MOD) % MOD;
}

int mul(int a, int b){
    return (1LL * a * b) % MOD;
}


int a, b;

int solve(){
    if (!(cin >> a >> b))
        return 1;
    cout << a * b << '\n';
    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int tests = 1;
    cin >> tests;
    for (int test = 1; test <= tests; test++){
        if (solve())
            break;
#ifdef LOCAL
        cout << "-----------\n";
#endif
    }
    return 0;
}
