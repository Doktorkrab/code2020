#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000;
int arr[MAXN];
int main(){
	arr[0] = arr[1] = 0;
	for (int i = 2; i < MAXN; i++){
		if (arr[i - 1] == 0){
			arr[i] = 1;
			continue;
		}
		for (int f = 2; f <= i; f++){
			if (i % f == 0 && f % 2 == 1 && arr[i / f] == 0){
				arr[i] = 1;
				break;
			}
		}
	}
	for (int i = 1; i < MAXN; i++)
		if (arr[i] == 0 && i % 4 == 0)
			cout << i << '\n';
}