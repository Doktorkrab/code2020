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
 
ll n;

 
int solve() {
    if (!(cin >> n))
        return 1;
    vector<int> cnt(10, 1);
    int pos = 0;
    while(1){
    	ll ans = 1;
    	for (int x : cnt)
    		ans *= x;
    	if (ans >= n){
    		string s = "codeforces";
    		for (int i = 0; i < 10; i++){
    			for (int j = 0; j < cnt[i]; j++)
    				cout << s[i];
    		}
			cout << '\n';
    		return 0;
    	}
    	cnt[pos++]++;
    	if (pos == 10)
    		pos = 0;
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