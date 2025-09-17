///https://codeforces.com/contest/356/problem/A

#include <bits/stdc++.h>

using namespace std;

#define  MAXN  300005

int n, m, L[MAXN], R[MAXN], X[MAXN], st[MAXN * 4], lazy[MAXN * 4];

void down(int id) {
    if(lazy[id] == 0) return;
    st[id * 2] = st[id * 2 + 1] = lazy[id * 2] = lazy[id * 2 + 1] = lazy[id];
    lazy[id] = 0;
}

void update(int id, int l, int r, int u, int v, int val) {
    if(v < l || r < u) return;
    if(u <= l && r <= v) return void(lazy[id] = st[id] = val);
    int mid = r + l >> 1;
    down(id);
    update(id * 2, l, mid, u, v, val);
    update(id * 2 + 1, mid + 1, r, u, v, val);
}

int get(int id, int l, int r, int pos) {
    if(l == r) return st[id];
    int mid = r + l >> 1;
    down(id);
    if(pos <= mid) return get(id * 2, l, mid, pos);
    return get(id * 2 + 1, mid + 1, r, pos);
}

void process(void) {
    cin >> n >> m;
    for(int i = 1; i <= m; i++) cin >> L[i] >> R[i] >> X[i];
    for(int i = m; i >= 1; i--) {
        if(L[i] < X[i]) update(1, 1, n, L[i], X[i] - 1, X[i]);
        if(X[i] < R[i]) update(1, 1, n, X[i] + 1, R[i], X[i]);
    }
    for(int i = 1; i <= n; i++) cout << get(1, 1, n, i) << ' ';
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    process();
    return 0;
}