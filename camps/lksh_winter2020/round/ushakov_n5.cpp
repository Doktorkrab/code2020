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
int inc_ub(vi &a, int x) { //first bigger than x
    return upper_bound(all(a), x) - a.begin();
}
int dec_ub(vi &a, int x) { //first less than x
    int l = -1, r = a.size();
    while (l < r - 1) {
        int m = (l + r) >> 1;
        if (a[m] < x)
            r = m;
        else
            l = m;
    }
    return r;
}

int slow(V <ii> a) {
    int n = a.size();
    const int INF = 2e18;
    vi cx, cy;
    FOR (i, n) {
        cx.app(a[i].x);
        cy.app(a[i].y);
    }
    sort(all(cx));
    cx.resize(unique(all(cx)) - cx.begin());
    sort(all(cy));
    cy.resize(unique(all(cy)) - cy.begin());
    int ans = INF;
    FOR (lx, (int)cx.size()) {
        for (int rx = lx; rx < (int)cx.size(); ++rx) {
            FOR (ly, (int)cy.size()) {
                for (int ry = ly; ry < (int)cy.size(); ++ry) {

                    int nn = (cx[rx] - cx[lx]) * (cy[ry] - cy[ly]);

                    if (nn < ans) {
                        int L = INF, R = 0, D = INF, U = 0;
                        trav (p, a) {
                            if (p.x < cx[lx] || p.x > cx[rx] || p.y < cy[ly] || p.y > cy[ry]) {
                                ckmin(L, p.x);
                                ckmax(R, p.x);
                                ckmin(D, p.y);
                                ckmax(U, p.y);
                            }
                        }
                        if (L < R && D < U)
                            nn += (R - L) * (U - D);
                        ckmin(ans, nn);
                    }

                }
            }
        }
    }
    return ans;
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
        int n;
        cin >> n;
        V <ii> a(n);
        FOR (i, n) {
            cin >> a[i].x >> a[i].y;
        }
        cout << slow(a) << endl;
    }
}