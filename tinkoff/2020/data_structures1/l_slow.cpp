#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <cmath>
#define ll long long


using namespace std;
const int maxN = 402000;
int a[maxN];

struct node{
    node* l;
    node* r;
    int prior;
    int val;
    int mod;
    int sz;
    node(){
        sz = 0;
        mod = 0;
        prior = (rand() << 16) + rand();
        val = 0;
        l = 0;
        r = 0;
    }
};
node * root[2];

void update(node *a){
    if (!a)
        return;
    int sz = 1;
    if (a->l)
        sz += a->l->sz;
    if (a->r)
        sz += a->r->sz;
    a->sz = sz;
}

void push(node *t){
    if (!t)
        return;
    if (t->mod){
        if (t->l)
            t->l->mod += t->mod;
        if (t->r){
            t->r->mod += t->mod;
        }
        t->val += t->mod;
        t->mod = 0;
    }
}

node* merge(node *L, node* R){
    if (!L){
        return R;
    }
    if (!R){
        return L;
    }
    if (L->prior < R->prior){
        push(L);
        L->r = merge(L->r, R);
        update(L);
        return L;
    }
    else{
        push(R);
        R->l = merge(L, R->l);
        update(R);
        return R;
    }
}

void split(node *t, node *&a, node*& b, int cnt){
    if (!t){
        b = 0;
        a = 0;
        return;
    }
    if (!cnt){
        a = 0;
        b = t;
        update(b);
        return;
    }
    int pp = 0;
    if (t->l)
        pp += t->l->sz;
    push(t);
    if (pp >= cnt){
        split(t->l, a, t->l, cnt);
        b = t;
        update(a);
        update(b);
    }
    else{
        split(t->r, t->r, b, cnt - pp - 1);
        a = t;
        update(a);
        update(b);
    }
}

bool flag = false;

int less_than(node *t, int x){
    int cnt = 0;
    while (t){
        push(t);
        if (t->val == x){
            t = t->r;
            continue;
        }
        if (t->val > x){
            t = t->r;
        }
        else{
            cnt++;
            if (t->r)
                cnt += t->r->sz;
            t = t->l;
        }
    }
    return cnt;

}


node* add(node *t, int len, int p){
    node* a, *b;
    split(t, a, b, len);
    a->mod += p;
    return merge(a, b);
}

int cur = 0;

node* insert(node* t, int x){
    node* tree = t;
    int cnt = 0;
    bool tr = 0;
    cnt = less_than(t, x);
    cnt = t->sz - cnt;
    node* nd = new node;
    nd->val = x;
    nd->sz = 1;
    node *a, *b;
    split(tree, a, b, cnt);
    return merge(merge(a, nd), b);
}

node* rem(node* t, int x){
    node* tree = t;
    int cnt = 0;
    flag = 0;
    while (t){
        push(t);
        if (t->val == x){
            flag = true;
            if (t->l)
                cnt += t->l->sz;
            break;
        }
        if (t->val < x){
            t = t->l;
        }
        else{
            cnt++;
            if (t->l)
                cnt += t->l->sz;
            t = t->r;
        }
    }
    if (!flag)
        return tree;
    node *a, *b, *c, *d;
    split(tree, a, b, cnt + 1);
    split(a, c, d, cnt);
    return merge(c, b);
}

void print(node *t){

    if (!t)
        return;
    push(t);
    if (t->r)
        print(t->r);
    if (t->val != 0){
        cout << t->val << " ";
    }
    if (t->l){
        print(t->l);
    }
}

void precalc(int n){
    sort(a + 1, a + n + 1);
    reverse(a + 1, a + n + 1);
    for (int j = maxN; j >= 1; j--){
        node *nd = new node;
        nd->val = 0;
        nd->sz = 1;
        root[1] = merge(root[1], nd);
    }

    for (int i = 1; i <= n; i++){
        node * nd = new node;
        nd->val = a[i];
        nd->sz = 1;
        root[cur] = merge(root[cur], nd);
        root[1 - cur] = add(root[1 - cur], a[i], 1);
    }
    for (int j = maxN; j >= 1; j--){
        node *nd = new node;
        nd->val = 0;
        nd->sz = 1;
        root[0] = merge(root[0], nd);
    }
}

int main(){
    //freopen("input1.txt", "r", stdin);
    //freopen("output2.txt", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    precalc(n);

    for (int i = 1; i <= m; i++){
        char tp;
        int x;
        cin >> tp;
        if (tp == 'a'){
            cin >> x;
            root[1 - cur] = add(root[1 - cur], x, 1);
            root[cur] = insert(root[cur], x);
        }
        if (tp == 'r'){
            cin >> x;
            root[cur] = rem(root[cur], x);
            if (flag)
                root[1 - cur] = add(root[1 - cur], x, -1);
        }
        if (tp == 'c'){
            cin >> x;
            cout << less_than(root[cur], x + 1) - less_than(root[cur], x) << "\n";
        }
        if (tp == 't'){
            cur = 1 - cur;
        }
    }
    print(root[cur]);

    return 0;
}
