///https://www.spoj.com/problems/KQUERY/

#include <bits/stdc++.h>

using namespace std;

#define  MAXN  30004
#define  MAXQ  200005

struct query {
    int u, v, k, p;
} q[MAXQ];

bool operator < (const query& a, const query& b) {
    return a.k < b.k;
}

struct num {
    int v, id;
} tmp[MAXN];

bool operator < (const num& a, num& b) {
    return a.v < b.v;
}

int N, Q, a[MAXN], st[MAXN * 4];

void build(int id, int l, int r) {
    if(l == r) return void(st[id] = 1);
    int mid = r + l >> 1;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    st[id] = st[id * 2] + st[id * 2 + 1];
}

void update(int id, int l, int r, int pos, int val) {
    if(pos < l || r < pos) return;
    if(l == r) return void(st[id] = val);
    int mid = r + l >> 1;
    update(id * 2, l, mid, pos, val);
    update(id * 2 + 1, mid + 1, r, pos, val);
    st[id] = st[id * 2] + st[id * 2 + 1];
}

int get(int id, int l, int r, int u, int v) {
    if(v < l || r < u) return 0;
    if(u <= l && r <= v) return st[id];
    int mid = r + l >> 1;
    return get(id * 2, l, mid, u, v) + get(id * 2 + 1, mid + 1, r, u, v);
}

int ans[MAXQ];

void process(void) {
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> a[i];
        tmp[i].v = a[i];
        tmp[i].id = i;
    }
    sort(tmp + 1, tmp + N + 1);
    cin >> Q;
    for(int i = 1; i <= Q; i++) {
        cin >> q[i].u >> q[i].v >> q[i].k;
        q[i].p = i;
    }
    sort(q + 1, q + Q + 1);
    build(1, 1, N);
    int cur = 1;
    for(int i = 1; i <= Q; i++) {
        while(cur <= N && a[tmp[cur].id] <= q[i].k) {
            update(1, 1, N, tmp[cur].id, 0);
            cur++;
        }
        ans[q[i].p] = get(1, 1, N, q[i].u, q[i].v);
    }
    for(int i = 1; i <= Q; i++) cout << ans[i] << '\n';
}

int main(void) {
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    process();
    return 0;
}