#include <bits/stdc++.h>

using namespace std;

#define MAX_N 500

// modify the following functions
// you can define global variables and functions

struct State{
    int turn;
    int robber;
    int cop;
};
int needToWin[2][MAX_N][MAX_N]; // 0 - cop, 1 - robber
int nxt[MAX_N][MAX_N];
int start(int n, bool g[MAX_N][MAX_N]) {
    for (int i = 0; i < n; i++){
        int have = count(g[i], g[i] + n, 1);
        for (int j = 0; j < n; j++){
            if (i != j){
                needToWin[0][j][i] = 1;
                needToWin[1][j][i] = have;
            }
        }
    }
    deque<State> q;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < 2; j++)
            q.push_back({j, i, i});
    int cnt = 0;
    while (!q.empty()){
        auto [t, r, c] = q.front();
        q.pop_front();
        cnt++;
        if (t == 0){
            for (int i = 0; i < n; i++){
                if (g[r][i] && needToWin[1][c][i]){
                    needToWin[1][c][i]--;
                    if (needToWin[1][c][i] == 0){
                        q.push_back({1, i, c});
                    }
                }
            }
        }
        else {
            for (int i = 0; i < n; i++){
                if ((c == i || g[c][i]) && needToWin[0][i][r]){
                    needToWin[0][i][r] = 0;
                    nxt[i][r] = c;
                    q.push_back({0, r, i});
                }
            }
        }
        // for (int k = 0; k < 2; k++){
        //     for (int i = 0; i < n; i++)
        //         for (int j = 0; j < n; j++)
        //             cout << needToWin[k][i][j] << " \n"[j + 1 == n];
        //     cout << '\n';
        // }
        // cout << '\n';
    }
    // for (int k = 0; k < 2; k++){
    //     for (int i = 0; i < n; i++)
    //         for (int j = 0; j < n; j++)
    //             cout << needToWin[k][i][j] << " \n"[j + 1 == n];
    //     cout << '\n';
    // }
    // cout << cnt << '\n';
    if (cnt == 2 * n * n)
        return 0;
    return -1;
}

int cop = 0;
int nextMove(int R) {
    return cop = nxt[cop][R];
}

// don't modify the main function
int main() {
    int N;
    cin >> N;
    bool A[MAX_N][MAX_N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> A[i][j];
        }
    }
    int P = start(N,A);
    cout << P << endl;
    int R;
    cin >> R;
    while (true) {
        if (P == R) break;
        P = nextMove(R);
        cout << P << endl;
        if (P == R) break;
        cin >> R;
    }
}
