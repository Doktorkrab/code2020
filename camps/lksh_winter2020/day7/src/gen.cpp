#include <bits/stdc++.h>

using namespace std;


int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

    int n = 50000;
    int m = 1;
    cout << n << ' ';
    for (int i = 0; i <= n; i++)
        cout << rnd() % 7 << " \n"[i == n];
    cout << m << " ";
    for (int i = 0; i <= m; i++)
        if (i == 0)
            cout << rnd() % 6 + 1 << " \n"[i == m];
        else
            cout << rnd() % 7 << " \n"[i == m];
}