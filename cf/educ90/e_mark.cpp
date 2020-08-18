#include <bits/stdc++.h>

using namespace std;

#define ALL(v) v.begin(), v.end()
#define speed cin.tie(0); cout.tie(0); iostream::sync_with_stdio(false)

int main() {
//    speed;

    //KTO PROCHITAL TOT LOH, PIDOR I NE APNET FIOLA
    const int FATE = 15'400'000;
    vector<int> digitsum(FATE);
    int now_s = 0;
    for (int i = 1; i < FATE; ++i) {
        now_s++;
        int npow = 10;
        while (i % npow == 0) {
            now_s -= 9;
            npow *= 10;
        }
        digitsum[i] = now_s;
    }
    vector<map<int, int>> digit_sums(10);
    for (int i = 0; i < 10; ++i) {
        for (int j = 1; j <= 150; ++j) {
            digit_sums[i][j] = -1;
        }
    }

    for (int i = 0; i < FATE - 2; ++i) {
        int now = 0;
        for (int j = 0; j < 10; ++j) {
            now += digitsum[i + j];
            if (now >= 151) continue;
            if (digit_sums[j][now] == -1) {
                digit_sums[j][now] = i;
            }

        }
    }

    int t;
    cin >> t;
    for (int _ = 0; _ < t; ++_) {
        int n, k;
        cin >> n >> k;
        if (digit_sums[k][n] != -1) {
            cout << digit_sums[k][n] << '\n';
            continue;
        }
        if (k == 0) {
            int amount_9 = n / 9;
            int left_d = n % 9;
            if (left_d != 0) {
                cout << left_d;
            }
            for (int i = 0; i < amount_9; ++i) {
                cout << '9';
            }
            cout << '\n';
            continue;
        }
        if (k == 1) {
            if (n < 20) {
                cout << -1 << '\n';
                continue;
            }
            if (n % 2 == 1) {
                int nn = (n + 1) / 2;
                int amount_9 = nn / 9;
                int left_d = nn % 9;
                if (left_d != 0) {
                    cout << left_d;
                }
                for (int i = 0; i < amount_9 - 1; ++i) {
                    cout << '9';
                }
                cout << '8' << '\n';
                continue;
            } else {
                int nn = (n + 8) / 2;
                nn -= 17;
                int amount_9 = nn / 9;
                int left_d = nn % 9;
                if (left_d != 0) {
                    cout << left_d;
                }
                for (int i = 0; i < amount_9; ++i) {
                    cout << '9';
                }
                cout << "89\n";
                continue;
            }
        }
        cout << -1 << '\n';
    }
}