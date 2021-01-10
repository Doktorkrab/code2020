#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ii pair <int, int>
#define app push_back
#define all(a) a.begin(), a.end()
#define bp __builtin_popcountll
#define ll long long
#define mp make_pair
#define x first
#define y second
#define Time (double)clock()/CLOCKS_PER_SEC
#define debug(x) std::cout << #x << ": " << x << '\n';
#define FOR(i, n) for (int i = 0; i < n; ++i)
#define pb push_back
#define trav(a, x) for (auto& a : x)
using vi = vector<int>;
template <typename T>
std::ostream& operator <<(std::ostream& output, const pair <T, T> & data)
{
    output << "(" << data.x << "," << data.y << ")";
    return output;
}
template <typename T>
std::ostream& operator <<(std::ostream& output, const std::vector<T>& data)
{
    for (const T& x : data)
        output << x << " ";
    return output;
}
//ll div_up(ll a, ll b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up
//ll div_down(ll a, ll b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down 
#define tcT template<class T
#define tcTU tcT, class U
tcT> using V = vector<T>;
tcT> void re(V<T>& x) {
    trav(a, x)
        cin >> a;
}
tcT> bool ckmin(T& a, const T& b) {
    return b < a ? a = b, 1 : 0;
} // set a = min(a,b)
tcT> bool ckmax(T& a, const T& b) {
    return a < b ? a = b, 1 : 0;
}

const int N = 1007;

int n, m;
vi g[N];
int dist[N];

bool used[N];
int BAN = -1;
bool dfs(int u, int w) {
    if (u == BAN)
        return 0;

    used[u] = 1;
    for (int v : g[u]) {
        if (v == BAN)
            continue;

        if (v == w)
            return 1;

        if (!used[v])
            if (dfs(v, w))
                return 1;
    }
    return 0;
}

signed main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
#define endl '\n'
    ios_base::sync_with_stdio(0); cin.tie(0);
#endif

    int t;
    cin >> t;

    while (t--) {
        cin >> n >> m;
        FOR (i, N) {
            g[i].clear();
        }
        FOR (i, m) {
            int u, v;
            cin >> u >> v;
            g[u].app(v);
        }

        FOR (i, N) {
            dist[i] = N;
        }

        dist[1] = 0;
        queue <int> q;
        q.push(1);

        while (q.size()) {
            int u = q.front(); q.pop();
            for (int v : g[u]) {
                if (ckmin(dist[v], dist[u] + 1)) {
                    q.push(v);
                }
            }
        }

        if (!dfs(1, n)) {
            cout << 0 << endl;
            cout << endl;
            continue;
        }

        vi ans;
        for (int u = 1; u <= n; ++u) {
            memset(used, 0, sizeof used);
            BAN = -1;
            if (!dfs(u, u)) {
                memset(used, 0, sizeof used);
                BAN = u;
                if (!dfs(1, n)) {
                    ans.app(u);
                }
            }
        }

        auto comp = [&] (int u, int v) {
            return dist[u] < dist[v];
        };

        sort(all(ans), comp);

        cout << ans.size() << endl;
        cout << ans << endl;
    }

}