#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    srand(time(NULL));
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    vector<ll> fib = {1, 1};
    const ll INFLL = 1e18;
    while (1) {
        ll x = fib[fib.size() - 2] + fib[fib.size() - 1];
        if (x >= INFLL)
            break;
        fib.push_back(x);
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < fib.size(); j++) {
            if (fib[j] == a[i]) {
                cnt++;
                break;
            }
        }
    }
    cout << cnt;
}