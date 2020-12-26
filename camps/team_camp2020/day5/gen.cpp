#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5;
const int MAXT = 5;
char fld[MAXN][MAXN];
int main(){
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int n = MAXN;
    int t = MAXT;
    cout << n << ' ' << t << '\n';
    int cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (cnt < 300)
                fld[i][j] = "..#"[rnd() % 3];
            else
                fld[i][j] = '.';
            cnt += fld[i][j] == '#';
        }
    for (int i = 0; i < t; i++)
        cout << "UDRL"[rnd() % 4];
    cout << '\n';
    fld[rnd()  % n][rnd() % n] = '@';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << fld[i][j];
        cout << '\n';
    }
}