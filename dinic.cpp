struct Dinitz{
    using F = long long; //Change for other types of flow, long double or whatever.
    const long long infFlow = 1e18;

    struct edge{
        int v; F flow, cap;
        edge (int _v, F _flow, F _cap){
            v = _v; flow = _flow; cap = _cap;
        }
    };
    int s, t, n;
    vector<edge> edges; //Stores the info of all the edges.
    vector<vector<int>> adj; //Stores the index of the outgoing edges from u.
    vector<int> level, ptr; //Level of the node and pointer of the outgoing edges of the node.

    void init(int _s, int _t, int _n){
        s = _s; t = _t; n = _n;
        adj.clear(); adj.resize(n);
    }
    
    void addEdge(int u, int v, F cap){
        adj[u].push_back((int)edges.size());
        edges.push_back({v, 0, cap});
        adj[v].push_back((int)edges.size());
        edges.push_back({u, 0, 0}); //Cap is 0 because the reverse edge can be seen as negative flow.
    }

    bool bfs(){
        level.assign(n, -1);
        queue<int> q; q.push(s);
        level[s] = 0;
        while(!q.empty()){
            int x = q.front(); q.pop();
            for(int id : adj[x]){
                edge e = edges[id];
                if(level[e.v] != -1 || e.cap == e.flow) continue;
                level[e.v] = level[x] + 1;
                q.push(e.v);
            }
        }
        if(level[t] == -1) return false;
        else return true;
    }

    F dfs(int x, F flo){
        if(flo == 0 || x == t) return flo;
        for (int& cid = ptr[x]; cid < (int)adj[x].size(); cid++) {
            edge e = edges[adj[x][cid]];
            if(e.flow == e.cap || level[e.v] != level[x] + 1) continue;
            int nextFlow = dfs(e.v, min(flo, e.cap - e.flow));
            if(nextFlow == 0) continue;
            edges[adj[x][cid]].flow += nextFlow;
            edges[adj[x][cid] ^ 1].flow -= nextFlow; //Substracting from the reverse edge.
            return nextFlow;
        }
        return 0;
    }

    F flow(){
        F f = 0;
        while(bfs()){
            ptr.assign(n, 0);
            F flo = dfs(s, infFlow);
            while(flo != 0){ //It has to be done several times because I must stop once I find a flow.
                f += flo;
                flo = dfs(s, infFlow);
            }
        }
        return f;
    }
};