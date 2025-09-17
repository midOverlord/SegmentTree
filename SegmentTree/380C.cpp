///https://codeforces.com/contest/380/problem/C

#include <bits/stdc++.h>

using namespace std;

#define  MAXN  1000006

struct Node {
    int open, close, opt;
} st[MAXN * 4];

string s;

int n, q;

Node operator + (const Node& left, const Node& right) {
    Node res = {0, 0, 0};
    int tmp = min(left.open, right.close);
    res.open = left.open - tmp + right.open;
    res.close = left.close + right.close - tmp;
    res.opt = left.opt + right.opt + tmp * 2;
    return res;
}

void build(int id, int l, int r) {
    if(l == r) {
        if(s[l] == '(') st[id] = {1, 0, 0};
        else st[id] = {0, 1, 0};
        return;
    }
    int mid = r + l >> 1;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    st[id] = st[id * 2] + st[id * 2 + 1];
}

Node get(int id, int l, int r, int u, int v) {
    if(v < l || r < u) return {0, 0, 0};
    if(u <= l && r <= v) return st[id];
    int mid = r + l >> 1;
    return get(id * 2, l, mid, u, v) + get(id * 2 + 1, mid + 1, r, u, v);
}

void process(void) {
    cin >> s;
    int n = s.size();
    s = '.' + s;
    cin >> q;
    build(1, 1, n); 
    for(int i = 1; i <= q; i++) {
        int u, v; cin >> u >> v;
        Node cur = get(1, 1, n, u, v);
        cout << cur.opt << '\n';
    }
}

int main(void) {
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    process();
    return 0;
}