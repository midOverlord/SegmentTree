#include <bits/stdc++.h>

using namespace std;

#define  st  first 
#define  nd  second

const int MAXN = 5e5 + 5e5 + 5e5 + 5;
const int MAXV = 5e5 + 5;

int n, q, a[MAXN], cur[MAXV], lazy[MAXN * 4], qL, qR, N, cntL = 0, cntR = 0;
pair<int, int> st[MAXN * 4];

void down(int id) {
    if(lazy[id] == 0) return;
    st[id * 2].st += lazy[id];
    st[id * 2].nd -= lazy[id];
    st[id * 2 + 1].st += lazy[id];
    st[id * 2 + 1].nd -= lazy[id];
    lazy[id * 2] += lazy[id];
    lazy[id * 2 + 1] += lazy[id];
    lazy[id] = 0;
}

void nodeset(int id, int l, int r, int pos, int k) {
    if(l == r) {
        if(k == 0) st[id] = {0, n - 1};
        else if(k == 1) st[id] = {n - 1, 0};
        else st[id] = {pos - qL, qR - pos};
        lazy[id] = 0;
        return;
    }
    down(id);
    int mid = r + l >> 1;
    if(pos <= mid) nodeset(id * 2, l, mid, pos, k);
    else nodeset(id * 2 + 1, mid + 1, r, pos, k);
}

void update(int id, int l, int r, int u, int v, int val) {
    if(v < u || v < l || r < u) return;
    if(u <= l && r <= v) {
        st[id].st += val; st[id].nd -= val;
        lazy[id] += val;
        return;
    }
    down(id);
    int mid = r + l >> 1;
    update(id * 2, l, mid, u, v, val);
    update(id * 2 + 1, mid + 1, r, u, v, val);
}

pair<int, int> get(int id, int l, int r, int pos) {
    if(l == r) return st[id];
    down(id);
    int mid = r + l >> 1;
    if(pos <= mid) return get(id * 2, l, mid, pos);
    return get(id * 2 + 1, mid + 1, r, pos);
}

void process(void) {
    cin >> n >> q;
    qL = q + 1; qR = q + n; N = q * 2 + n;
    for(int i = qL; i <= qR; i++) cin >> a[i];
    for(int i = qL; i <= qR; i++) cur[a[i]] = i;
    for(int i = qL; i <= qR; i++) nodeset(1, 1, N, i, -1);
    long long ans = 0;
    while(q--) {
        int x; cin >> x;
        char cmd; cin >> cmd;
        pair<int, int> res = get(1, 1, N, cur[x]);
        ans += (min(max(0, res.st), max(0, res.nd)));
        if(cmd == 'l') {
            update(1, 1, N, qL, cur[x] - 1, 1);
            cur[x] = --qL;
            nodeset(1, 1, N, cur[x], 0);
        } else {
            update(1, 1, N, cur[x] + 1, qR, -1);
            cur[x] = ++qR;
            nodeset(1, 1, N, cur[x], 1);
        }
    }
    cout << ans;
}

signed main(void) {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    process();
    return 0;
}