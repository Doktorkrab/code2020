#include <bits/stdc++.h>


using namespace std;


int main(){
	int n;
	cin >> n;
	vector<int> a(n);
	for (int& i : a)
		cin >> i;
	vector<int> d1(n), d2(n);
	for (int i = 0; i < n; i++)
		cin >> d1[i];
	for (int i = 0; i < n; i++)
		cin >> d2[i];
	for (int i = 0; i < n; i++){
		if (d1[i] == -1 && d2[i] == -1)
			continue;
		assert(d1[i] > 1 && d2[i] > 1);
		assert(gcd(d1[i] + d2[i], a[i]) == 1);
	}

	vector<int> dd1(n), dd2(n);
	for (int i = 0; i < n; i++)
		cin >> dd1[i];
	for (int i = 0; i < n; i++)
		cin >> dd2[i];
	for (int i = 0; i < n; i++){
		if (dd1[i] == -1 && dd2[i] == -1){
			assert(d1[i] == -1);
			continue;
		}

		assert(dd1[i] > 1 && dd2[i] > 1);
		assert(d1[i] != -1);
		assert(gcd(dd1[i] + dd2[i], a[i]) == 1);
	}
}