#include <bits/stdc++.h>


using namespace std;


int main(){
	mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
	int n = rnd() % 5 + 4;
	int m = rnd() % 4 + 1;
	cout << n << ' ' << m << '\n';
	for (int i = 0; i < n; i++)
		cout << rnd() % 10;
	cout << '\n';
	for (int i = 0; i < m; i++)
		cout << rnd() % n + 1 << ' ' << rnd() % 10 << '\n';
}