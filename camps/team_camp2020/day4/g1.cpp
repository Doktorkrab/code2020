#ifdef DBG1
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <cassert>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

#ifdef DBG1
#define dbg(...) fprintf(stderr, __VA_ARGS__)
#else
#define dbg(...)
#endif

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair <int, int> pii;

#ifdef DBG1
#define EMULATE 1
#else
#define EMULATE 0
#endif

ll TOTAL = ll(1e9) * ll(1e9);
ll N;
ll x;
int k;

#if EMULATE
vector <ll> dels;
ll shift;

void readTest() {
  dels.resize(k);
  for (int i = 0; i < k; ++i) {
    scanf("%lld", &dels[i]);
  }
  scanf("%lld", &shift);
}

ll getElement(ll v) {
	v += shift;
	if (v > N) {
		v -= N;
  }
	for (int i = 0; i < k; ++i) {
		if (dels[i] <= v) {
			++v;
    }
  }
  dbg("pos2val returns %lld\n", v);
	return v;
}
#endif

void answer(ll v) {
#if EMULATE
    assert(getElement(v) == ::x);
#endif
    printf("! %lld\n", v);
    fflush(stdout);
    exit(0);
}

void answerNoSolution() {
#if EMULATE
    assert(binary_search(dels.begin(), dels.end(), ::x));
#endif
    printf("! -1\n");
    fflush(stdout);
    exit(0);
}

ll check(ll v) {
    static int query = 0;
    ++query;
    assert(query <= 10);
    assert(1 <= v && v <= N);
    printf("? %lld\n", v);
    fflush(stdout);
    ll x;
#if EMULATE
    x = getElement(v);
#else
    scanf("%lld", &x);
#endif
    assert(1 <= x && x <= TOTAL);
    if (x == ::x) {
        answer(v);
    }
    return x;
}

int main() {
    scanf("%lld%d", &x, &k);
    N = TOTAL - k;
    dbg("N %lld\n", N);
#if EMULATE
    readTest();
#endif
    ll first = check(N);
    ll Lx = x - 3 * k;
    ll Rx = x + 3 * k;
    ll Rv = ((x >= first) ? (x - first) : (TOTAL + x - first));
    ll Lv = Rv - k;
    dbg("Lx %lld Rx %lld\n", Lx, Rx);
    while (Lv <= Rv) {
        ll Mv = Lv + (Rv - Lv) / 2;
        ll Mv2 = Mv % N;
        if (Mv2 <= 0) { Mv2 += N; }
        dbg("Lv %lld Rv %lld Mv %lld Mv2 %lld\n", Lv, Rv, Mv, Mv2);
        ll Mx = check(Mv2);
        if (Mx < Lx) {
            Mx += TOTAL;
        }
        if (Mx > Rx) {
            Mx -= TOTAL;
        }
        assert(Lx <= Mx && Mx <= Rx);
        if (Mx < x) {
            Lv = Mv + 1;
        } else if (Mx > x) {
            Rv = Mv - 1;
        } else {
            assert(0);
        }
    }
    answerNoSolution();

    return 0;
}
