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

const int MAXN = 14;
int n;
pair<int, char> have[MAXN];
vector<int> now[MAXN];
bool type[5];
int sz[5];

bool rec_win(int pos) {
    if (pos == n) {
        return true;
    }
    for (int i = 0; i < 5; i++) {
        if (i == 4) {
            if (SZ(now[i]) == 0 || (SZ(now[i]) == 1 && have[pos] == have[now[i][0]])) {
                now[i].push_back(pos);
                bool ans = rec_win(pos + 1);
                now[i].pop_back();
                if (ans)
                    return true;
            }
            continue;
        }
        if (SZ(now[i]) == 0) {
            now[i].push_back(pos);
            if (rec_win(pos + 1))
                return true;
            now[i].pop_back();
        }
        if (SZ(now[i]) == 1) {
            if (have[pos] == have[now[i].back()]) {
                type[i] = false;
                now[i].push_back(pos);
                if (rec_win(pos + 1))
                    return true;
                now[i].pop_back();
            } else if (have[pos].second == have[now[i].back()].second &&
                       have[now[i].back()].first + 1 == have[pos].first) {
                type[i] = true;
                now[i].push_back(pos);
                if (rec_win(pos + 1))
                    return true;
                now[i].pop_back();
            }
        }
        if (SZ(now[i]) == 2) {
            if (!type[i] && have[now[i].back()] == have[pos]) {
                now[i].push_back(pos);
                if (rec_win(pos + 1))
                    return true;
                now[i].pop_back();
            }
            if (type[i] && have[pos].second == have[now[i].back()].second &&
                have[now[i].back()].first + 1 == have[pos].first) {
                now[i].push_back(pos);
                if (rec_win(pos + 1))
                    return true;
                now[i].pop_back();
            }
        }
    }
    return false;
}

bool rec_triple(int pos) {
    if (pos == n) {
        return SZ(now[0]) == 2 && sz[0] == 3;
    }
    for (int i = 0; i < 5; i++) {
        if (i == 4) {
            if (SZ(now[i]) == 0 || (SZ(now[i]) == 1 && have[pos] == have[now[i][0]])) {
                now[i].push_back(pos);
                bool ans = rec_triple(pos + 1);
                now[i].pop_back();
                if (ans)
                    return true;
            }
            continue;
        }
        if (i == 0) {
            if (sz[i] == 3)
                continue;
            sz[i]++;
            if (rec_triple(pos + 1))
                return true;
            if (!SZ(now[i]) || (SZ(now[i]) && ((have[pos].second == have[now[i].back()].second &&
                                                have[now[i].back()].first + 1 == have[pos].first) ||
                                               have[pos] == have[now[i].back()])) ||
                (have[pos].second == have[now[i].back()].second &&
                 have[now[i].back()].first + 2 == have[pos].first)) {
                now[i].push_back(pos);
                if (rec_triple(pos + 1))
                    return true;
                now[i].pop_back();
            }
            sz[i]--;
            continue;
        }
        if (SZ(now[i]) == 0) {
            now[i].push_back(pos);
            if (rec_triple(pos + 1))
                return true;
            now[i].pop_back();
        }
        if (SZ(now[i]) == 1) {
            if (have[pos] == have[now[i].back()]) {
                type[i] = false;
                now[i].push_back(pos);
                if (rec_triple(pos + 1))
                    return true;
                now[i].pop_back();
            } else if (have[pos].second == have[now[i].back()].second &&
                       have[now[i].back()].first + 1 == have[pos].first) {
                type[i] = true;
                now[i].push_back(pos);
                if (rec_triple(pos + 1))
                    return true;
                now[i].pop_back();
            }
        }
        if (SZ(now[i]) == 2) {
            if (!type[i] && have[now[i].back()] == have[pos]) {
                now[i].push_back(pos);
                if (rec_triple(pos + 1))
                    return true;
                now[i].pop_back();
            }
            if (type[i] && have[pos].second == have[now[i].back()].second &&
                have[now[i].back()].first + 1 == have[pos].first) {
                now[i].push_back(pos);
                if (rec_triple(pos + 1))
                    return true;
                now[i].pop_back();
            }
        }
    }
    return false;
}

bool rec_pair(int pos) {
    if (pos == n) {
        return true;
    }
    for (int i = 0; i < 5; i++) {
        if (i == 4) {
            if (SZ(now[i]) == 0 || SZ(now[i]) == 1) {
                now[i].push_back(pos);
                bool ans = rec_pair(pos + 1);
                now[i].pop_back();
                if (ans)
                    return true;
            }
            continue;
        }
        if (SZ(now[i]) == 0) {
            now[i].push_back(pos);
            if (rec_pair(pos + 1))
                return true;
            now[i].pop_back();
        }
        if (SZ(now[i]) == 1) {
            if (have[pos] == have[now[i].back()]) {
                type[i] = false;
                now[i].push_back(pos);
                if (rec_pair(pos + 1))
                    return true;
                now[i].pop_back();
            } else if (have[pos].second == have[now[i].back()].second &&
                       have[now[i].back()].first + 1 == have[pos].first) {
                type[i] = true;
                now[i].push_back(pos);
                if (rec_pair(pos + 1))
                    return true;
                now[i].pop_back();
            }
        }
        if (SZ(now[i]) == 2) {
            if (!type[i] && have[now[i].back()] == have[pos]) {
                now[i].push_back(pos);
                if (rec_pair(pos + 1))
                    return true;
                now[i].pop_back();
            }
            if (type[i] && have[pos].second == have[now[i].back()].second &&
                have[now[i].back()].first + 1 == have[pos].first) {
                now[i].push_back(pos);
                if (rec_pair(pos + 1))
                    return true;
                now[i].pop_back();
            }
        }
    }
    return false;
}

int solve() {
    n = 14;
    for (int i = 0; i < n; i++) {
        string x;
        cin >> x;
        have[i].second = x.back();
        x.pop_back();
        have[i].first = stoi(x);
    }
    sort(have, have + n);
    if (rec_win(0)) {
        cout << "Tsumo\n";
        return 1;
    }
    for (int i = 0; i < 5; i++)
        now[i].clear();
    bool a1 = rec_triple(0);

    for (int i = 0; i < 5; i++)
        now[i].clear();
    bool a2 = rec_pair(0);
    if (a1 || a2) {
        cout << "Tenpai\n";
        return 1;
    }
    cout << "Noten\n";
    return 1;
}

signed main() {
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
