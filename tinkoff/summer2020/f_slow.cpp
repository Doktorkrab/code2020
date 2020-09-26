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
 
int n, m, q;
const int MAXN = 1e5 + 7;
pair<int, int> queries[MAXN];
int arr[MAXN];
int ans[MAXN];

int mod(int a, int b){
    //cout << a << ' ' << (abs(a) + b - 1) / b * b << '\n';
    if (a < 0){
        int tmp = (abs(a) + b - 1) / b * b;
        a = tmp + a;
    }
    return a % b;
}
int solve() {
    if (!(cin >> n >> m >> q))
        return 1;
    for (int i = 0; i < q; i++){
        cin >> queries[i].first >> queries[i].second;
        queries[i].second *= -1;
    }
    reverse(queries, queries + q);
    //cout << mod(-3, 2) << '\n';
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    vector<vector<int>> tmp(q, vector<int>(n));
    vector<vector<int>> tmp1(q, vector<int>(n));
    for (int i = 0; i < n; i++){
        int offset = i % m, block = i / m;
        cout << "(" << offset << ", " << block << ") -> ";
        //cout << "!" << offset << ' ' << block << '\n';
        for (int j = 0; j < q; j++){
            offset += queries[j].second;
            if (queries[j].first == 2){
                block += (offset - mod(offset, m)) / m;
                tmp1[j][i] = (offset - mod(offset, m)) / m;
            }
            tmp[j][i] = offset;
            offset = mod(offset, m);
            //cout << '\t' << offset << ' ' << block << '\n';
        }
        block = mod(block, n / m);
        //cout << block << ' ' << offset << ' ' << block * m + offset << '\n';
        cout << "(" << offset << ", " << block << ")\n";
        ans[block * m + offset] = arr[i];
    }
    for (auto i : tmp){
        for (int j : i)
            cout << j << ' ';
        cout << '\n';
    }
    cout << '\n';
    for (auto i : tmp){
        for (int j : i)
            cout << mod(j, m) << ' ';
        cout << '\n';
    }
    cout << '\n';
    for (auto i : tmp1){
        for (int j : i)
            cout << j << ' ';
        cout << '\n';
    }
    cout << '\n';
    //for (auto i : tmp1){
        //assert(count(ALL(i), 0) == 0 || count(ALL(i), 0) == SZ(i));
    //}
    for (int i = 0; i < n; i++)
        cout << ans[i] << " \n"[i + 1 == n];
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

