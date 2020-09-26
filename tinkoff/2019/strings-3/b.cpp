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
const int ALP = 26;
const int MAXN = 1e6 + 7;
struct Node{
    int link = 0;
    int len = 0;
    int go[ALP];
    ll count = 0;
    Node(){
        for (int i = 0; i < ALP; i++)
            go[i] = -1;
    }
};
Node st[MAXN];
int sz = 0, lst = 0;
ll sum = 0;
void add(int c){
    int cur = sz++;
    int p = lst;
    c -= 'a';
    st[cur].len = st[lst].len + 1;
    while (p != -1 && st[p].go[c] == -1){
        st[cur].count += st[p].count;
        sum += st[p].count;
        st[p].go[c] = cur;
        // cout << p << "->" << cur << " " << (char)(c+'a') << '\n'; 
        p = st[p].link;
    }
    if (p == -1){
        lst = cur;
        return;
    }
    int q = st[p].go[c];
    if (st[p].len + 1 == st[q].len){
        st[cur].link = q;
    }
    else {
        int clone = sz++;
        st[clone].len = st[p].len + 1;
        for (int i = 0; i < ALP; i++)
            st[clone].go[i] = st[q].go[i];
        st[clone].link = st[q].link;
        while (p != -1 && st[p].go[c] == q){

            // cout << p << "-|>" << q << " " << (char)(c+'a') << '\n'; 
            // cout << p << "->" << clone << " " << (char)(c+'a') << '\n';
            st[q].count -= st[p].count;
            st[clone].count += st[p].count;
            st[p].go[c] = clone;
            p = st[p].link;

        }
        st[q].link = st[cur].link = clone;
    }
    lst = cur;
}
int solve() {
    st[0].link = -1;
    st[0].len = 0;
    st[0].count = 1;
    sz = 1;
    sum = 0;
    string s;
    for (int i = 0; i < lst; i++){
        fill(st[i].go, st[i].go + ALP, -1);
        st[i].count = 0;
    }
    lst = 0;
    if (!(cin >> s))
        return 1;
    for (char c : s){
        add(c);
        cout << sum << '\n';
    }
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