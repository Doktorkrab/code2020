#include <bits/stdc++.h>


using namespace std;


int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int n = rnd() % 5 + 2;
    int m = rnd() % 5 + 2;
    int k = rnd() % 100 + 1;
    int s = rnd() % 100 + k;
    cout << k << ' ' << s << '\n' << n << ' ' << m << '\n';
    vector<string> fld(n, string(m, 'a'));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            fld[i][j] = "...##$"[rnd() % 6];
    fld[rnd() % n][rnd() % m] = '@';
    while (true){
        int x = rnd() % n;
        int y = rnd() % m;
        if (fld[x][y] == '@')
            continue;
        fld[x][y] = 'E';
        break;
    }
    for (int i = 0; i < n; i++)
        cout << fld[i] << '\n';
}