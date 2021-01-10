#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef complex<double> cd;

const double PI = acos(-1);

const int MOD = 7;

long long inq(long long x, long long y)
{
    if (!y) return 1;
    long long l = inq(x, y / 2);
    if (y % 2) return l * l % MOD * x % MOD;
    return l * l % MOD;
}

int lg;

int bitreverse(int x)
{
    int y = 0;
    for (int i = 0; i < lg; i++)
    {
        if ((x & (1 << i)))
            y = 2 * y + 1;
        else
            y = 2 * y;
    }
    return y;
}

vector<cd> dft(vector<cd> a, int fl)
{
    for (int i = 0; i < a.size(); i++)
    {
        if (i < bitreverse(i))
            swap(a[i], a[bitreverse(i)]);
    }
    for (int len = 2; len <= a.size(); len <<= 1)
    {
        double ang = 2 * PI / len / fl;
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < a.size(); i += len)
        {
            cd w(1);
            for (int j = 0; j < len / 2; j++)
            {
                cd v = a[i + j], u = a[i + j + len / 2] * w;
                a[i + j] = v + u;
                a[i + j + len / 2] = v - u;
                w *= wlen;
            }
        }
    }
    return a;
}

vector<ll> fft(vector<ll> a, vector<ll> b)
{
    if (max(a.size(), b.size()) <= 3000)
    {
        vector<ll> c(a.size() + b.size() - 1);
        for (int i = 0; i < a.size(); i++)
        {
            for (int j = 0; j < b.size(); j++)
            {
                c[i + j] = c[i + j] + a[i] * b[j];
            }
        }
        for (int i = 0; i < a.size() + b.size() - 1; i++)
        {
            c[i] %= MOD;
        }
        return c;
    }
    lg = 0;
    int x = 1;
    while (x < a.size() + b.size() - 1)
        x *= 2, lg++;
    vector<cd> a0(x), b0(x);
    for (int i = 0; i < a.size(); i++)
        a0[i].real(a[i]);
    for (int i = 0; i < b.size(); i++)
        b0[i].real(b[i]);
    a0 = dft(a0, 1);
    b0 = dft(b0, 1);
    for (int i = 0; i < x; i++)
        a0[i] *= b0[i];
    a0 = dft(a0, -1);
    vector<ll> ans(a.size() + b.size() - 1);
    for (int i = 0; i < (int)a.size() + (int)b.size() - 1; i++)
        ans[i] = round(a0[i].real() / x);
    for (int i = 0; i < ans.size(); i++)
        ans[i] %= MOD;
    return ans;
}

vector<ll> substact(vector<ll> a, vector<ll> b)
{
    vector<ll> ans(max(a.size(), b.size()));
    a.resize(ans.size());
    b.resize(ans.size());
    for (int i = 0; i < ans.size(); ++i)
    {
        ans[i] = (a[i] + MOD - b[i]) % MOD;
    }
    return ans;
}

vector<ll> rev(vector<ll> a, ll deg)
{
    vector<ll> b(1);
    ll rev = inq(a[0], MOD - 2);
    b[0] = rev;
    while (b.size() < deg)
    {
        vector<ll> c = a;
        c.resize(b.size() * 2);
        vector<ll> d = fft(b, substact({2}, fft(c, b)));
        d.resize(2 * b.size());
        b = d;
    }
    b.resize(deg);
    return b;
}

int main()
{
    //freopen("divpoly.in", "r", stdin);
    //freopen("divpoly.out", "w", stdout);

    srand(time(NULL));
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n = 50000, m = 2;
    cin >> n;
    vector<ll> a(n + 1);
    for (int i = 0; i <= n; i++) cin >> a[i];
    cin >> m;
    vector<ll> b(m + 1);
    for (int i = 0; i <= m; i++) cin >> b[i];

    if (n < m)
    {
        cout << 0 << " " << 0 << "\n";
        cout << n << " ";
        for (int i = 0; i <= n; i++)
            cout << a[i] << " \n"[i == n];
//        cout << '\n';
        return 0;
    }

    vector<ll> c = rev(b, n - m + 1);
    c = fft(c, a);
    c.resize(n - m + 1);
    cout << c.size() - 1 << " ";
    for (int i = 0; i < c.size(); i++) cout << c[i] << " ";
    cout << "\n";
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    reverse(c.begin(), c.end());
    vector<ll> d = substact(a, fft(b, c));
    while (d.size() > 1 && d.back() == 0)
        d.pop_back();
    cout << d.size() - 1 << " ";
    for (int i = 0; i < d.size(); i++) cout << d[d.size() - i - 1] << " \n"[i + 1 == d.size()];
//    cout << '\n';
}