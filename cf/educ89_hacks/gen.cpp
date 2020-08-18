#include <bits/stdc++.h>



using namespace std;
int main(){
	mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
	int n = 5e5;
	cout << n << '\n';
	const int MAXC = 1e7 - 2;
	for (int i = 0; i < n; i++)
		cout << rnd() % MAXC + 2 << " \n"[i + 1 == n];
}