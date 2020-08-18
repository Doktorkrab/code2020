#include <bits/stdc++.h>


using namespace std;


int main(){
	mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
	cout << "1\n";
	int n = rnd() % 10 + 4;
	int m = rnd() % 4 + 1;
	cout << n << ' ' << m << '\n';
	for (int i = 0; i < m; i++)
		cout << rnd() % 5 + 1 << ' ' << rnd() % 5 + 1 << '\n';
}