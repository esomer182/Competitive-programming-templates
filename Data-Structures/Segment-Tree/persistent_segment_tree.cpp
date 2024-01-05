//Tested on: https://cses.fi/problemset/result/8119824/
struct Node{
    ll x, l, r, upd;
};

struct segTree{
    //If I want to refer to the initial array, roots[0], else the i-th modification is roots[i].
    vector<Node> v;
    vector<int> roots;
    int size;

    void init(int n){
        size = 1;
        while(size < n) size *= 2;
        v.resize(2 * size);
        roots.push_back(0);
    }
    
    void build(int x, int lx, int rx, vector<ll>& a){
        v[x] = {0, 2 * x + 1, 2 * x + 2, 0};
        if(rx - lx == 1){
            if(lx < (int)a.size()) v[x].x = a[lx];
            return;
        }
        int m = (lx + rx) / 2;
        build(v[x].l, lx, m, a);
        build(v[x].r, m, rx, a);
        v[x].x = v[v[x].l].x + v[v[x].r].x;
    }
    
    void build(vector<ll>& a){
        build(0, 0, size, a);
    }
    
    int set(int l, int r, int x, int lx, int rx, ll u){
        if(lx >= l && rx <= r){
            Node a = {v[x].x + u * (rx - lx), v[x].l, v[x].r, v[x].upd + u};
            int ind = (int)v.size();
            v.push_back(a);
            return ind;
        }else if(lx >= r || rx <= l) return x;
        int m = (lx + rx) / 2;
        int left = set(l, r, v[x].l, lx, m, u);
        int rightt = set(l, r, v[x].r, m, rx, u);
        Node a = {v[left].x + v[rightt].x + v[x].upd * (rx - lx), left, rightt, v[x].upd};
        int ind = (int)v.size();
        v.push_back(a);
        return ind;
    }
    
    void set(int l, int r, ll u, int root){
        roots.push_back(set(l, r, roots[root], 0, size, u));
    }
    
    ll calc(int l, int r, int x, int lx, int rx){
        if(lx >= l && rx <= r){
            return v[x].x;
        }else if(lx >= r || rx <= l) return 0;
        int m = (lx + rx) / 2;
        ll m1 = calc(l, r, v[x].l, lx, m);
        ll m2 = calc(l, r, v[x].r, m, rx);
        return m1 + m2 + v[x].upd * (rx - lx);
    }
    
    ll calc(int l, int r, int root){
        return calc(l, r, roots[root], 0, size);
    }
};
