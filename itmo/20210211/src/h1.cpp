#include <iostream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

#define INF 1e9
vector<vector<char>> lst;
vector<int> d;
int n, m;
vector<vector<int>> mat;
vector<vector<int>> curd;
vector<int> p1 = {0, 0, -1, 1};
vector<int> p2 = {1, -1, 0, 0};
vector<vector<pair<int, int>>> g;

void bfs(int x, int y) {
    d[mat[x][y]] = 0;
    curd[x][y] = 0;
    queue<pair<int, int>> q;
    q.push({x, y});
    while (!q.empty()) {
        pair<int, int> ccc = q.front();
        q.pop();
        int a = ccc.first, b = ccc.second;
        if (mat[a][b] != -1) {
            d[mat[a][b]] = min(d[mat[a][b]], curd[a][b]);
        }
        if (curd[a][b] == 100){
            continue;
        }
        for (int k = 0; k < 4; k++) {
            int aa = a + p1[k], bb = b + p2[k];
            if (aa < 0 || bb < 0 || aa >= n || bb >= m || lst[aa][bb] == '#') continue;
            if (curd[aa][bb] > curd[a][b] + 1) {
                curd[aa][bb] = curd[a][b] + 1;
                q.push({aa, bb});
            }
        }
    }
}

vector<int> used;


void djk(int st) {
    used[st] = 0;
    set<pair<int, int>> q;
    q.insert({0, st});
    while (!q.empty()) {
        pair<int, int> ccc = *q.begin();
        q.erase(q.begin());
        int v = ccc.second, c = ccc.first;
        for (auto to : g[v]) {
            if (used[to.first] > c + to.second) {
                if (used[to.first] != INF)
                    q.erase(q.find({used[to.first], to.first}));
                used[to.first] = c + to.second;
                q.insert({used[to.first], to.first});
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int k, s;
    cin >> k >> s;
    cin >> n >> m;
    vector<pair<int, int>> pos;
    int st, f;
    mat.assign(n, vector<int>(m, -1));
    for (int i = 0; i < n; i++) {
        lst.push_back({});
        for (int j = 0; j < m; j++) {
            char x;
            cin >> x;
            lst[i].push_back(x);
            if (lst[i][j] == '$' || lst[i][j] == '@' || lst[i][j] == 'E') {
                pos.push_back({i, j});
                mat[i][j] = pos.size() - 1;
            }
            if (x == '@') st = pos.size() - 1;
            if (x == 'E') f = pos.size() - 1;

        }
    }
    g.assign(pos.size(), {});
    for (int i = 0; i < pos.size(); i++) {
        d.assign(pos.size(), INF);
        curd.assign(n, vector<int>(m, INF));
        bfs(pos[i].first, pos[i].second);
        for (int j = 0; j < pos.size(); j++) {
            if (j != i) {
                if (s / k >= d[j]) {
                    //cerr << i  << " " << j << " " << d[j] << " " << pos[j].first << " " << pos[j].second << '\n';
                    g[i].push_back({j, d[j]});
                }
            }
        }
    }
    used.assign(pos.size(), INF);
    djk(st);

    if (used[f] == INF) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << used[f] * k << '\n';
    }
//    for (int i =0 ; i < pos.size(); i++){
//        cerr << used[i] << " ";
//    }

    return 0;
}