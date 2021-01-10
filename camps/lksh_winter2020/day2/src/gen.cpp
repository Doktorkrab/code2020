#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5;
const int MAXC = 1e4;

int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int carry = MAXN;
    for (; carry > 1; ){
        int n = rnd() % (carry - 1) + 2;
        cout << n << '\n';
        carry -= n;
        for (int i = 0; i < n; i++)
            cout << rnd() % MAXC + 1 << " \n"[i + 1 == n];
        for (int i = 1; i < n; i++)
            cout << rnd() % i + 1 << " \n"[i + 1 == n];
    }
}