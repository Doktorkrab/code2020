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
const int MAXN = 15;
int place_row[MAXN];
int placed[MAXN][MAXN];
int rows[MAXN];
int columns[MAXN];
int carry_row[MAXN];
int used[10005];
int rec(int pos){
    if (pos == n){
        bool good = true;
        for (int i = 0; i < n; i++)
            good &= (place_row[i] == 2);
        if (good){
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    cout << placed[i][j] << " \n"[j + 1 == n];
        }
        return 0;
    }
    for (int i = 0; i < n; i++){
        if (place_row[i] == 2)
            continue;
        place_row[i]++;
        for (int j = i + 1; j < n; j++){
            if (place_row[j] == 2)
                continue;
            place_row[j]++;
            int a = -1;
            if (place_row[i] == 2)
                a = carry_row[i];
            int b = -1;
            if (place_row[j] == 2)
                b = carry_row[j];
            if (a == -1 && b == -1){
                for (int k = 1; k * k <= columns[pos]; k++){
                    if (carry_row[i] % k == 0 && carry_row[j] % (columns[pos] / k) == 0 && k != (columns[pos] / k) && !used[k] && !used[columns[pos] / k]){
                        used[k] = used[columns[pos] / k] = true;
                        carry_row[i] /= k;
                        carry_row[j] /= (columns[pos] / k);
                        placed[pos][i] = k;
                        placed[pos][j] = columns[pos] / k;
                        if (rec(pos + 1))
                            return 1;
                        carry_row[i] *= k;
                        carry_row[j] *= (columns[pos] / k);
                        placed[pos][i] = placed[pos][j] = 0;
                        used[k] = used[columns[pos] / k] = false;
                    }
                    if (carry_row[j] % k == 0 && carry_row[i] % (columns[pos] / k) == 0 && k != (columns[pos] / k) && !used[k] && !used[columns[pos] / k]){
                        used[k] = used[columns[pos] / k] = true;
                        carry_row[j] /= k;
                        carry_row[i] /= (columns[pos] / k);
                        placed[pos][j] = k;
                        placed[pos][i] = columns[pos] / k;
                        if (rec(pos + 1))
                            return 1;
                        carry_row[j] *= k;
                        carry_row[i] *= (columns[pos] / k);
                        placed[pos][j] = placed[pos][i] = 0;
                        used[k] = used[columns[pos] / k] = false;
                    }
                }
            }
            int bb = columns[pos] / b;
            if (a == -1 && b != -1 && columns[pos] % b == 0 && !used[columns[pos] / b] && !used[b] && carry_row[i] % (bb) == 0){
                used[columns[pos] / b] = true;
                used[b] = true;
                placed[pos][j] = b;
                placed[pos][i] = columns[pos] / b;
                carry_row[i] /= bb;
                if (rec(pos + 1))
                    return 1;
                used[columns[pos] / b] = false;
                used[b] = false;
                placed[pos][j] = 0;
                placed[pos][i] = 0;
                carry_row[i] *= bb;
            }
            int aa = columns[pos] / a;
            if (b == -1 && a != -1 && columns[pos] % a == 0 && !used[columns[pos] / a] && !used[a] && carry_row[j] % aa == 0){
                used[columns[pos] / a] = true;
                used[a] = true;
                carry_row[j] /= aa;
                placed[pos][i] = a;
                placed[pos][j] = columns[pos] / a;
                if (rec(pos + 1))
                    return 1;
                used[columns[pos] / a] = false;
                used[a] = false;
                placed[pos][j] = 0;
                placed[pos][i] = 0;
                carry_row[j] *= aa;
            }
            if (a != -1 && b != -1 && !used[a] && !used[b] && a * b == columns[pos]){
                used[a] = used[b] = true;
                placed[pos][i] = a;
                placed[pos][j] = b;
                if (rec(pos + 1))
                    return 1;
                placed[pos][i] = 0;
                placed[pos][j] = 0;
                used[a] = used[b] = false;
            }
            place_row[j]--;
        }
        place_row[i]--;
    }
    return 0;
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++){
        cin >> rows[i];
        carry_row[i] = rows[i];
    }
    //for (int i = 0; i < n; i++)
        //cerr << carry_row[i] << " \n"[i + 1 == n];
    for (int i = 0; i < n; i++)
        cin >> columns[i];
    assert(!rec(0));
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
