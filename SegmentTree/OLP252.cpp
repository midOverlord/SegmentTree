#include <bits/stdc++.h>
using namespace std;
#define  ALL(v)  (v).begin(), (v).end()
#define  RALL(v)  (v).rbegin(), (v).rend()
#define  MASK(i)  (1LL << (i))
#define  BIT(x, i)  (((x) >> (i)) & 1)
#define  __Aespa_Giselle__  signed main()

const int MAXN = 2e5 + 5;
const int MOD = 998244353;

int n, q, a[MAXN], b[MAXN], c[MAXN], st[MAXN * 4], lazy[MAXN * 4][2];

int calc(int l, int r) {
    return (1LL * (r + l) * (r - l + 1) / 2) % MOD;
}

void build(int id, int l, int r) {
    if(l == r) return void(st[id] = c[l]);
    int mid = r + l >> 1;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    st[id] = (st[id * 2] + st[id * 2 + 1]) % MOD;
}

void fix(int id, int l, int r) {
    int Ladder = lazy[id][0];
    int Const = lazy[id][1];
    st[id] = (st[id] + (1LL * Ladder * calc(l, r) % MOD)) % MOD;
    st[id] = (st[id] + (1LL * Const * (r - l + 1) % MOD)) % MOD;
    if(l != r) {
        lazy[id * 2][0] = (lazy[id * 2][0] + Ladder) % MOD;
        lazy[id * 2][1] = (lazy[id * 2][1] + Const) % MOD;
        lazy[id * 2 + 1][0] = (lazy[id * 2 + 1][0] + Ladder) % MOD;
        lazy[id * 2 + 1][1] = (lazy[id * 2 + 1][1] + Const) % MOD;
    }
    lazy[id][0] = 0; lazy[id][1] = 0;
}

void update(int id, int l, int r, int u, int v, int diff) {
    fix(id, l, r);
    if(v < l || r < u) return;
    if(u <= l && r <= v) {
        lazy[id][0] = diff;
        lazy[id][1] = (MOD - (1LL * (u - 1) * diff % MOD)) % MOD;
        fix(id, l, r);
        return;
    }
    int mid = r + l >> 1;
    update(id * 2, l, mid, u, v, diff);
    update(id * 2 + 1, mid + 1, r, u, v, diff);
    st[id] = (st[id * 2] + st[id * 2 + 1]) % MOD;
}

int get(int id, int l, int r, int u, int v) {
    fix(id, l, r);
    if(v < l || r < u) return 0;
    if(u <= l && r <= v) return st[id];
    int mid = r + l >> 1;
    return (get(id * 2, l, mid, u, v) + get(id * 2 + 1, mid + 1, r, u, v)) % MOD;
}

void WONDERFUL() {
    cin >> n >> q;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) {
        b[i] = (b[i - 1] + a[i]) % MOD;
        c[i] = (c[i - 1] + b[i]) % MOD;
    }
    build(1, 1, n);
    while(q--) {
        int cmd; cin >> cmd;
        if(cmd == 1) {
            int pos, val; cin >> pos >> val;
            update(1, 1, n, pos, n, (1LL * val - a[pos] + MOD) % MOD);
            a[pos] = val;
        } else {
            int x; cin >> x;
            cout << get(1, 1, n, 1, x) << '\n';
        }
    }
}

__Aespa_Giselle__ {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ///int T; cin >> T; while(T--)
    WONDERFUL();
    return 0;
}
