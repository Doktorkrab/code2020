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
const int MAXN = 105;
int arr[MAXN];
int can[MAXN];
int solve() {
   if (!(cin >> n))
       return 1;
   vector<int> kek;
   for (int i = 0; i < n; i++)
       cin >> arr[i];
   for (int i = 0; i < n; i++){
        cin >> can[i];
        if (!can[i])
            kek.push_back(arr[i]);
   }
   sort(ALL(kek));
   reverse(ALL(kek));
   int pnt = 0;
   for (int i = 0; i < n; i++)
       if (can[i] == 0)
           arr[i] = kek[pnt++];
   for (int i = 0; i < n; i++)
       cout << arr[i] << " \n"[i + 1 == n];
   return 0;
}

signed main() {
   ios::sync_with_stdio(0);
   cin.tie(0);
   cout.tie(0);
   int tests = 1e9;
    cin >> tests;
   for (int i = 1; i <= tests; i++) {
       if (solve())
           break;
#ifdef LOCAL
       cout << "------------------------------\n";
#endif
   }
}
