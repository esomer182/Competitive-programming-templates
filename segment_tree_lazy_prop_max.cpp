struct segTree {
    int size;
    vector<ll> mx;
    vector<ll> upd;
    void init(int n){
        size = 1;
        while (size < n) size *= 2;
        mx.assign(2 * size, -1e18);
        upd.assign(2 * size, 0ll);
    }
    void set(int l, int r, int v, int x, int lx, int rx){
        if (lx >= l && rx <= r){
            mx[x] += v;
            upd[x] += v;
            return;
        }else if(lx >= r || rx <= l) return;
        int m = (lx + rx) / 2;
        set(l, r, v, 2 * x + 1, lx, m);
        set(l, r, v, 2 * x + 2, m, rx);
        mx[x] = max(mx[x * 2 + 1], mx[x * 2 + 2]) + upd[x];
    }
    void set(int l, int r, int v){
        set(l, r, v, 0, 0, size);
    }
    void build(vector<ll> &a, int x, int lx, int rx){
        if (rx - lx == 1){
            if (lx < (int)a.size()){
                mx[x] = a[lx];
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        mx[x] = max(mx[x * 2 + 1], mx[x * 2 + 2]);
    }
    void build(vector<ll>& a){
        build(a, 0, 0, size);
    }

    ll calc(int l, int r, int x, int lx, int rx){
        if (lx >= r || l >= rx)
            return -1e18;
        if (lx >= l && rx <= r){
            return mx[x];
        }
        int m = (lx + rx) / 2;
        ll s1 = calc(l, r, 2 * x + 1, lx, m);
        ll s2 = calc(l, r, 2 * x + 2, m, rx);
        return max(s1, s2) + upd[x];
    }

    ll calc(int l, int r){
        return calc(l, r, 0, 0, size);
    }
};
