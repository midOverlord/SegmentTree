///https://codeforces.com/contest/145/problem/E

#include <bits/stdc++.h>

using namespace std;

#define  MAXN  1000006

int n, q, lazy[MAXN * 4];

char a[MAXN];

struct Node {
    int num4, num7, inc, dec;
} st[MAXN * 4];

Node operator + (const Node& left, const Node& right) {
    Node res;
    res.num4 = left.num4 + right.num4;
    res.num7 = left.num7 + right.num7;
    res.inc = max(left.num4 + right.inc, left.inc + right.num7);
    res.dec = max(left.dec + right.num4, left.num7 + right.dec);
    return res;
}

void build(int id, int l, int r) {
    if(l == r) {
        if(a[l] == '4') st[id] = {1, 0, 1, 1};
        if(a[l] == '7') st[id] = {0, 1, 1, 1};
        return;
    }
    int mid = r + l >> 1;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    st[id] = st[id * 2] + st[id * 2 + 1];
}

void sw(int id) {
    swap(st[id].num4, st[id].num7);
    swap(st[id].inc, st[id].dec);
}

void down(int id) {
    if(lazy[id] == 0) return;
    sw(id * 2);
    lazy[id * 2] = 1 ^ lazy[id * 2];
    sw(id * 2 + 1);
    lazy[id * 2 + 1] = 1 ^ lazy[id * 2 + 1];
    lazy[id] = 0;
}

void update(int id, int l, int r, int u, int v) {
    if(v < l || r < u) return;
    if(u <= l && r <= v) {
        lazy[id] = 1 ^ lazy[id];
        sw(id);
        return;
    }
    int mid = r + l >> 1;
    down(id);
    update(id * 2, l, mid, u, v);
    update(id * 2 + 1, mid + 1, r, u, v);
    st[id] = st[id * 2] + st[id * 2 + 1];
}

void process(void) {
    cin >> n >> q;
    for(int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);
    for(int i = 1; i <= q; i++) {
        string cmd; cin >> cmd;
        if(cmd.size() == 5) cout << st[1].inc << '\n';
        else {
            int u, v; cin >> u >> v;
            update(1, 1, n, u, v);
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    process();
    return 0;
}