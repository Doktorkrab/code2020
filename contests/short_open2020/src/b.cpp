#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
#include <ostream>
#define FAST_ALLOCATOR_MEMORY 5e8
#ifdef FAST_ALLOCATOR_MEMORY
int allocator_pos = 0;
	char allocator_memory[(int)FAST_ALLOCATOR_MEMORY];
	inline void * operator new ( size_t n ) {
		char *res = allocator_memory + allocator_pos;
		allocator_pos += n;
		assert(allocator_pos <= (int)FAST_ALLOCATOR_MEMORY);
		return (void *)res;
	}
	inline void operator delete ( void * ) noexcept { }
	//inline void * operator new [] ( size_t ) { assert(0); }
	//inline void operator delete [] ( void * ) { assert(0); }
#endif
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

int n, m, q;
const int MAXN = 1e4 + 7;
ll costs[MAXN];
ll best[MAXN];
multiset<ll> best_set;
multiset<ll> now[MAXN];
multiset<ll> cant[MAXN];

void recalc(int v){
    best_set.erase(best_set.find(best[v]));
    best[v] = 0;
    if (SZ(now[v])){
        ll best_now = (*now[v].rbegin());
        ll best_sec = 0;
        if (SZ(cant[v]))
            best_sec = (*cant[v].rbegin());
        if (SZ(now[v]) > 1)
            best_sec = max(best_sec, (*next(now[v].rbegin())));
        best[v] = best_sec + best_now + costs[v];
    }
    best_set.insert(best[v]);
}
void add_edge(int v, int u){
    now[v].erase(now[v].find(costs[u]));
    now[u].erase(now[u].find(costs[v]));
    cant[v].insert(costs[u]);
    cant[u].insert(costs[v]);
}
void del_edge(int v, int u){
    cant[v].erase(cant[v].find(costs[u]));
    cant[u].erase(cant[u].find(costs[v]));
    now[v].insert(costs[u]);
    now[u].insert(costs[v]);
}
int solve() {
    if (!(cin >> n >> m >> q))
        return 1;
    for (int i = 0; i < n; i++) {
        cin >> costs[i];
        best_set.insert(0);
    }
    for (int i = 0; i < n; i++){
        now[i] = multiset<ll>(costs, costs + n);
        now[i].erase(now[i].find(costs[i]));
    }
    for (int i = 0; i < m; i++){
        int v, u;
        cin >> v >> u;
        --v, --u;
        add_edge(v, u);
    }
    for (int i = 0; i < n; i++)
        recalc(i);
    for (int i = 0; i < q; i++){
        int type, v, u;
        cin >> type >> v >> u;
        --v, --u;
        if (type == 2) {
            del_edge(v, u);
        }
        if (type == 1){
            add_edge(v, u);
        }
        recalc(v);
        recalc(u);
        cout << (*best_set.rbegin()) << '\n';
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
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
