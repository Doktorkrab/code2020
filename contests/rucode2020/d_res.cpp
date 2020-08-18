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

int n;
const int MAXN = 1e6 + 5;
using ll = int64_t;
#define int ll
int primes[MAXN], cnt = 0;
int d[MAXN];

inline void init(){
	memset(primes, 0, MAXN * sizeof(int));
	fill(d, d + MAXN, -1);
	cnt = 0;
}

inline void init1(){
	init();
	for (int i = 2; i < MAXN; i++){
		// cerr << d[i] << ' ';
		if (d[i] == -1){
			d[i] = cnt;
			primes[cnt++] = i;
		}
		// cerr << i << '\n';
		for (int j = 0; j <= d[i] && i * primes[j] < MAXN; j++){
			// cerr << i * primes[j] << ' ' << MAXN << '\n';
			d[i * primes[j]] = j;
		
		}
	}
	// cerr << '\n';
}
void solve(){
	vector<int> have;
	for (int i = 0; i < cnt; i++){
		cout << "? " << primes[i] << endl;
		int x;
		cin >> x;
		if (x != 1)
			have.push_back(x);
	}
	if (have.empty()){
		cout << "! 1" << endl;
		return;
	}
	int ans = 1;
	for (int i : have){
		int now = i * i;
		while (now <= 1000000)
			now *= i;
		if (now > 1e9)
			now /= i;
		cout << "? " << now << endl;
		int x;
		cin >> x;
		ans *= x;
	}
	cout << "! " << ans << '\n';
}

int32_t main(){
	#ifdef LOCAL
		// freopen("E.in", "r", stdin);
		// freopen("E.out", "w", stdout);
	#endif
	
    // ios::sync_with_stdio(0);
    // cin.tie(0), cout.tie(0);
    init1();
    // while (cin >> l >> r)
        solve();

}