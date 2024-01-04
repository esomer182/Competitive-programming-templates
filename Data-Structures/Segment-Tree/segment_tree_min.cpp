struct segTree {
    int size;
    vector<ll> minimum;
    void init(int n){
        size = 1;
        while (size < n) size *= 2;
        minimum.assign(2 * size, 1e18);
    }

    void set(int i, int v, int x, int lx, int rx){
        if (rx - lx == 1){
            minimum[x] = v;
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m){
            set(i, v, 2 * x + 1, lx, m);
        }else{
            set(i, v, 2 * x + 2, m, rx);
        }
        minimum[x] = min(minimum[x * 2 + 1], minimum[x * 2 + 2]);
    }

    void set(int i, int v){
        set(i, v, 0, 0, size);
    }

    void build(vector<int> &a, int x, int lx, int rx){
        if (rx - lx == 1){
            if (lx < (int)a.size()){
                minimum[x] = a[lx];
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        minimum[x] = min(minimum[2 * x + 1], minimum[2 * x + 2]);
    }
    void build(vector<int>& a){
        build(a, 0, 0, size);
    }


    ll calc(int l, int r, int x, int lx, int rx){
        if (lx >= r || l >= rx)
            return 1e18;
        if (lx >= l && rx <= r){
            return minimum[x];
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
