///https://codeforces.com/problemset/problem/914/D
#include <bits/stdc++.h>
using namespace std;
#define  ALL(v)  (v).begin(), (v).end()
#define  RALL(v)  (v).rbegin(), (v).rend()
#define  MASK(i)  (1LL << (i))
#define  BIT(x, i)  (((x) >> (i)) & 1)
#define  __Aespa_Giselle__  signed main()

const int MAXN = 5e5 + 5;

int n, q, a[MAXN], st[MAXN * 4];

void build(int id, int l, int r) {
    if(l == r) return void(st[id] = a[l]);
    int mid = r + l >> 1;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    st[id] = __gcd(st[id * 2], st[id * 2 + 1]);
}

void update(int id, int l, int r, int pos, int val) {
    if(l == r) return void(st[id] = val);
    int mid = r + l >> 1;
    if(pos <= mid) update(id * 2, l, mid, pos, val);
    else update(id * 2 + 1, mid + 1, r, pos, val);
    st[id] = __gcd(st[id * 2], st[id * 2 + 1]);
}

struct Node {
    int id, l, r;
};

vector<Node> not_divisible;

void get(int id, int l, int r, int u, int v, int x) {
    if(v < l || r < u) return;
    if(u <= l && r <= v) {
        if(st[id] % x != 0) not_divisible.push_back({id, l, r});
        return;
    }
    int mid = r + l >> 1;
    get(id * 2, l, mid, u, v, x);
    get(id * 2 + 1, mid + 1, r, u, v, x);
}

bool check(int id, int l, int r, int x) {
    if(l == r) return true;
    int mid = r + l >> 1;
    if(st[id * 2] % x != 0) {
        if(st[id * 2 + 1] % x != 0) return false;
        return check(id * 2, l, mid, x);
    }
    return check(id * 2 + 1, mid + 1, r, x);
}

void guess(int u, int v, int x) {
    not_divisible.clear();
    get(1, 1, n, u, v, x);
    if(not_divisible.size() >= 2) cout << "NO" << '\n';
    else if(not_divisible.size() == 0) cout << "YES" << '\n';
    else {
        auto node = not_divisible[0];
        if(check(node.id, node.l, node.r, x)) cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }
}

void WONDERFUL() {
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);
    cin >> q;
    while(q--) {
        int cmd; cin >> cmd;
        if(cmd == 1) {
            int u, v, x; cin >> u >> v >> x;
            guess(u, v, x);
        } else {
            int pos, val; cin >> pos >> val;
            update(1, 1, n, pos, val);
        }
    }
}

__Aespa_Giselle__ {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ///int T; cin >> T; while(T--) 
    WONDERFUL();
    return 0;
}
