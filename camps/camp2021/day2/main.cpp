#include <bits/stdc++.h>

using namespace std;
#define SZ(x) (int)((x).size())
#define ALL(x) (x).begin(), (x).end()
#define TMAX(x) numeric_limits<x>::max()

int n;

int solve(){
    if (!(cin >> n))
        return 1;
    return 0;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int tests = 1e9;
//    cin >> tests;
    for (int test = 1; test < tests; test++){
        if (!solve())
            break;
#ifdef LOCAL
        cout << "-------\n";
#endif
    }
}