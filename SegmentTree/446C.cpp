///https://codeforces.com/contest/446/problem/C
#include <bits/stdc++.h>
using namespace std;
#define  ALL(v)  (v).begin(), (v).end()
#define  RALL(v)  (v).rbegin(), (v).rend()
#define  MASK(i)  (1LL << (i))
#define  BIT(x, i)  (((x) >> (i)) & 1)
#define  __Aespa_Giselle__  signed main()

const int MAXN = 3e5 + 5;
const int MOD = 1e9 + 9;

/// add l -> r : first = x, second = y
/// x, y, x + y, x + 2y, 2x + 3y, 3x + 5y, 5x + 8y, ...
/// x : 1, 0, 1, 1, 2, 3, 5, ... -> (1 + f[1] + ... + f[len - 2])
/// y : 0, 1, 1, 2, 3, 5, 8, ... -> (f[1] + ... + f[len - 1])
/// -> add = x * (f[len]) + y * (f[len + 1] - 1)
/// left:
///      first = x,
///      second = y
/// right: 
///      first = x * f[len_left - 1] + y * f[len_left], 
///      second = x * f[len_left] + y * f[len_left + 1]

int n, m, a[MAXN], fibo[MAXN], st[MAXN * 4], lazy[MAXN * 4][2];

void build(int id, int l, int r) {
    if(l == r) return void(st[id] = a[l]);
    int mid = r + l >> 1;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    st[id] = (st[id * 2] + st[id * 2 + 1]) % MOD;
}

void apply(int id, int l, int r, int x, int y) {
    int len = r - l + 1;
    st[id] = (st[id] + (1LL * x * (fibo[len]) % MOD) + (1LL * y * (MOD + fibo[len + 1] - 1) % MOD)) % MOD;
    lazy[id][0] = (lazy[id][0] + x) % MOD;
    lazy[id][1] = (lazy[id][1] + y) % MOD;
} 

void down(int id, int l, int r) {
    int mid = r + l >> 1;
    int x_left = lazy[id][0];
    int y_left = lazy[id][1];
    apply(id * 2, l, mid, x_left, y_left);
    int len_left = mid - l + 1;
    int x_right = ((1LL * lazy[id][0] * fibo[len_left - 1] % MOD) + (1LL * lazy[id][1] * fibo[len_left] % MOD)) % MOD;
    int y_right = ((1LL * lazy[id][0] * fibo[len_left] % MOD) + (1LL * lazy[id][1] * fibo[len_left + 1] % MOD)) % MOD;
    apply(id * 2 + 1, mid + 1, r, x_right, y_right);
    lazy[id][0] = 0; lazy[id][1] = 0;
}

void update(int id, int l, int r, int u, int v) {
    if(v < l || r < u) return;
    if(u <= l && r <= v) {
        apply(id, l, r, fibo[l - u + 1], fibo[l - u + 2]);
        return;
    }
    down(id, l, r);
    int mid = r + l >> 1;
    update(id * 2, l, mid, u, v);
    update(id * 2 + 1, mid + 1, r, u, v);
    st[id] = (st[id * 2] + st[id * 2 + 1]) % MOD;
}

int get(int id, int l, int r, int u, int v) {
    if(v < l || r < u) return 0;
    if(u <= l && r <= v) return st[id];
    down(id, l, r);
    int mid = r + l >> 1;
    return (get(id * 2, l, mid, u, v) + get(id * 2 + 1, mid + 1, r, u, v)) % MOD;
}

void WONDERFUL() {
    cin >> n >> m;
    fibo[1] = 1; fibo[2] = 1;
    for(int i = 3; i <= n + 2; i++) fibo[i] = (fibo[i - 1] + fibo[i - 2]) % MOD;
    for(int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);
    while(m--) {
        int cmd, u, v; cin >> cmd >> u >> v;
        if(cmd == 1) {
            update(1, 1, n, u, v);
        } else {
            cout << get(1, 1, n, u, v) << '\n';
        }
    }
}

__Aespa_Giselle__ {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ///int T; cin >> T; while(T--) 
    WONDERFUL();
    return 0;
}