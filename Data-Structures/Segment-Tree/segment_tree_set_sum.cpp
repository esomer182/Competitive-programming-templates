struct segTree {
    //Las más recientes son las que tienen el índice más pequeño.
    int size;
    vector<pair<ll, ll>> sums;
    vector<pair<ll, ll>> upd;
    void init(int n){
        size = 1;
        while (size < n) size *= 2;
        sums.assign(2 * size, {0, -1});
        upd.assign(2 * size, {0, -1});
    }
    void set(ll i, int l, int r, int x, int lx, int rx, int q, ll curr, int qry){
        if (lx >= l && rx <= r){
            sums[x] = {(rx - lx) * i, q};
            upd[x] = {i, q};
            return;
        }
        if((upd[x].second != -1 && upd[x].second < qry) || qry == -1){curr = upd[x].first; qry = upd[x].second;}
        if(qry != -1 && (sums[x].second == -1 || qry < sums[x].second)) sums[x] = {(rx - lx) * curr, qry};
        if(rx <= l || lx >= r) return;
        int m = (lx + rx) / 2;
        set(i, l, r, 2 * x + 1, lx, m, q, curr, qry);
        set(i, l, r, 2 * x + 2, m, rx, q, curr, qry);
        sums[x] = {sums[2 * x + 1].first + sums[2 * x + 2].first, q};
    }
    void set(ll i, int l, int r, int q){
        set (i, l, r, 0, 0, size, q, 0, -1);
    }

    void build(vector<ll> &a, int x, int lx, int rx){
        if (rx - lx == 1){
            if (lx < (int)a.size()){
                sums[x] = {a[lx], -1};
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        sums[x] = {sums[2 * x + 1].first + sums[2 * x + 2].first, -1};
    }
    void build(vector<ll>& a){
        build(a, 0, 0, size);
    }

    ll sum(int l, int r, int x, int lx, int rx, ll curr, int qry){
        if (lx >= r || l >= rx)
            return 0;
        if (lx >= l && rx <= r){
            if(qry != -1 && (sums[x].second == -1 || qry < sums[x].second)) sums[x] = {(rx - lx) * curr, qry};
            return sums[x].first;
        }
        if((upd[x].second != -1 && upd[x].second < qry) || qry == -1){curr = upd[x].first; qry = upd[x].second;}
        int m = (lx + rx) / 2;
        ll s1 = sum(l, r, 2 * x + 1, lx, m, curr, qry);
        ll s2 = sum(l, r, 2 * x + 2, m, rx, curr, qry);
        return s1 + s2;
    }

    ll sum (int l, int r){
        return sum(l, r, 0, 0, size, 0, -1);
    }
};
