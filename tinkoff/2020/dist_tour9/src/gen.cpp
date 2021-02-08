#include <bits/stdc++.h>


using namespace std;

int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int t = 1;
    cout << t << '\n';
    for (int x = 0; x < t; x++) {
        int n = rnd() % 5 + 1;
        cout << n << '\n';
        for (int i = 1; i < n; i++)
            cout << i + 1 << " " << rnd() % i + 1 << '\n';
        for (int i = 0; i < n; i++)
            cout << (int) (rnd() % 3) - 1 << " \n"[i + 1 == n];
    }
}