#include <bits/stdc++.h>
#define file(a) freopen(#a".in", "r", stdin), freopen(#a".out", "w", stdout)
//#define int long long
using namespace std;

const int N = 1e6 + 5;

int n, m, l, r, t, B;
int qcnt, ccnt, ans;
int a[N], res[N], cnt[N];

char op;

struct node{
	int l, r, lst, id;
}q[N], c[N];

void add(int x, int f = 0){
	x = f ? x : a[x];
	if (!cnt[x]) ans++;
	cnt[x]++;
}

void del(int x, int f = 0){
	x = f ? x : a[x], cnt[x]--;
	if (!cnt[x]) ans--;
}

void upt(int k, int x){
	int L = q[k].l, R = q[k].r, idx = c[x].l, to = c[x].r;
	if (L <= idx && idx <= R){
		del(idx);
		add(to, 1);
	}
	swap(a[idx], to);
}

signed main(){
	
	ios::sync_with_stdio(0); cin.tie(0);
	
	cin >> n >> m; B = pow(n, 0.666);
	
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	
	for (int i = 1, x, y; i <= m; i++){
		cin >> op >> x >> y;
		if (op == 'Q') q[++qcnt] = {x, y, ccnt, qcnt};
		else c[++ccnt] = {x, y, 0, ccnt};
	}
	
	sort(q + 1, q + 1 + qcnt, [](node a, node b){
		return a.l / B == b.l / B ? (a.r / B == b.r / B ? a.lst < b.lst : a.r < b.r) : a.l < b.l;
	}); l = 1;
	
	for (int i = 1; i <= qcnt; i++){
		while(l < q[i].l) del(l++);
		while(l > q[i].l) add(--l);
		while(r < q[i].r) add(++r);
		while(r > q[i].r) del(r--);
		while(t < q[i].lst) upt(i, ++t);
		while(t > q[i].lst) upt(i, t--);
		res[q[i].id] = ans;
	}
	
	for (int i = 1; i <= qcnt; i++)
		cout << res[i] << endl;
	
	return 0;
}
