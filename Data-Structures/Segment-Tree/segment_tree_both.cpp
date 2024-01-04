struct segTree {
    int size;
    vector<ll> sums;
    vector<ll> v;
    void init(int n){
        size = 1;
        while (size < n) size *= 2;
        sums.assign(2 * size, 0LL);
        v.assign(2 * size, 1e18);
    }
    void build(vector<ll> &a, int x, int lx, int rx){
        if (rx - lx == 1){
            if (lx < (int)a.size()){
                sums[x] = a[lx];
                v[x] = a[lx];
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        sums[x] = sums[2 * x + 1] + sums[2 * x + 2];
        v[x] = min(v[2 * x + 1], v[2 * x + 2]);
    }
    void build(vector<ll>& a){
        build(a, 0, 0, size);
    }
    void set(int i, int u, int x, int lx, int rx){
        if (rx - lx == 1){
            sums[x] = u;
            v[x] = u;
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m){
            set(i, u, 2 * x + 1, lx, m);
        }else{
            set(i, u, 2 * x + 2, m, rx);
        }
        sums[x] = sums[2 * x + 1] + sums[2 * x + 2];
        v[x] = min(v[2 * x + 1], v[2 * x + 2]);
    }
    void set(int i, int u){
        set (i, u, 0, 0, size);
    }

    ll sum(int l, int r, int x, int lx, int rx){
        if (lx >= r || l >= rx){
            return 0;
        }
        if (lx >= l && rx <= r){
            return sums[x];
        }
        int m = (lx + rx) / 2;
        ll s1 = sum(l, r, 2 * x + 1, lx, m);
        ll s2 = sum(l, r, 2 * x + 2, m, rx);
        return s1 + s2;
    }

    ll sum (int l, int r){
        return sum(l, r, 0, 0, size);
    }

    ll calc(int l, int r, int x, int lx, int rx){
        if (lx >= r || l >= rx){
            return 1e18;
        }
        if (lx >= l && rx <= r){
            return v[x];
        }
        int m = (lx + rx) / 2;
        ll s1 = calc(l, r, 2 * x + 1, lx, m);
        ll s2 = calc(l, r, 2 * x + 2, m, rx);
        return min(s1, s2);
    }

    ll calc(int l, int r){
        return calc(l, r, 0, 0, size);
    }
};
