struct segTree{
    vector<ll> v;
    vector<pair<ll, int>> upd;
    int size = 1;
    void init(int n){
        while(size < n) size *= 2;
        v.assign(2 * size, 0);
        upd.assign(2 * size, {0, 0});
    }
    void push(int x, int lx, int rx){
        int szChild = (rx - lx)/2;
        if(upd[x].second == 1){
            //Ha habido una operación set, así que setteo todo el rango a upd[x].first;
            v[2 * x + 1] = szChild * upd[x].first;
            v[2 * x + 2] = szChild * upd[x].first;
            upd[2 * x + 1] = upd[x]; //También tienen que ser iguales.
            upd[2 * x + 2] = upd[x];
            upd[x] = {0, 0};
        } else {
            v[2 * x + 1] += szChild * upd[x].first; //No setteo, solo sumo.
            v[2 * x + 2] += szChild * upd[x].first;
            upd[2 * x + 1].first += upd[x].first; //Sumo lo que he sumado ahora.
            upd[2 * x + 2].first += upd[x].first;
            upd[x] = {0, 0};
        }
    }
    void add(int l, int r, int x, int lx, int rx, ll u){
        if(lx >= l && rx <= r){
            v[x] += u * (rx - lx);
            upd[x].first += u;
            return;
        }
        if(lx >= r || l >= rx) return;
        int m = (lx + rx) / 2;
        push(x, lx, rx);
        add(l, r, 2 * x + 1, lx, m, u);
        add(l, r, 2 * x + 2, m, rx, u);
        v[x] = v[2 * x + 1] + v[2 * x + 2];
        return;
    }
    void add(int l, int r, int u){
        return add(l, r, 0, 0, size, u);
    }
    void set(int l, int r, int x, int lx, int rx, ll u){
        if(lx >= l && rx <= r){
            v[x] = u * (rx - lx);
            upd[x].first = u;
            upd[x].second = 1;
            return;
        }
        if(lx >= r || l >= rx) return;
        int m = (lx + rx) / 2;
        push(x, lx, rx);
        set(l, r, 2 * x + 1, lx, m, u);
        set(l, r, 2 * x + 2, m, rx, u);
        v[x] = v[2 * x + 1] + v[2 * x + 2];
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

    ll sum(int l, int r, int x, int lx, int rx){
        if(lx >= l && rx <= r) return v[x];
        else if(lx >= r || rx <= l) return 0;
        int m = (lx + rx) / 2;
        push(x, lx, rx);
        ll s1 = sum(l, r, 2 * x + 1, lx, m);
        ll s2 = sum(l, r, 2 * x + 2, m, rx);
        return s1 + s2;
    }

    ll sum(int l, int r){
        return sum(l, r, 0, 0, size);
    }
};
