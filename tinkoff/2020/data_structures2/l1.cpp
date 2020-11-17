#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

const int MAXA = 3000000;
const int MAXN = 100000;
const int MAXLOG = 22;

const long long COST = 1000 * 1000 * 1000;


long long dp[MAXA];
int l[MAXN], r[MAXN], c[MAXN];

int p[MAXA];
int mv[MAXA];
int rk[MAXA];
int A;

int get(int a) {
    int res = a;
    while (p[res] != res) res = p[res];
    while (p[a] != a) {
        int t = p[a];
        p[a] = res;
        a = t;
    }
    return res;
}

void join(int a, int b) {
    a = get(a);
    b = get(b);
    if (rk[a] > rk[b]) swap(a, b);
    p[a] = b;
    if (dp[mv[b]] > dp[mv[a]]) {
        mv[b] = mv[a];
    }
    if (rk[a] == rk[b]) rk[b]++;
}

long long get_min(int r) {
    return dp[mv[get(r)]];
}

vector<int> stack;

void add(int pos) {
    mv[pos] = pos;
    while (!stack.empty() && dp[stack.back()] > dp[pos]) {
        join(pos, stack.back());
        stack.pop_back();
    }
    stack.push_back(pos);
    cout << "stack: ";
    for (int i : stack)
        cout << i << ' ';
    cout << '\n';
}

int main() {
//    freopen("anti.in", "r", stdin);
//    freopen("anti.out", "w", stdout);
    int n;
    scanf("%d%d", &n, &A);

    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &l[i], &r[i], &c[i]);
    }

    for (int i = 0; i <= A; i++) {
        dp[i] = 1LL * i * COST;
        p[i] = i;
        rk[i] = i;
        mv[i] = -1;
    }

    for (int i = A; i >= 0; i--) {
        add(i);
        for (int j = 0; j < n; j++) {
            if (i - l[j] < 0) continue;
            int st = i - l[j];
            if (st + r[j] > A) continue;
            long long mv = get_min(st + r[j]);
            mv -= c[j];
            dp[st] = max(dp[st], mv);
        }
    }

    printf("%lld\n", dp[0]);
}
