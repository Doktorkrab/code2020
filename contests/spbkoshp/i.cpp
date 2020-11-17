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

const int MAX_N = 100000 + 7;

vector<int> graph[MAX_N];
 
int solve() {
    if (!(cin >> n))
        return 1;
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        graph[a].emplace_back(b);
        graph[b].emplace_back(a);
    }

    vector<int> dist(n, MAX_N);
    dist[0] = 0;
    deque<int> q;
    q.push_back(0);
    long long answer = 0;
    vector<long long> powers_two_to_one(n, 0);
    while (!q.empty()) {
        int now = q.front();
        q.pop_front();
        for (int v : graph[now]) {
            if (dist[now] == 2 && dist[v] == 1) {
                powers_two_to_one[now]++;
            }
            if (dist[now] == 0) {
                dist[v] = 1;
                q.push_back(v);
            }
            if (dist[now] == 1) {
                if (dist[v] > 2) {
                    dist[v] = 2;
                    q.push_back(v);
                }
            }
        }
    }
    for (long long e : powers_two_to_one) {
        answer += (e * (e - 1));
    }
    vector<int> powers_from_one_to_one(n, 0);
    for (int i = 0; i < n; ++i) {
        if (dist[i] != 1) continue;
        for (int v : graph[i]) {
            if (dist[v] == 1) {
                powers_from_one_to_one[i]++;
                powers_from_one_to_one[v]++;
            }
        }
    }
    for (int i = 0; i < n; ++i) powers_from_one_to_one[i] /= 2;
    for (int i = 0; i < n; ++i) {
        answer += (powers_from_one_to_one[i] * (powers_from_one_to_one[i] - 1));
    }
    cout << answer << '\n';
    return 0;
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
