#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    //freopen("bankcraft.in", "r", stdin);
    //freopen("bankcraft.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n = 8;
    vector<string> s(n);
    for (int i = 0; i < n; i++)
        cin >> s[i];

    auto ok = [&](int x, int y) {
        return 0 <= x && x < n && 0 <= y && y < n;
    };

    int px = 0, py = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (s[i][j] == 'N') {
                px = i, py = j;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int d = (i - px) * (i - px) + (j - py) * (j - py);
            if (d == 5)
                s[i][j] = 'X';
        }
    }
    for (int i = 0; i < n; i++)
        cout << s[i] << "\n";
}