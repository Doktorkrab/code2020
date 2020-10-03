#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <ctime>
#include <bitset>
#include <complex>

using namespace std;
int64_t n;
const int MAXN = 2e7 + 5;
bool aa[MAXN];
bool aaa[MAXN];
inline void init(){

}
inline bool check(int64_t x){
    if (x == 1)
        return 0;
    for (int64_t a = 2; a * a <= x; a++)
        if (x % a == 0)
            return 0;
    // cerr < x
    return 1;
}
inline void solve(){
    int64_t n1 = n * n;

    for (int64_t i = 2; i <= n; i++){
        if (aa[i])
            continue;
        for (int64_t j = i * i; j <= n; j += i)
            aa[i] = 1;
        for (int64_t j = max((int64_t)2 * i, (n1 + i - 1) / i * i);j <= n1 + n; j += i)
            aaa[j - n1] = 1;
    }
    // for (int i = 0; i < )
    int ans = 0;
    for (int i = 0; i <= n; i++){
        // cerr << aaa[i] << ' ';
        ans += !aaa[i];
    }
    // cerr << '\n';
    cout << ans - (n == 1) << '\n';
}


int main(){
	#ifdef LOCAL
		freopen("D.in", "r", stdin);
		freopen("D.out", "w", stdout);
	#endif
	
    ios::sync_with_stdio(0);
    while (cin >> n)
        solve();

}
