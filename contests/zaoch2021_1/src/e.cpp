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


struct Event {
    string type;
    int from, to;
};

int n, k;
const int MAXN = 1005;
const int MAXK = 12;
const int MAXC = (1 << MAXK);
int used[MAXN][MAXC];
Event events[MAXN];
string print_ans(int mask){
    string ans;
    while (mask > 0){
        ans += '0' + (mask % 2);
        mask /= 2;
    }
//    reverse(ALL(ans));
    while (SZ(ans) != k)
        ans.push_back('0');
    return ans;
}
bool dfs(int line, int registers) {
    used[line][registers] = 1;
//    cout << events[line].type << ' ' << print_ans(registers) << '\n';
    if (events[line].type == "begin"){
        bool ret = dfs(1, registers);
        used[line][registers] = 2;
        return ret;
    }
    if (events[line].type == "end"){
        used[line][registers] = 2;
        return false;
    }
    int next = registers;
    int from = events[line].from;
    int to = events[line].to;
    int next_line = line + 1;
    
    if (events[line].type != "jump") {
        next &= ~(1 << to);
    }
    if (events[line].type == "and") {
        int reg1 = (registers >> from) & 1;
        int reg2 = (registers >> to) & 1;
        next |= ((reg1 & reg2) << to);
    }
    if (events[line].type == "or") {
        int reg1 = (registers >> from) & 1;
        int reg2 = (registers >> to) & 1;
        next |= ((reg1 | reg2) << to);
    }
    if (events[line].type == "xor") {
        int reg1 = (registers >> from) & 1;
        int reg2 = (registers >> to) & 1;
//        cout << reg1 << ' ' << reg2 << '\n';
//        cout << to << ' ' << from << '\n';
//        cout << print_ans(next) << '\n';
        next |= ((reg1 ^ reg2) << to);
    }
    if (events[line].type == "move") {
        int reg1 = (registers >> from) & 1;
        next |= ((reg1) << to);
    }
    if (events[line].type == "set") {
        next |= (from << to);
    }
    if (events[line].type == "not"){
        int reg1 = (registers >> to) & 1;
        next |= ((reg1 ^ 1) << to);
    }
    if (events[line].type == "jump"){
        int reg = (registers >> to) & 1;
        if (reg)
            next_line = events[line].from;
    }


    if (used[next_line][next] == 2) {
        used[next_line][next] = 2;
        return false;
    }
    if (used[next_line][next] == 1)
        return true;
    bool ret = dfs(next_line, next);
    used[next_line][next] = 2;
    return ret;
}

int solve() {
    if (!(cin >> n >> k))
        return 1;
    string s;
    for (int i = 0; i < n; i++) {
        cin >> s;
        int a, b;
        if (s == "and" || s == "or" || s == "xor" || s == "move" || s == "set" || s == "jump") {
            cin >> a >> b;
            events[i].to = a;
            events[i].from = b;
        } else if (s == "not") {
            cin >> a;
            events[i].to = a;
        }
        events[i].type = s;
    }
//    cout << dfs(0, 1) << '\n';
//    return 0;
    for (int mask = 0; mask < (1 << k); mask++){
        if (used[0][mask] == 0 && dfs(0, mask)){
            cout << "No\n" << print_ans(mask) << '\n';
            return 0;
        }
    }
    cout << "Yes\n";
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("e.in", "r", stdin);
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
