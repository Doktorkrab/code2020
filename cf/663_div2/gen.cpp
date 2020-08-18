#include<bits/stdc++.h>
using namespace std;


int main(){
	mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
	int n = rnd() % 3 + 1;
	int m = rnd() % 2 + n;
	cout << n << ' ' << m << '\n';
	for (int i = 0; i < n; i++){
		for (int i = 0; i < m; i++)
			cout << rnd() % 2;
		cout << '\n';
	}
}