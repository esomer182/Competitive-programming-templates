#include<bits/stdc++.h>
 
using namespace std;
 
#define endl "\n"
 
typedef long long int ll;

const int MOD = 1e9 + 7;
const ll space = 100100;

mt19937 gen(time(0));

struct Treap{
	vector<pair<ll, int>> nodes;
	vector<pair<int, int>> val;
	vector<pair<int, int>> child;
	int root = -1;
	
	void insert(pair<int, int> a, ll pos, int prior){
		int mine = (int)val.size();
		val.push_back(a);
		nodes.push_back({pos, prior});
		if(root == -1){
			root = 0;
			child.push_back({-1, -1});
			return;
		}
		int x = root;
		int lst = -1;
		int nd = -1;
		while(x != -1){
			if(nodes[x].second < prior){
				if(lst == -1) root = mine;
				else if(child[lst].first == x) child[lst].first = mine;
				else child[lst].second = mine;
				child.push_back({-1, -1});
				nd = x; x = -1;
			}else if(pos > nodes[x].first){
				if(child[x].second == -1){
					child[x].second = mine;
					child.push_back({-1, -1});
					x = -1;
				}else x = child[x].second;
			}else{
				if(child[x].first == -1){
					child[x].first = mine;
					child.push_back({-1, -1});
					x = -1;
				}else x = child[x].first;
			}
		}
		int right = mine; int left = mine;
		while(nd != -1){
			if(nodes[nd].first > pos){
				if(right == mine){
					child[right].second = nd;
				}else child[right].first = nd;
				int nw = child[nd].first;
				child[nd].first = -1;
				right = nd;
				nd = nw;
			}else{
				if(left == mine){
					child[left].first = nd;
				}else child[left].second = nd;
				int nw = child[nd].second;
				child[nd].second = -1;
				left = nd;
				nd = nw;
			}
		}
	}
	
	void erase(ll pos){
		int x = root;
		int parent = -1; int left = -1; int right = -1; int side = -1;
		while(x != -1){
			if(pos > nodes[x].first){
				x = child[x].second;
				parent = x; side = 2;
			}else if(pos < nodes[x].first){
				x = child[x].first;
				parent = x; side = 1;
			}else{
				left = child[x].first; right = child[x].second;
				if(left == -1 && right == -1){
					if(side == 1){
						child[parent].first = -1;
					}else if(side == 2){
						child[parent].second = -1;
					}else root = -1;
				}
				break;
			}
		}
		while(left != -1 || right != -1){
			int node, nwside;
			if(left == -1){
				node = right; right = child[right].first; nwside = 1;
			}else if(right == -1){
				node = left; left = child[left].second; nwside = 2;
			}else if(nodes[right].second > nodes[left].second){
				node = right; right = child[right].first; nwside = 1;
			}else{
				node = left; left = child[left].second; nwside = 2;
			}
			if(parent == -1){
				root = node;
				side = nwside;
				parent = node;
			}else if(side == 1){
				child[parent].first = node;
				side = nwside;
				parent = node;
			}else{
				child[parent].second = node;
				side = nwside;
				parent = node;
			}
		}
	}
	
};

void solve(){
	int n; cin >> n;
	vector<vector<pair<int, int>>> left(n + 1);
	pair<int, int> lst = {-1, -1};
	vector<int> lw(n, 1);
	set<int> used;
	Treap tr;
	for(int i = 0; i < n; i++){
		int x; cin >> x;
		int c = (int)left[x].size();
		left[x].push_back(lst);
		lst = {x, c};
		int priority = (gen() % MOD);
		bool gd = used.count(priority);
		while(gd){
			priority = (gen() % MOD);
			gd = used.count(priority);
		}
		tr.insert({{x, c}, i * space, priority});
	}
	int q; cin >> q;
	while(q--){
	
	}
}
 
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    //~ int tt; cin >> tt;
    int tt = 1;
    for(int t = 1; t <= tt; t++){
        solve();
    }
}
