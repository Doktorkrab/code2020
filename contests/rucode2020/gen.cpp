#include <bits/stdc++.h>


using namespace std;

#define int long long
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
	int k = rnd() % 1000 + 2;
	int l = rnd() % (k - 1) + 1;
	int cnt = rnd() % ((int)(4e6)) / (k + l) + 1;
	vector<int> kek;
	unordered_set<int> lol;
	while (lol.size() != cnt + 1){
		int nxt = rnd() % ((int) 1e15);
		lol.insert(nxt);
	}
	vector<int> lol1(lol.begin(), lol.end());
	for (int i = 0; i < cnt; i++)
		for (int j = 0; j < k; j++)
			kek.push_back(lol1[i]);
	for (int i = 0; i < l; i++)
		kek.push_back(lol1.back());
	shuffle(kek.begin(), kek.end(), rnd);
	cout << cnt * k + l << '\n';
	for (int i : kek)
		cout << i << ' ';
	cout << '\n';
	cout << "k=" << k << ' ' << "l=" << l << ' ' << "razlichix=" << cnt << '\n';
	cout << lol1.back() << '\n';
}