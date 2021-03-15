#include <bits/stdc++.h>


using namespace std;

int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int t = 1;
    cout << t << '\n';
    for (int k = 0; k < t; k++) {
        int n = rnd() % 7 + 1;
        cout << n << '\n';
        for (int i = 1; i < n; i++){
            cout << i + 1 << ' ' << rnd() % i + 1 << '\n';
        }
    }

}