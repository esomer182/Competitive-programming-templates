//Tested on: https://judge.yosupo.jp/submission/181932. I should try to make it faster.
struct HLD{
    vector<bool> final, heavy;
    vector<pair<int, int>> paths;
    vector<int> id, parent, nodes, ind, depth;
 
    segTree st;
 
    int DFS(int x, vector<vector<int>>& adj, int p){
        parent[x] = p;
        vector<pair<int, int>> v;
        int subtree = 1;
        for(int node : adj[x]){
            if(node == p) continue;
            depth[node] = depth[x] + 1;
            v.push_back({node, DFS(node, adj, x)});
            subtree += v.back().second;
        }
        int half = subtree / 2; if(subtree % 2 == 1) half++;
        bool fin = 1;
        for(auto pr : v){
            if(pr.second >= half){
                fin = 0;
                heavy[pr.first] = 1;
            }
        }
        final[x] = fin;
        return subtree;
    }
 
    void build(vector<vector<int>>& adj, vector<int>& v){
        int n = adj.size();
        final.assign(n, 0); heavy.assign(n, 0); id.resize(n); parent.resize(n); nodes.resize(n); ind.resize(n); depth.resize(n);
        depth[0] = 0;
        DFS(0, adj, -1);
        int curr = 0;
        for(int i = 0; i < n; i++){
            if(final[i]){
                int x = i;
                int start = curr;
                id[x] = paths.size();
                ind[x] = curr;
                nodes[curr] = x; curr++;
                while(heavy[x]){
                    x = parent[x];
                    id[x] = paths.size();
                    ind[x] = curr;
                    nodes[curr] = x; curr++;
                }
                paths.push_back({start, curr - 1});
            }
        }
        st.init(n);
        for(int i = 0; i < n; i++) st.set(i, v[nodes[i]]);
    }
 
    int query(int a, int b){
        int ans = 0;
        bool done = false;
        while(!done){
            if(depth[nodes[paths[id[a]].second]] < depth[nodes[paths[id[b]].second]]) swap(a, b);
            if(id[a] == id[b]){
                ans = max(ans, st.calc(min(ind[a], ind[b]), max(ind[a], ind[b]) + 1));
                a = b;
                done = true;
            }else{
                ans = max(ans, st.calc(ind[a], paths[id[a]].second + 1));
                a = parent[nodes[paths[id[a]].second]];
            }
        }
        return ans;
    }
};
