#include <bits/stdc++.h>


using namespace std;


int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int n = 5;
    int m = rnd() % (n / 2) + 1;
    int k = 2;
    cout << n << ' ' << m << ' ' << k << "\n";
    for (int i = 0; i < n; i++)
        cout << rnd() % 10 + 1 << " \n"[i + 1 == n];
}