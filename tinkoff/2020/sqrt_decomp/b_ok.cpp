#include <bits/stdc++.h>

using namespace std;

const int d = 2750, maxx = 200001;

int s[maxx];

int g[maxx];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        g[i] = s[i];
    }
    for (int i = 0; i < n; i += d) {
        sort(g + i, g + min(n, i + d));
    }
    int m;
    cin >> m;
    int t, a, b, c;
    for (int i = 0; i < m; i++) {
        cin >> t >> a >> b;
        if (t == 1) {
            a--;
            int l = (a / d) * d;
            int r = min(n, l + d);
            int pb = lower_bound(g + l, g + r, s[a]) - g;
            if (s[a] < b) {
                for (; pb < r - 1 && g[pb + 1] < b; pb++) {
                    g[pb] = g[pb + 1];
                }
                g[pb] = b;
            } else {
                for (; pb > l && g[pb - 1] > b; pb--) {
                    g[pb] = g[pb - 1];
                }
                g[pb] = b;
            }
            s[a] = b;
        } else {
            cin >> c;
            b--;
            int l = (b / d) * d;
            int r = min(n, l + d);
            int ans = 0;
            if (b > ((l + r) >> 1) || r >= c) {
                int t = min(r, c);
                for (int i = b; i < t; i++) {
                    if (s[i] < a) {
                        ans--;
                    }
                }
            } else {
                ans -= lower_bound(g + l, g + r, a) - g - l;
                for (int i = l; i < b; i++) {
                    if (s[i] < a) {
                        ans++;
                    }
                }
            }
            if (r < c) {
                int ll = (c / d) * d;
                while (r < ll) {
                    ans -= lower_bound(g + r, g + r + d, a) - g - r;
                    r += d;
                }
                l = r;
                r = min(l + d, n);
                if (c < ((l + r) >> 1)) {
                    for (int i = l; i < c; i++) {
                        if (s[i] < a) {
                            ans--;
                        }
                    }
                } else {
                    ans -= lower_bound(g + l, g + r, a) - g - l;
                    for (int i = c; i < r; i++) {
                        if (s[i] < a) {
                            ans++;
                        }
                    }
                }
            }
            ans *= 2;
            ans += c - b;
            if (ans < 0) {
                ans = 0;
            }
            cout << ans << '\n';
        }
    }
}
