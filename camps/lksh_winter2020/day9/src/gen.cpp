#include <bits/stdc++.h>

using namespace std;


int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int n = rnd() % 3 + 1;
    auto get_rnd = [&](int a, int b){
        int need = rnd() % (b - a + 1);
        return a + need;
    };
    cout << n << '\n';
    for (int i = 0; i < n; i++)
        cout << get_rnd(-10, 10) << ' ' << get_rnd(-10, 10) << '\n';
}