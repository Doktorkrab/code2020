#include <bits/stdc++.h>

using namespace  std;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

void gen_b_plus(){
    int t = rnd() % 3 + 1;
    cout << t << '\n';
    for (int tt = 0; tt < t; tt++){
        int n = rnd() % 16 + 1;
        for (int i = 0; i <n; i++)
            cout << "+-"[rnd() % 2];
        cout << " ";
        for (int i = 0; i < n; i++)
            cout << "+";
        cout << '\n';
    }
}

void gen_c(){
    int n = rnd() % 5 + 1;
    cout << n << '\n';
    for (int i = 0; i < n; i++){
        int x = rnd() % (n) + 1;
        if (x - 1 == i)
            x = -1;
        cout << x << '\n';
    }
}

int main(){
//    gen_b_plus();
    gen_c();
}