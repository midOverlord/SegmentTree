///https://codeforces.com/gym/105733/problem/H
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e5 + 5;
const int MOD = 998244353;

int n, q;

struct Node {
    int cnt, pref, suff, ans;
} st[MAXN * 4];

Node operator + (const Node& L, const Node& R) {
    if(L.cnt == 0) return R;
    if(R.cnt == 0) return L;
    Node res;
    res.cnt = L.cnt + R.cnt;
    res.pref = (L.pref != 0 ? L.pref : R.pref);
    res.suff = (R.suff != 0 ? R.suff : L.suff);
    int add = ((R.pref - 1) - (L.suff + 1) + 1 + 2);
    res.ans = 1LL * (1LL * L.ans * R.ans % MOD) * add % MOD;
    return res;
}

void build(int id, int l, int r) {
    if(l == r) return void(st[id] = {0, 0, 0, 0});
    int mid = r + l >> 1;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    st[id] = st[id * 2] + st[id * 2 + 1];
}

void update(int id, int l, int r, int pos) {
    if(l == r) {
        if(st[id].cnt == 0) return void(st[id] = {1, pos, pos, 1});
        return void(st[id] = {0, 0, 0, 0});
    }
    int mid = r + l >> 1;
    if(pos <= mid) update(id * 2, l, mid, pos);
    else update(id * 2 + 1, mid + 1, r, pos);
    st[id] = st[id * 2] + st[id * 2 + 1];
}

Node get(int id, int l, int r, int u, int v) {
    if(v < l || r < u) return {0, 0, 0, 0};
    if(u <= l && r <= v) return st[id];
    int mid = r + l >> 1;
    return get(id * 2, l, mid, u, v) + get(id * 2 + 1, mid + 1, r, u, v);
}

void process(void) {
    cin >> n >> q;
    build(1, 1, n);
    for(int i = 1; i <= q; i++) {
        int cmd; cin >> cmd;
        if(cmd == 1) {
            int pos; cin >> pos;
            update(1, 1, n, pos);
        } else {
            int u, v; cin >> u >> v;
            cout << get(1, 1, n, u, v).ans << '\n';
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T; while(T--) process();
    return 0;
}