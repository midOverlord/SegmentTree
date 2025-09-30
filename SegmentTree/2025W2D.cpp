#include <bits/stdc++.h>

using namespace std;

#define  MAXN  500005

struct Node {
    int pfx, sfx, free;
} st[MAXN * 4];

int n, m, lazy[MAXN * 4];

Node Merge(Node& left, Node& right, int l, int r, int mid) {
    Node res;
    res.pfx = left.pfx == mid - l + 1 ? left.pfx + right.pfx : left.pfx;
    res.sfx = right.sfx == r - (mid + 1) + 1 ? right.sfx + left.sfx : right.sfx;
    res.free = max({left.free, right.free, left.sfx + right.pfx});
    return res;
}

void build(int id, int l, int r) {
    lazy[id] = -1;
    if(l == r) return void(st[id] = {1, 1, 1});
    int mid = r + l >> 1;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    st[id] = Merge(st[id * 2], st[id * 2 + 1], l, r, mid);
}

void down(int id, int l, int r, int mid) {
    if(lazy[id] == -1) return;
    if(lazy[id]) {
        st[id * 2] = {mid - l + 1, mid - l + 1, mid - l + 1};
        st[id * 2 + 1] = {r - (mid + 1) + 1, r - (mid + 1) + 1, r - (mid + 1) + 1};
    } else {
        st[id * 2] = {0, 0, 0};
        st[id * 2 + 1] = {0, 0, 0};
    }
    lazy[id * 2] = lazy[id];
    lazy[id * 2 + 1] = lazy[id];
    lazy[id] = -1;
}

void update(int id, int l, int r, int u, int v, int k) {
    if(v < l || r < u) return;
    if(u <= l && r <= v) {
        lazy[id] = k;
        if(lazy[id]) st[id] = {r - l + 1, r - l + 1, r - l + 1};
        else st[id] = {0, 0, 0};
        return;
    }
    int mid = r + l >> 1;
    down(id, l, r, mid);
    update(id * 2, l, mid, u, v, k);
    update(id * 2 + 1, mid + 1, r, u, v, k);
    st[id] = Merge(st[id * 2], st[id * 2 + 1], l, r, mid);
}

int get(int id, int l, int r, int k) {
    if(st[id].free < k) return -1;
    int mid = r + l >> 1;
    down(id, l, r, mid);
    if(st[id * 2].free >= k) return get(id * 2, l, mid, k);
    if(st[id * 2].sfx + st[id * 2 + 1].pfx >= k) return mid - st[id * 2].sfx + 1;
    return get(id * 2 + 1, mid + 1, r, k);
}

void process(void) {
    cin >> n >> m;
    build(1, 1, n);
    int ans = 0;
    for(int t = 1; t <= m; t++) {
        char cmd; cin >> cmd;
        if(cmd == 'A') {
            int k; cin >> k;
            int pos = get(1, 1, n, k);
            if(pos == -1) ans++;
            else update(1, 1, n, pos, pos + k - 1, 0);
        } else {
            int u, v; cin >> u >> v;
            update(1, 1, n, u, v, 1);
        }
    }
    cout << ans;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    process();
    return 0;
}