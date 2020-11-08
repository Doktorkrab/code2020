#ifdef LOCAL
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#else
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#endif

#include <bits/stdc++.h>
#include <immintrin.h>

using namespace std;
using ll = long long;#ifdef LOCAL
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#else
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#endif



#define SZ(x) (int)((x).size())
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()

#define TMAX(type) numeric_limits<type>::max()
#define TMIN(type) numeric_limits<type>::min()

unsigned GetMin(const unsigned *a, int n) {
    __m256i min_avx = _mm256_set1_epi32(TMAX(unsigned));
    int i = 0;
    for (; i + 8 <= n; i += 8) {
        __m256i cur_block_a = _mm256_lddqu_si256(reinterpret_cast<const __m256i *>(a + i));
        min_avx = _mm256_min_epu32(min_avx, cur_block_a);
    }
    unsigned mn = TMAX(unsigned);
    for (; i < n; i++)
        mn = min(mn, a[i]);
    auto *mins = (unsigned *) &min_avx;
    for (i = 0; i < 8; i++) {
        mn = min(mn, mins[i]);
    }
    return mn;
}

void AddProg(unsigned *a, int n, unsigned k) {
    __m256i cur_add = _mm256_set_epi32(8 * k, 7 * k, 6 * k, 5 * k, 4 * k, 3 * k, 2 * k, 1 * k);
    __m256i add_k = _mm256_set1_epi32(8 * k);
    const __m256i mask = _mm256_set1_epi32(TMAX(unsigned));
    int i = 0;
    for (; i + 8 <= n; i += 8) {
        __m256i cur_block_a = _mm256_lddqu_si256(reinterpret_cast<const __m256i *>(a + i));
        cur_block_a = _mm256_add_epi32(cur_block_a, cur_add);
        _mm256_maskstore_epi32(reinterpret_cast< int *>(a + i), mask, cur_block_a);
        cur_add = _mm256_add_epi32(cur_add, add_k);
    }
//    unsigned *adds = (unsigned *) &cur_add;
    for (; i < n; i++) {
        a[i] += (i + 1) * k;
    }
}

#ifdef LOCAL

int main() {
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    unsigned *a, *b, *c;
    const int MAXN = 1000;
//    const int MAXC = 20;
    while(true){
        int n = rnd() % MAXN + 1;
        a = new unsigned[n];
        for (int i = 0; i < n; i++)
            a[i] = rnd() /*% MAXC*/;
        b = new unsigned[n];
        c = new unsigned[n];

        copy(a, a + n, b);
        copy(a, a + n, c);
        unsigned k = rnd() /*% MAXC*/;
        for (unsigned i = 0; i < n; i++)
            b[i] += (i + 1) * k;
        AddProg(a, n, k);
        bool good = true;
        for (int i = 0; i < n; i++){
            if (a[i] != b[i]){
                cout << "\nbad add\n";
                good = false;
            }
        }
        if (*min_element(c, c + n) != GetMin(c, n)){
            cout << "\nbad min\n";
            good = false;
        }
        if (!good){
            for (int i = 0; i < n; i++)
                cout << c[i] << " \n"[i + 1 == n];
            cout << n << ' ' << k << '\n';
            break;
        }
        cout << ".";

    }
//    unsigned arr[] = {9, 19, 14, 9, 15, 8, 2, 5};
//    GetMin(arr, 8);
}

#endif