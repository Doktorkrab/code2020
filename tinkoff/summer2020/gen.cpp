#include <bits/stdc++.h>
#include <chrono>

using namespace std;

int main(){
    mt19937 rnd(chrono::steady_clock::steady_clock::now().time_since_epoch().count());
    int n = rnd() % 1 + 3, m = rnd() % 1 + 3, k = rnd() % 2 + 1;
    cout << n << ' ' << m << ' ' << k << '\n';
    cout << rnd() % n + 1 << ' ' << rnd() % m + 1 << '\n';
    for (int i = 0; i < k; i++){
        cout << rnd() % n + 1 << ' ' << rnd() % m + 1 << ' ' << "RUDL"[rnd() % 4] << '\n';
        for (int x = 0; x < n; x++){
            for (int y = 0; y < m; y++)
                cout << (char)('0' + rnd() % 4);
            cout << '\n';
        }
    }
}
