///https://codeforces.com/contest/52/problem/C

#include <bits/stdc++.h>

using namespace std;

#define  MAXN  200005

int n, q, a[MAXN];

long long st[MAXN * 4], lazy[MAXN * 4];

void build(int id, int l, int r) {
    if(l == r) return void(st[id] = a[l]);
    int mid = r + l >> 1;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    st[id] = min(st[id * 2], st[id * 2 + 1]);
}

void down(int id) {
    st[id * 2] += lazy[id];
    lazy[id * 2] += lazy[id];
    st[id * 2 + 1] += lazy[id];
    lazy[id * 2 + 1] += lazy[id];
    lazy[id] = 0;
}

void update(int id, int l, int r, int u, int v, int val) {
    if(v < l || r < u) return;
    if(u <= l && r <= v) {
        lazy[id] += val;
        st[id] += val;
        return;
    }
    int mid = r + l >> 1;
    down(id);
    update(id * 2, l, mid, u, v, val);
    update(id * 2 + 1, mid + 1, r, u, v, val);
    st[id] = min(st[id * 2], st[id * 2 + 1]);
}

long long get(int id, int l, int r, int u, int v) {
    if(v < l || r < u) return LLONG_MAX;
    if(u <= l && r <= v) return st[id];
    int mid = r + l >> 1;
    down(id);
    return min(get(id * 2, l, mid, u, v), get(id * 2 + 1, mid + 1, r, u, v));
}

void process(void) {
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    cin >> q; cin.ignore();
    build(1, 1, n);
    for(int i = 1; i <= q; i++) {
        vector<int> num;
        string str;
        getline(cin, str);
        stringstream tmp(str);
        int val;
        while(tmp >> val) num.push_back(val);
        num[0]++; num[1]++;
        if(num.size() == 2) {
            if(num[0] <= num[1]) cout << get(1, 1, n, num[0], num[1]) << '\n';
            else cout << min(get(1, 1, n, 1, num[1]), get(1, 1, n, num[0], n)) << '\n';
        } else {
            if(num[0] <= num[1]) update(1, 1, n, num[0], num[1], num[2]);
            else {
                update(1, 1, n, 1, num[1], num[2]);
                update(1, 1, n, num[0], n, num[2]);
            }
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    process();
    return 0;
}