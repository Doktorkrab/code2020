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
const int MAXN = 2e5 + 7;
pair<char, int> arr[MAXN];

bool is_correct() {
    set<int> have;
    for (int i = 0; i < 2 * n; i++) {
        if (arr[i].first == '+')
            have.insert(arr[i].second);
        if (arr[i].first == '-') {
            if (!SZ(have) || (*have.begin()) != arr[i].second)
                return false;
            have.erase(have.begin());
        }
    }
    return true;
}

int solve() {
    if (!(cin >> n))
        return 1;
    vector<int> pluses_have;
    for (int i = 0; i < 2 * n; i++){
        char x;
        cin >> x;
        arr[i].first = x;
        if (x == '+')
            pluses_have.push_back(i);
        if (x == '-'){
            int y;
            cin >> y;
            arr[i].second = y;
            if (!SZ(pluses_have)){
                cout << "NO\n";
                return 0;
            }
            arr[pluses_have.back()].second = y;
            pluses_have.pop_back();
        }
    }
    if (SZ(pluses_have) == 0 && is_correct()) {
        cout << "YES\n";
        for (int i = 0; i < 2 * n; i++)
            if (arr[i].first == '+')
                cout << arr[i].second << ' ';
        cout << '\n';
    }
    else {
        cout << "NO\n";
    }
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
