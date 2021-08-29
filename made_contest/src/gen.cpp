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


mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

const int L = 20;
string res;
void gen(int len){
    if (len == L)
        return;
    if (rnd() % 2)
        res = "(" + res + ")";
    else
        res += "()";
    gen(len + 2);
}

void gen_random(){
    for (int i = 0; i < L; i++)
        res += "()"[rnd() % 2];
}

signed main() {
    gen(0);
    vector<string> ok;
    while (SZ(res)){
        if (SZ(res) == 1){
            ok.push_back(res);
            break;
        }
        int l = rnd() % (SZ(res) - 1) + 1;
        ok.push_back(res.substr(0, l));
        res = res.substr(l);
    }
    shuffle(ALL(ok), rnd);
    cout << SZ(ok) << '\n';
    for (auto s : ok)
        cout << s << '\n';
}
