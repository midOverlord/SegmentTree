///https://codeforces.com/contest/558/problem/E

#include <bits/stdc++.h>

using namespace std;

#define  MAXN  100005

int n, q, st[26][MAXN * 4], lazy[26][MAXN * 4], cnt[26];

string s;

void build(int id, int l, int r) {
    if(l == r) return void(st[s[l - 1] - 'a'][id] = 1);
    int mid = r + l >> 1;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    for(int ch = 0; ch <= 25; ch++) st[ch][id] = st[ch][id * 2] + st[ch][id * 2 + 1];
}

void down(int ch, int id, int l, int r, int mid) {
    if(lazy[ch][id] == -1) return;
    st[ch][id * 2] = lazy[ch][id] * (mid - l + 1);
    lazy[ch][id * 2] = lazy[ch][id];
    st[ch][id * 2 + 1] = lazy[ch][id] * (r - (mid + 1) + 1);
    lazy[ch][id * 2 + 1] = lazy[ch][id];
    lazy[ch][id] = -1;
}

void update(int ch, int id, int l, int r, int u, int v, int val) {
    if(v < l || r < u) return;
    if(u <= l && r <= v) {
        lazy[ch][id] = val;
        st[ch][id] = val * (r - l + 1);
        return;
    }
    int mid = r + l >> 1;
    down(ch, id, l, r, mid);
    update(ch, id * 2, l, mid, u, v, val);
    update(ch, id * 2 + 1, mid + 1, r, u, v, val);
    st[ch][id] = st[ch][id * 2] + st[ch][id * 2 + 1];
}

int get(int ch, int id, int l, int r, int u, int v) {
    if(v < l || r < u) return 0;
    if(u <= l && r <= v) return st[ch][id];
    int mid = r + l >> 1;
    down(ch, id, l, r, mid);
    return get(ch, id * 2, l, mid, u, v) + get(ch, id * 2 + 1, mid + 1, r, u, v);
}

void process(void) {
    cin >> n >> q >> s;
    memset(lazy, -1, sizeof lazy);
    build(1, 1, n);
    for(int i = 1; i <= q; i++) {
        int u, v, k; cin >> u >> v >> k;
        for(int ch = 0; ch <= 25; ch++) {
            cnt[ch] = get(ch, 1, 1, n, u, v);
            if(cnt[ch]) update(ch, 1, 1, n, u, v, 0);
        }
        int ch = (k ? 0 : 25);
        while(0 <= ch && ch <= 25) {
            if(cnt[ch]) {
                update(ch, 1, 1, n, u, u + cnt[ch] - 1, 1);
                u += cnt[ch];
            }
            ch += (k ? +1 : -1);
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int ch = 0; ch <= 25; ch++) {
            if(get(ch, 1, 1, n, i, i)) {
                cout << char(ch + 'a');
            }
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    process();
    return 0;
}