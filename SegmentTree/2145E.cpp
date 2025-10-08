///https://codeforces.com/contest/2145/problem/E
#include <bits/stdc++.h>

using namespace std;

#define  ALL(v)  (v).begin(), (v).end()
#define  MASK(i)  (1LL << (i))
#define  BIT(x, i)  (((x) >> (i)) & 1)

const int MAXN = 5e5 + 5;

int n, A, D, a[MAXN], d[MAXN], pref[MAXN], st[MAXN * 4], lazy[MAXN * 4];

void down(int id) {
    if(lazy[id] == 0) return;
    st[id * 2] += lazy[id];
    lazy[id * 2] += lazy[id];
    st[id * 2 + 1] += lazy[id];
    lazy[id * 2 + 1] += lazy[id];
    lazy[id] = 0;
    return;
}

void update(int id, int l, int r, int u, int v, int val) {
    if(v < u || v < l || r < u) return;
    if(u <= l && r <= v) {
        st[id] += val;
        lazy[id] += val;
        return;
    }
    down(id);
    int mid = r + l >> 1;
    update(id * 2, l, mid, u, v, val);
    update(id * 2 + 1, mid + 1, r, u, v, val);
    st[id] = min(st[id * 2], st[id * 2 + 1]);
}

int get(int id, int l, int r) {
    if(l == r) return (st[id] <= 0 ? l : r + 1);
    down(id);
    int mid = r + l >> 1;
    if(st[id * 2] <= 0) return get(id * 2, l, mid);
    return get(id * 2 + 1, mid + 1, r);
}

int f(int x, int y) {
    return max(0, x - A) + max(0, y - D);
}

void process(void) {
    cin >> A >> D >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> d[i];
    for(int i = 1; i <= n; i++) {
        int cur = f(a[i], d[i]);
        if(cur <= n) pref[cur]++;
    }
    for(int i = 1; i <= n; i++) pref[i] += pref[i - 1];
    for(int i = 0; i <= n; i++) update(1, 0, n, i, i, pref[i] - i);
    int m; cin >> m;
    while(m--) {
        int k, na, nd; cin >> k >> na >> nd;
        update(1, 0, n, f(a[k], d[k]), n, -1);
        a[k] = na; d[k] = nd;
        update(1, 0, n, f(a[k], d[k]), n, +1);
        cout << get(1, 0, n) << '\n';
    }
}

signed main(void) {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    process();
    return 0;
}