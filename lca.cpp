struct LCA{
    vector<vector<int>> dp;
    vector<int> depths;
    void DFS(int x, vector<vector<int>>& adj, int p){
        dp[x][0] = p;
        for(auto node : adj[x]){
            if(node != p){
                depths[node] = depths[x] + 1;
                DFS(node, adj, x);
            }
        }
    }
    void build(vector<vector<int>>& adj){
        int n = adj.size();
        dp.assign(n, vector<int>(20, 0)); depths.resize(n);
        depths[0] = 0;
        DFS(0, adj, -1);
        for(int i = 1; i < 20; i++){
            for(int j = 0; j < n; j++){
                if(dp[j][i - 1] == -1) {dp[j][i] = -1; continue;}
                dp[j][i] = dp[dp[j][i - 1]][i - 1];
            }
        }
    }

    int kth(int x, int d){
        for(int k = 19; k >= 0; k--){
            if((1 << k) <= d){
                x = dp[x][k];
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
        for(int k = 19; k >= 0; k--){
            if(dp[a][k] == dp[b][k]){
                anc = max(0, dp[a][k]);
            }else{
                a = dp[a][k];
                b = dp[b][k];
            }
        }
        return anc;
    }

    int dist(int a, int b){
        return depths[a] + depths[b] - 2 * depths[lca(a, b)];
    }
};
