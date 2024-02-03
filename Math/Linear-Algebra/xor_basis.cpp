struct Basis{
    pair<int, int> basis[LOG];
    vector<int> done;
 
    void init(){
        done.push_back(1);
        for(int k = 0; k < LOG; k++) basis[k] = {-1, -1};
    }
 
    bool add(pair<int, int> p){
        if(done.empty()) init();
        int val = p.first; int j = p.second;
        for(int k = LOG-1; k >= 0; k--){
            if(!((1 << k) & val)) continue;
            if(basis[k].first == -1){
                basis[k] = {val, j};
                return true;
            }else{
                val ^= basis[k].first;
            }
        }
        return false;
    }
};
