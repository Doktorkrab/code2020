#include <bits/stdc++.h>


using namespace std;

int main(){
	mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
	int n = rnd() % 151, k = rnd() % 10;
	cout << "1\n";
	cout << n << ' ' << k << '\n';
}