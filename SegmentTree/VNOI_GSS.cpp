///https://oj.vnoi.info/problem/gss

#include <bits/stdc++.h>

using namespace std;

#define  MAXN  50004

const int INF = 1e9;

int n, q, a[MAXN];

struct Node {
    int pre, suf, sum, maxsum;
} st[MAXN * 4];

Node operator + (const Node& left, const Node& right) {
    Node res;
    res.pre = max(left.pre, left.sum + right.pre);
    res.suf = max(right.suf, right.sum + left.suf);
    res.sum = left.sum + right.sum;
    res.maxsum = max({left.maxsum, right.maxsum, left.suf + right.pre});
    return res;
}

void build(int id, int l, int r) {
    if(l == r) {
        st[id].pre = st[id].suf = st[id].sum = a[l];
        st[id].maxsum = a[l];
        return;
    }
    int mid = r + l >> 1;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    st[id] = st[id * 2] + st[id * 2 + 1];
}

Node get(int id, int l, int r, int u, int v) {
    if(v < l || r < u) return {-INF, -INF, 0, -INF};
    if(u <= l && r <= v) return st[id];
    int mid = r + l >> 1;
    return get(id * 2, l, mid, u, v) + get(id * 2 + 1, mid + 1, r, u, v);
}

void process(void) {
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    cin >> q;
    build(1, 1, n);
    for(int i = 1; i <= q; i++) {
        int u, v; cin >> u >> v;
        Node ans = get(1, 1, n, u, v);
        cout << ans.maxsum << '\n';
    }
}

int main(void) {
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    process();
    return 0;
}