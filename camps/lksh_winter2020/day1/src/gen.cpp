#include <bits/stdc++.h>

using namespace std;

int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int t = rnd() % 5 + 1;
    cout << t << '\n';
    for (int i = 0; i < t; i++){
        int len = rnd() % 100 + 1;
        for (int j = 0; j < len; j++)
            cout << (char)(33 + rnd() % (126 - 33));
        cout << '\n';
    }
}