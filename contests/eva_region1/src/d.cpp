#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;


#define SZ(x) (int)((x).size())
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()

#define TMAX(type) numeric_limits<type>::max()
#define TMIN(type) numeric_limits<type>::min()
#ifdef LOCAL
#define ass(X) assert(X)
#else
#define ass(X) {}
#endif

int n;
map<vector<int>, int> mem[3];
map<vector<int>, int> change[3];

bool rec(vector<int> state, int cur) {
    int sum = 0;
    for (int i = 0; i < 3; i++)
        sum += state[cur * 3 + i];
    if (!sum) {
        change[cur][state] = -1;
        return false;
    }
    if (mem[cur].count(state))
        return mem[cur][state];
    bool now = false;
    change[cur][state] = -1;
    for (int i = 0; i < 3; i++) {
        if (state[cur * 3 + i]) {
            state[cur * 3 + i]--;
            now |= !rec(state, i);
            state[cur * 3 + i]++;
        }
        if (now) {
            change[cur][state] = i;
            break;
        }
    }
//    for (int i = 0; i < 9; i++)
//        cout << state[i] << ' ';
//    cout << ": " << now << '\n';
    return mem[cur][state] = now;
}

int turn = 0;

void recover(int cur, vector<int> state) {
    assert(change[cur].count(state));
    if (change[cur][state] == -1) {
        cout << "AB"[turn] << ": Lose\n";
        return;
    }
    cout << "AB"[turn] << ": " << (char) ('a' + cur) << "..." << (char) ('a' + change[cur][state]) << endl;
    int ind = cur * 3 + change[cur][state];
    int nxt = change[cur][state];
    state[ind]--;
    turn ^= 1;
    recover(nxt, state);

}

int solve() {
    if (!(cin >> n))
        return 1;
    vector<int> state(9);
    string s;
    for (int i = 0; i < n; i++) {
        cin >> s;
        int st = s[0] - 'a';
        int ft = s.back() - 'a';
        state[3 * st + ft]++;
    }
    if (rec(state, 0))
        recover(0, state);
    else if (rec(state, 1))
        recover(1, state);
    else if (rec(state, 2))
        recover(2, state);
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("d.in", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
//    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}
