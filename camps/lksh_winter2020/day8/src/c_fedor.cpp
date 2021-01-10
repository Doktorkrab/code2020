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

vi cur;
V <vi> L, S;
void gen_list(int sum) {
    if (sum > 6)
        return;
    L.app(cur);
    for (int i = 1; i <= 6; ++i) {
        cur.app(i);
        gen_list(sum + i);
        cur.pop_back();
    }
}
void gen_multiset(int sum, int last) {
    if (sum > 6)
        return;

    vi cnt(7);
    trav(e, cur)
        cnt[e]++;
    S.app(cnt);

    for (int i = last; i <= 6; ++i) {
        cur.app(i);
        gen_multiset(sum + i, i);
        cur.pop_back();
    }
}
vi base = {0, 1, 0, 0, 0, 0, 0};

int C(int n, int k) {
    if (n < k)
        return 0;
    if (k == 0)
        return 1;
    int ans = 1;
    for (int i = 0; i < k; ++i)
        ans *= n - i;
    for (int i = 1; i <= k; ++i)
        ans /= i;
    return ans;
}
int C_rep(int n, int k) {
    if (k == 0)
        return 1;
    return C(n + k - 1, k);
}

vi solve(string s) {
    if (s == "B")
        return base;
    int sz = s.size();
    vi ans(7);
    if (s[0] == 'L') {
        vi t = solve(s.substr(2, sz - 3));
        trav(ls, L) {
            int sum = 0, fac = 1;
            trav(e, ls) {
                sum += e;
                fac *= t[e];
            }
            ans[sum] += fac;
        }
    }
    else if (s[0] == 'S') {
        vi t = solve(s.substr(2, sz - 3));
        trav(cnt, S) {
            int sum = 0, fac = 1;
            for (int w = 1; w < 7; ++w) {
                sum += cnt[w] * w;
                fac *= C_rep(t[w], cnt[w]);
            }
            ans[sum] += fac;
        }
    }
    else {
        string in = s.substr(2, sz - 3);
        assert(s[0] == 'P');
        int bal = 0, pos = -1;
        FOR(i, (int)in.size()) {
            if (in[i] == '(')
                bal++;
            else if (in[i] == ')')
                bal--;
            else if (in[i] == ',' && bal == 0)
                pos = i;
        }
        vi A = solve(in.substr(0, pos));
        vi B = solve(in.substr(pos + 1, sz - 3 - pos - 1));
        FOR(i, 7)
            FOR(j, 7)
                if (i + j <= 6) {
                    ans[i + j] += A[i] * B[j];
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
    gen_list(0);
    gen_multiset(0, 1);
    string s;
    cin >> s;
    cout << solve(s) << endl;
}