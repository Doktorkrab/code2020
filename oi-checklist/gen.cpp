#include <bits/stdc++.h>


using namespace std;


int main(){
	mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
	int n = rnd() % 5 + 4;
	int m = rnd() % 4 + 1;
	cout << n << ' ' << m << '\n';
	set<pair<int, int>> was;
	for (int i = 0; i < m; i++){
		int l = rnd() % n + 1, r = rnd() % n + 1;
		if (l > r)
			swap(l, r);
		while (was.count({l, r})){
			l = rnd() % n + 1, r = rnd() % n + 1;
			if (l > r)
				swap(l, r);
		}
		was.insert({l, r});
		cout << rnd() % 10 + 1 << ' ' << l << ' ' << r << '\n';
	}
}