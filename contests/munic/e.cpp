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
 
int n, k;
vector<int> have;
void rec(int ost){

    if (SZ(have) == k) {
        if (ost == 0) {
            cout << have[0];
            for (int i = 1; i < k; i++) {
                if (have[i] >= 0)
                    cout << '+';
                cout << have[i];
            }
            cout << '\n';
        }
        return;
    }

    if (!SZ(have))
        for (int i = -100; i <= 100; i++){
            have.push_back(i);
            rec(ost - i);
            have.pop_back();
        }
    else {
        for (int i = have.back() - 1; i <= have.back() + 1; i++){
            have.push_back(i);
            rec(ost - i);
            have.pop_back();
        }
    }
}
 
int solve() {
    if (!(cin >> n >> k))
        return 1;
//    assert(n != 1);
    rec(n);
    return 0;
}
 
signed main() {
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
