///https://codeforces.com/contest/339/problem/D

#include <bits/stdc++.h>

using namespace std;

#define  MAXN  140005

int n, m, a[MAXN];

struct Node {
    int v, iter;
} st[MAXN * 4];

Node operator + (const Node& left, const Node& right) {
    Node res;
    if(left.iter) res.v = (left.v | right.v);
    else res.v = (left.v ^ right.v);
    res.iter = (1 ^ left.iter);
    return res;
}

void build(int id, int l, int r) {
    if(l == r) return void(st[id] = {a[l], 1});
    int mid = r + l >> 1;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    st[id] = st[id * 2] + st[id * 2 + 1];
}

void update(int id, int l, int r, int pos, int val) {
    if(pos < l || r < pos) return;
    if(l == r) return void(st[id] = {val, 1});
    int mid = r + l >> 1;
    update(id * 2, l, mid, pos, val);
    update(id * 2 + 1, mid + 1, r, pos, val);
    st[id] = st[id * 2] + st[id * 2 + 1];
}

void process(void) {
    cin >> n >> m;
    int N = (1 << n);
    for(int i = 1; i <= N; i++) cin >> a[i];
    build(1, 1, N);
    for(int i = 1; i <= m; i++) {
        int pos, val; cin >> pos >> val;
        update(1, 1, N, pos, val);
        cout << st[1].v << '\n';
    }
}

int main(void) {
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    process();
    return 0;
}