struct Node{
	ll k, n, l, r;
	ll intersect(Node a){
		if(k == a.k) return -1e18;
		return (a.n - n) / (k - a.k);
	}
	
	ll get(ll x){
		return k * x + n;
	}
};

struct LiChao{
	vector<Node> v;
	int size;
	void init(ll k, ll n){
		v.push_back({k, n, -1, -1});
	}
	void set(int x, ll lx, ll rx, ll k, ll n){
		Node nw = {k, n, -1, -1};
		ll ins = v[x].intersect(nw);
		if(ins < lx || ins >= rx || rx - lx == 1){
			if(v[x].get(lx) > nw.get(lx)){
				v[x].k = k;
				v[x].n = n;
			}
			return;
		}
		ll m = (lx + rx) / 2;
		if(ins < m){
			ll nwk, nwn;
			if(v[x].get(m) > nw.get(m)){
				nwk = v[x].k;
				nwn = v[x].n;
				v[x].k = k;
				v[x].n = n;
			}else{
				nwk = k;
				nwn = n;
			}
			if(v[x].l == -1){
				v[x].l = (int)v.size();
				v.push_back({nwk, nwn, -1, -1});
			}else{
				set(v[x].l, lx, m, nwk, nwn);
			}
		}else{
			ll nwk, nwn;
			if(v[x].get(m-1) > nw.get(m-1)){
				nwk = v[x].k;
				nwn = v[x].n;
				v[x].k = k;
				v[x].n = n;
			}else{
				nwk = k;
				nwn = n;
			}
			if(v[x].r == -1){
				v[x].r = (int)v.size();
				v.push_back({nwk, nwn, -1, -1});
			}else{
				set(v[x].r, m, rx, nwk, nwn);
			}
		}
	}
	
	void set(ll k, ll n){
		set(0, -(1ll << 30), (1ll << 30), k, n);
	}
	
	ll calc(int x, ll lx, ll rx, ll i){
		if(rx - lx == 1){
			return v[x].get(i);
		}
		ll m = (lx + rx) / 2;
		ll val = 1e18;
		if(i < m && v[x].l != -1) val = calc(v[x].l, lx, m, i);
		else if(i >= m && v[x].r != -1) val = calc(v[x].r, m, rx, i);
		val = min(val, v[x].get(i));
		return val;
	}
	
	ll calc(int i){
		return calc(0, -(1ll << 30), (1ll << 30), i);
	}
};
