struct LCA{
    const int LOG = 20;
    vector<vector<int>> dp;
    vector<vector<pair<int, int>>> sparse;
    vector<int> depths;
    vector<pair<int, int>> euler, times;
    void DFS(int x, vector<vector<int>>& adj, int p){
        dp[0][x] = p;
        times[x].first = (int)euler.size();
        euler.push_back({depths[x], x});
        for(int node : adj[x]){
            if(node != p){
                depths[node] = depths[x] + 1;
                DFS(node, adj, x);
                euler.push_back({depths[x], x});
            }
        }
        times[x].second = (int)euler.size() - 1;
    }
    void build(vector<vector<int>>& adj){
        int n = adj.size();
        dp.assign(LOG, vector<int>(n, 0)); depths.resize(n);
        euler.clear();
        depths[0] = 0;
        times.resize(n);
        DFS(0, adj, -1);
        for(int i = 1; i < LOG; i++){
            for(int j = 0; j < n; j++){
                if(dp[i-1][j] == -1) {dp[i][j] = -1; continue;}
                dp[i][j] = dp[i-1][dp[i-1][j]];
            }
        }
        sparse.assign(LOG, vector<pair<int, int>>((int)euler.size()));
        for(int i = 0; i < LOG; i++){
            for(int j = 0; j < (int)euler.size(); j++){
                if(!i) sparse[i][j] = euler[j];
                else{
                    if(j - (1 << (i-1)) < 0) sparse[i][j] = sparse[i-1][j];
                    else sparse[i][j] = min(sparse[i-1][j], sparse[i-1][j - (1 << (i-1))]);
                }
            }
        }
    }
 
    int kth(int x, int d){
        for(int k = LOG-1; k >= 0; k--){
            if((1 << k) <= d){
                x = dp[k][x];
                d -= (1 << k);
            }
        }
        return x;
    }
 
    int lca(int a, int b){
        if(depths[b] > depths[a]) b = kth(b, depths[b] - depths[a]);
        else if(depths[a] > depths[b]) a = kth(a, depths[a] - depths[b]);
        if(a == b) return a;
        int anc = -1;
        for(int k = LOG-1; k >= 0; k--){
            if(dp[k][a] == dp[k][b]){
                anc = max(0, dp[k][a]);
            }else{
                a = dp[k][a];
                b = dp[k][b];
            }
        }
        return anc;
    }
 
    int dist(int a, int b){
        return depths[a] + depths[b] - 2 * depths[lca(a, b)];
    }
 
    int fastLca(int a, int b){
        int l = min(times[a].first, times[b].first);
        int r = max(times[a].second, times[b].second);
        int pw = 31 - __builtin_clz(r-l+1);
        return min(sparse[pw][r], sparse[pw][l + (1 << pw) - 1]).second;
    }
 
    int fastDist(int a, int b){
        return depths[a] + depths[b] - 2 * depths[fastLca(a, b)];
    }
};
