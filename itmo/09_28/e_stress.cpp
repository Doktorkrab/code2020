#include <stdio.h>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <cstring>
#include <ctime>

#define fmax wa213dsdcs


using namespace std;

const int BASE = 1e9 + 7;
const int N = 5e5 + 800;
const int K = 20;

const int TEST = 0;

const int NN = 1010;
const int MN = 1 << 12;

struct Ask {
    int l, r, x;
    Ask(int l, int r, int x) : l(l - 1), r(r - 1), x(x) {}  
    Ask() {}
    void read() {
        scanf("%d%d%d", &l, &r, &x);
        --l; --r;
    }
    void print() {
        cerr << l + 1 << " " << r + 1 << " " << x << endl;
        return;
    }
    bool operator <(const Ask & u) const {
        return x < u.x;
    }
};

int n, m, k, pr[N], f[N], pf[N], pwx[N], rpwx[N], up[N];
int fmax[N][K], lt[N];

int F[NN][MN];

int pw(int x, int y) {
    int res = 1;
    while (y) {
        if (y & 1) res = (res * 1LL * x) % BASE;
        x = (x * 1LL * x) % BASE;
        y >>= 1;
    }
    return res;
}

int fs(int x) {
    int root = x;
    while (pr[root] != root) root = pr[root];
    while (pr[x] != x) { 
        int tmp = pr[x];
        pr[x] = root;
        x = tmp;
    }

    //if (pr[x] != x) pr[x] = fs(pr[x]);
    return root;
}

void uni(int x, int y) {
    x = fs(x);
    y = fs(y);
    pr[x] = y;
}

bool cmp(pair<int, int> u, pair<int, int> v) {
    if (u.first == v.first) return u.second > v.second;
    return u.first < v.first;
}

int brute(int n, int m, int k, vector<Ask> vec) {
    //for (auto e : vec) e.print();
    memset(F, 0, sizeof(F));
    F[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < (1 << m); mask++) {
            if (F[i][mask] == 0) continue;
            for (int j = 1; j <= k; j++) {
                int nmask = mask;
                for (int e = 0; e < m; e++) {
                    if ((vec[e].l <= i) && (vec[e].r >= i)) {
                        if (vec[e].x < j) {
                            nmask = -1;
                            break;
                        }
                        if (vec[e].x == j) nmask |= (1 << e);
                    }
                }
                if (nmask < 0) continue;
                F[i + 1][nmask] += F[i][mask];
                if (F[i + 1][nmask] >= BASE) F[i + 1][nmask] %= BASE;
            }
        }
    }
    return F[n][(1 << m) - 1];
}

int solve(int n, int m, int k, vector<Ask> vec) {
    for (int i = 0; i < m; i++) {
        assert(vec[i].l <= vec[i].r);
        if (vec[i].x > k) return 0;
    }
    if (k == 1) {
        return 1;
    }
    sort(vec.begin(), vec.end());
    for (int i = 0; i < n; i++) up[i] = k;
    for (int i = 0; i <= n; i++) pr[i] = i;
    for (int i = 0; i < vec.size(); i++) {
        if ((i == 0) || (vec[i].x != vec[i - 1].x)) {
            int j = i;
            while ((j < vec.size()) && (vec[j].x == vec[i].x)) {
                int o = vec[j].l;
                int no = fs(o);
                if (no > vec[j].r) {
                    return 0;
                }
                j++;
            }
        }
        int o = vec[i].l;
        int no;
        while ((no = fs(o)) <= vec[i].r) {
            up[no] = vec[i].x;
            uni(no, no + 1);
            o = no + 1;
        }
    }
    for (int i = 0; i <= n; i++) pr[i] = i;
    int ans = 1;
    for (int i = 0; i < vec.size();) {
        int j = i;
        vector<pair<int, int>> v;
        while ((j < vec.size()) && (vec[i].x == vec[j].x)) {
            v.push_back(make_pair(vec[j].l, vec[j].r));
            ++j;
        }
        int X = vec[i].x;
        sort(v.begin(), v.end(), cmp);
        vector<int> st;
        vector<int> st2;
        for (int e = 0; e < v.size(); e++) {
            while ((st.size() > 0) && (v[st.back()].second >= v[e].second)) {
                st2.push_back(st.back());
                st.pop_back();
            }
            st.push_back(e);
        } 
        vector<pair<int, int>> vv;
        //for (int e : st) vv.push_back(v[e]);
        for (int i = 0; i < st.size(); ++i) {
        	int e = st[i];
        	vv.push_back(v[e]);
        }
        vector<pair<int, int>> tmpv = v;
        v = vv;
        vector<int> points;
        for (int e = 0; e < v.size(); e++) {
            int o = v[e].first;
            int no;
            while ((no = fs(o)) <= v[e].second) {
                points.push_back(no);
                uni(no, no + 1);
                o = no + 1;
            }
        }
        for (int e = 0; e < st2.size(); e++) {
            int o = tmpv[st2[e]].first;
            int rr = tmpv[st2[e]].second;
            int no;
            while ((no = fs(o)) <= rr) {
                ans = (ans * 1LL * up[no]) % BASE;
                uni(no, no + 1);
                o = no + 1;
            }
        }
        if (X == 1) {
            i = j;
            continue;
        }
        sort(points.begin(), points.end());

        //for (int x : points) cerr << x << " ";
        //cerr << endl;
        int o = 0;
        pwx[0] = rpwx[0] = 1;
        int revx = pw(X - 1, BASE - 2);
        for (int it = 1; it <= points.size(); it++) {
            pwx[it] = (pwx[it - 1] * 1LL * (X - 1)) % BASE;
            rpwx[it] = (rpwx[it - 1] * 1LL * revx) % BASE;
        }
        for (int it = 0; it <= points.size(); it++) {
            pf[it] = f[it] = 0;
        }
        int cans = 0;
        for (int it = 0; it < points.size(); it++) {
            int e = points[it];
            while ((o < v.size()) && (v[o].second < e)) o++;
            if (o == 0) {
                f[it] += pw(X - 1, it);
            }
            int low = 0;
            if (o != 0) low = lower_bound(points.begin(), points.end(), v[o - 1].first) - points.begin();
            int sum = (pf[it] - pf[low] + BASE) % BASE;
            sum = (sum * 1LL * pwx[it]) % BASE;
            f[it] += sum;
            if (f[it] >= BASE) f[it] %= BASE;
            pf[it + 1] = (pf[it] + f[it] * 1LL * rpwx[it + 1]) % BASE;
            if ((v.back().first <= e) && (v.back().second >= e)) {
                int cur = f[it];
                int len = (int)points.size() - it - 1;
                cur = (cur * 1LL * pwx[len]) % BASE;
                cans += cur;
                if (cans >= BASE) cans %= BASE;
            }
        }
    //  cerr << pf[0] << " " << pf[1] << endl;
    //  cerr << i << " " << cans << endl;
        ans = (ans * 1LL * cans) % BASE;    
        if (ans < 0)
            vec[i].print();
        i = j;
    }
    int o = 0;
    int no;
    while ((no = fs(o)) < n) {
        ans = (ans * 1LL * up[no]) % BASE;
        o = no + 1;
    }
    return ans;
}

/*

void gen(int &n, int &m, int &k, vector<Ask> &vec) {
    n = rand() % 1000 + 1;
    m = rand() % 10 + 1;
    k = rand() % 50 + 1;
    vector<int> a;
    for (int i = 0; i < n; i++) {
        a.push_back(rand() % k + 1);
    }
    for (int i = 0; i < n; i++) {
        fmax[i][0] = a[i];
    }
    for (int j = 1; j < K; j++ ){
        for (int i = 0; i < n; i++) {
            int ni = i + (1 << (j - 1));
            fmax[i][j] = fmax[i][j - 1];
            if (ni < n) fmax[i][j] = max(fmax[i][j], fmax[ni][j - 1]);
        }
    }
    lt[1] = 0;
    for (int i = 2; i <= n; i++) lt[i] = lt[i >> 1] + 1;
    for (int i = 0; i < m; i++) {
        int l = rand() % n;
        int r;
        if (l + 20 <= n) {
            r = l + (rand() % 20);
        } else r = rand() % n;
        if (l > r) swap(l, r);
        int lk = lt[r - l + 1];
        int rr = r - (1 << lk) + 1;
        int x = max(fmax[l][lk], fmax[rr][rr]);
        vec.push_back(Ask(l + 1, r + 1, x));
    }
}

void gen2(int &n, int &m, int &k, vector<Ask> &vec) {
    n = rand() % 100 + 1;
    m = rand() % 5 + 1;
    k = rand() % 500 + 1;
    for (int i = 0; i < m; i++) {
        int l = rand() % n;
        int r = rand() % n;
        if (l > r) swap(l, r);
        int x = rand() % k + 1;
        vec.push_back(Ask(l + 1, r + 1, x));
    }
}

void gen_big_test(int &n, int &m, int &k, vector<Ask> &vec) {
    n = rand() % 100 + 1;
    m = rand() % 5 + 1;
    k = rand() % 5 + 1;
    vector<int> a;
    for (int i = 0; i < n; i++) a.push_back(rand() % k + 1);
    for (int i = 0; i < n; i++) fmax[i][0] = a[i];
    for (int j = 1; j < K; j++) {
        for (int i = 0; i < n; i++) {
            int ni = i + (1 << (j - 1));
            fmax[i][j] = fmax[i][j - 1];
            if (ni < n) fmax[i][j] = max(fmax[i][j], fmax[ni][j]);
        }
    }
    lt[1] = 0;
    for (int i = 2; i <= n; i++) lt[i] = lt[i >> 1] + 1;
    for (int i = 0; i < m; i++) {
        int l = rand() % n;
        int r = rand() % n;
        if (l > r) swap(l, r);
        int len = lt[r - l + 1];
        int rr = r - (1 << len) + 1;
        int x = max(fmax[l][len], fmax[rr][len]);
        vec.push_back(Ask(l + 1, r + 1, x));
    }
}

int stress() {
    if (!TEST) return 0;
    static int CNT_TEST = 0;
    CNT_TEST++;
    int n, m, k;
    vector<Ask> vec;
    //gen_big_test(n, m, k, vec);
    gen(n, m, k, vec);
    //cerr << n << " " << m << " " << k << endl;
    //int ans1 = brute(n, m, k, vec);
    for (auto u : vec) u.print();
    int ans2 = solve(n, m, k, vec);
    int ans1 = brute(n, m, k, vec);
    if (ans1 != ans2) {
        cerr << "answer is " << ans1 << " need " << ans2 << endl; 
        cerr << n << " " << m << " " << k << endl;
        for (auto u : vec) u.print();
        assert(false);
    } else cerr << "ok:" << CNT_TEST << "(" << ans1 << "," << ans2 << ")" << endl;
    return 1;
}
*/

int main() {
    srand(time(0));
    //freopen("lottery.in", "r", stdin);
    //freopen("lottery.out", "w", stdout);
    //while (stress()) {}
        scanf("%d%d%d", &n, &m, &k);
        vector<Ask> vec;
        for (int i = 0; i < m; i++) {
            Ask cur;
            cur.read();
            vec.push_back(cur);
        }
        int ans1 = solve(n, m, k, vec);
        printf("%d\n", ans1);
}
 
