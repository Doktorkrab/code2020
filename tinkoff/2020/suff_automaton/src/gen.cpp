#include <bits/stdc++.h>

using namespace std;


int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int n = rnd() % 7 + 1;
    for (int i = 0; i < n; i++){
        int len = rnd() % 8 + 1;
        for (int x = 0; x < len; x++)
            cout << (char)(rnd() % 26 + 'a');
    }
}