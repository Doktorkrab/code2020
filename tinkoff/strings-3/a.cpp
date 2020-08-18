#include <bits/stdc++.h>


using namespace std;

const int ALP = 26, MAXN = 2e5 + 7;

struct Node{
	int link = -1, len = 0;
	int go[ALP];
	Node (){
		for (int i = 0; i < ALP; i++)
			go[i] = -1;
	}
};
Node nodes[MAXN];
int cur = 0, n = 0;
string s;
int N;
void add_letter(int pos){
	while (s[pos - 1 - nodes[cur].len] != s[pos])
		cur = nodes[cur].link;
	// cerr << pos << ' ' << cur << ' ' << n << '\n';
	if (nodes[cur].go[s[pos] - 'a'] != -1){
		cur = nodes[cur].go[s[pos] - 'a'];
		return;
	}
	int b = n++;
	nodes[cur].go[s[pos] - 'a'] = b;
	nodes[b].len = nodes[cur].len + 2;
	int cur1 = nodes[cur].link;
	// cur = b;
	while (s[pos - 1 - nodes[cur1].len] != s[pos]){
		// cerr << "!" << cur1 << ' ' << s[pos - 1 - nodes[cur1].len] << '\n';
		cur1 = nodes[cur1].link;
	}
	// cerr << cur1 << ' ' << cur << ' ' << (cur1 == cur ? 1 : cur1) << '\n';
	nodes[b].link = (cur1 == cur ? 1 : nodes[cur1].go[s[pos] - 'a']);
	// cerr << "?" << b << ' ' << nodes[b].link << '\n';
	cur = b;
}
int main(){
	cin >> s;
	N = s.size();
	n = 2;
	nodes[0].len = -1;
	nodes[0].link = 0;
	nodes[1].len = 0;
	nodes[1].link = 0;
	for (int i = 0; i < N; i++){
		add_letter(i);
		cout << n - 2 << " \n"[i + 1 == N];
	}
}