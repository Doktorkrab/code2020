#include <bits/stdc++.h>


using namespace std;

int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int n = rnd() % 5 + 1;
    int q = rnd() % 1 + 1;
    const int MAXC = 10;
    cout << n << ' ' << q << '\n';
    for (int i = 0; i < n; i++)
        cout << rnd() % MAXC + 1 << ' ' << rnd() % MAXC + 1 << '\n';
    for (int i = 0; i < q; i++){
        int x1 = rnd() % MAXC + 1;
        int y1 = rnd() % MAXC + 1;
        int d = rnd() % MAXC + 1;
        cout << "2 " << x1 << ' ' << y1 << ' ' << x1 + d << ' ' << y1 + d << '\n';
    }
}