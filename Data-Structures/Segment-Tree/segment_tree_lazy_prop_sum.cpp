struct segTree{
    vector<ll> v;
    vector<ll> upd;
    int size = 1;
    void init(int n){
        while(size < n) size *= 2;
        v.assign(2 * size, 0);
        upd.assign(2 * size, 0);
    }
    void set(int l, int r, int x, int lx, int rx, ll u){
        if(lx >= l && rx <= r){
            v[x] += u * (rx - lx);
            upd[x] += u;
            return;
        }
        if(lx >= r || l >= rx) return;
        int m = (lx + rx) / 2;
        set(l, r, 2 * x + 1, lx, m, u);
        set(l, r, 2 * x + 2, m, rx, u);
        v[x] = v[2 * x + 1] + v[2 * x + 2] + upd[x] * (rx - lx);
        return;
    }
    void set(int l, int r, int u){
        return set(l, r, 0, 0, size, u);
    }

    void build(vector<ll> &a, int x, int lx, int rx){
        if (rx - lx == 1){
            if (lx < (int)a.size()){
                v[x] = a[lx];
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        v[x] = v[2 * x + 1] + v[2 * x + 2];
    }
    void build(vector<ll>& a){
        build(a, 0, 0, size);
    }

    pair<ll, int> sum(int l, int r, int x, int lx, int rx){
        if(lx >= l && rx <= r) return {v[x], rx - lx};
        else if(lx >= r || rx <= l) return {0, 0};
        int m = (lx + rx) / 2;
        pair<ll, int> s1 = sum(l, r, 2 * x + 1, lx, m);
        pair<ll, int> s2 = sum(l, r, 2 * x + 2, m, rx);
        return {s1.first + s2.first + upd[x] * (s1.second + s2.second), (s1.second + s2.second)};
    }

    ll sum(int l, int r){
        pair<ll, int> p = sum(l, r, 0, 0, size);
        return p.first;
    }
};
