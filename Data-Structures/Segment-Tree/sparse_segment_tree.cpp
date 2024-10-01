struct Node {
    ll val, upd;
    Node *lft = nullptr, *rght = nullptr;
    Node(ll val = 0, ll upd = 0) : val(val), upd(upd) {}
};

struct sparseSegTree {
    int sz;
    Node root;
    void init(int n){
        sz = 1;
        while (sz < n) sz *= 2;
        root = Node();
    }
    void push(Node& x, int lx, int rx){
        int szChild = (rx - lx) / 2;
        (x.lft)->val += x.upd * szChild; 
        (x.rght)->val += x.upd * szChild; 
        (x.lft)->upd += x.upd; 
        (x.rght)->upd += x.upd;
        x.upd = 0; 
    }
    void set(int l, int r, Node& x, int lx, int rx, ll val){
        if(lx >= l && rx <= r){
            x.val += val * (rx - lx);
            x.upd += val;
            return;
        }else if(lx >= r || rx <= l) return;
        int m = (lx + rx) / 2;
        if(x.lft == nullptr) x.lft = new Node();
        if(x.rght == nullptr) x.rght = new Node();
        push(x, lx, rx);
        set(l, r, *x.lft, lx, m, val);
        set(l, r, *x.rght, m, rx, val);
        x.val = x.lft->val + x.rght->val;
    }
    void set(int l, int r, ll val){
        set (l, r, root, 0, sz, val);
    }
    ll calc(int l, int r, Node& x, int lx, int rx){
        if (lx >= l && rx <= r) return x.val;
        else if (lx >= r || rx <= l) return 0;
        int m = (lx + rx) / 2;
        if(x.lft == nullptr) x.lft = new Node();
        if(x.rght == nullptr) x.rght = new Node();
        push(x, lx, rx);
        ll s1 = calc(l, r, *x.lft, lx, m);
        ll s2 = calc(l, r, *x.rght, m, rx);
        return s1 + s2;
    }
    ll calc(int l, int r){
        return calc(l, r, root, 0, sz);
    }
};
