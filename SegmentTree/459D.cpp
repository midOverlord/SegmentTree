///https://codeforces.com/contest/459/problem/D

#include <bits/stdc++.h>

using namespace std;

#define  MAXN  1000006

int n, a[MAXN], cnt[MAXN], rem[MAXN], st[MAXN * 4];

void update(int id, int l, int r, int pos, int val) {
    if(l == r) return void(st[id] += val);
    int mid = r + l >> 1;
    if(pos <= mid) update(id * 2, l, mid, pos, val);
    else update(id * 2 + 1, mid + 1, r, pos, val);
    st[id] = st[id * 2] + st[id * 2 + 1];
}

long long get(int id, int l, int r, int u, int v) {
    if(v < l || r < u) return 0;
    if(u <= l && r <= v) return st[id];
    int mid = r + l >> 1;
    return get(id * 2, l, mid, u, v) + get(id * 2 + 1, mid + 1, r, u, v); 
}

vector<int> tmp;

void process(void) {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        tmp.push_back(a[i]);
    }
    sort(tmp.begin(), tmp.end());
    tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
    for(int i = 1; i <= n; i++) a[i] = lower_bound(tmp.begin(), tmp.end(), a[i]) - tmp.begin() + 1;
    for(int i = n; i >= 1; i--) {
        rem[i] = ++cnt[a[i]];
        update(1, 1, n, rem[i], +1);
    }
    memset(cnt, 0, sizeof cnt);
    long long ans = 0;
    for(int i = 1; i <= n; i++) {
        update(1, 1, n, rem[i], -1);
        ans += get(1, 1, n, 1, ++cnt[a[i]] - 1);
    }
    cout << ans;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    process();
    return 0;
}