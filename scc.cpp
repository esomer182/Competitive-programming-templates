vector<vector<int>> nwAdj;
vector<int> scc, inDeg;
int currScc;

void getTopsort(int x, vector<vector<int>>& adj, vector<bool>& vis, vector<int>& topsort){
	vis[x] = 1;
	for(int node : adj[x]){
		if(!vis[node]) getTopsort(node, adj, vis, topsort);
	}
	topsort.push_back(x);
}

void getScc(int x, vector<vector<int>>& adj, vector<int>& scc){
	for(int node : adj[x]){
		if(scc[node] == -1){
			scc[node] = scc[x];
			getScc(node, adj, scc);
		}
	}
}

void findScc(int n, vector<pair<int, int>>& edges/*, vector<vector<int>>& nwAdj, vector<int>& scc, vector<int>& inDeg, int& currScc*/){ //Comment out if don't want to use global.
	vector<vector<int>> adj(n), radj(n);
	for(pair<int, int> p : edges){
		adj[p.first].push_back(p.second);
		radj[p.second].push_back(p.first);
	}
	vector<bool> vis(n, 0);
	vector<int> topsort;
	for(int i = 0; i < n; i++){
		if(!vis[i]) getTopsort(i, adj, vis, topsort);
	}
	scc.assign(n, -1);
	currScc = 0;
	for(int i = n - 1; i >= 0; i--){
		int x = topsort[i];
		if(scc[x] == -1){
			scc[x] = currScc; currScc++;
			getScc(x, radj, scc);
		}
	}
	nwAdj.assign(currScc, {});
	inDeg.assign(currScc, 0);
	for(pair<int, int> p : edges){
		int u = p.first; int v = p.second;
		if(scc[u] == scc[v]) continue;
		nwAdj[scc[u]].push_back(scc[v]);
		inDeg[scc[v]]++;
	}
}