#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); i++) 

const int MOD = 998244353;
const int N = 500 * 1000 + 13;

string s;

int add(int a, int b){
	a += b;
	if (a >= MOD)
		a -= MOD;
	return a;
}

int mul(int a, int b){
	return a * 1ll * b % MOD;
}

struct node{
	int val[4], len;
};

node merge(const node &a, const node &b, int l, int r){
	node c;
	int na = a.len == 1 ? 0 : 1;
	int nb = b.len == 1 ? 0 : 2;
	c.len = a.len + b.len;
	c.val[0] = mul(a.val[na], b.val[nb]);
	c.val[1] = mul(a.val[na], b.val[3]);
	c.val[2] = mul(a.val[3], b.val[nb]);
	c.val[3] = mul(a.val[3], b.val[3]);
	if (l == 1){
		na = a.len == 1 ? 2 : 0;
		nb = b.len == 1 ? 1 : 0;
		c.val[na + nb] = add(c.val[na + nb], mul(mul(a.val[0], b.val[0]), 19 - (l * 10 + r)));
		c.val[1 + na] = add(c.val[1 + na], mul(mul(a.val[0], b.val[1]), 19 - (l * 10 + r)));
		c.val[2 + nb] = add(c.val[2 + nb], mul(mul(a.val[2], b.val[0]), 19 - (l * 10 + r)));
		c.val[3] = add(c.val[3], mul(mul(a.val[2], b.val[1]), 19 - (l * 10 + r)));
	}
	return c;
}

node t[4 * N];

void build(int v, int l, int r){
	t[v].len = r - l;
	if (l == r - 1){
		t[v].val[0] = 1;
		t[v].val[3] = s[l] + 1;
		return;
	}
	int m = (l + r) / 2;
	build(v * 2, l, m);
	build(v * 2 + 1, m, r);
	t[v] = merge(t[v * 2], t[v * 2 + 1], s[m - 1], s[m]);
}

void upd(int v, int l, int r, int x, int val){
	if (l == r - 1){
		s[l] = val;
		t[v].val[3] = s[l] + 1;
		return;
	}
	int m = (l + r) / 2;
	if (x < m)
		upd(v * 2, l, m, x, val);
	else
		upd(v * 2 + 1, m, r, x, val);
	t[v] = merge(t[v * 2], t[v * 2 + 1], s[m - 1], s[m]);
}

int main(){
	int n, m;

	scanf("%d%d", &n, &m);
	static char buf[N];
	scanf("%s", buf);
	s = buf;
	forn(i, n) s[i] -= '0';
	
	memset(t, 0, sizeof(t));
	build(1, 0, n);
	
	forn(i, m){
		int x, v;
		scanf("%d%d", &x, &v);
		--x;
		upd(1, 0, n, x, v);
		printf("%d\n", t[1].val[3]);
	}
}