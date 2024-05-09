struct Hash{
	const ll MOD1 = 998244353;
	const ll MOD2 = 1e9 + 7;
	const ll base1 = 134551;
	const ll base2 = 918148;

	ll binpow(ll a, ll b, ll mod){
	    if(!b) return 1;
	    else if(b % 2 == 0){
	        ll x = binpow(a, b / 2, mod);
	        return (x * x) % mod;
	    }else{
	        ll x = binpow(a, b / 2, mod);
	        return (((x * x) % mod) * a) % mod;
	    }
	}

	ll inv(ll x, ll mod){
	    x %= mod;
	    return binpow(x, mod - 2, mod);
	}

	int n;
	vector<ll> pw1, pw2, inv1, inv2;
	vector<pair<ll, ll>> hash, hashRev;
	void hashString(string& s){
		n = (int)s.size();
		pw1.assign(n, 1); pw2.assign(n, 1);
		inv1.assign(n, 1); inv2.assign(n, 1);
		hash.resize(n);
		hashRev.resize(n);
		for(int i = 1; i < n; i++){
			pw1[i] = pw1[i-1] * base1; pw1[i] %= MOD1;
			pw2[i] = pw2[i-1] * base2; pw2[i] %= MOD2;
			inv1[i] = inv(pw1[i], MOD1);
			inv2[i] = inv(pw2[i], MOD2);
		}
		for(int i = 0; i < n; i++){
			if(i > 0){
				hash[i] = hash[i-1];
				hashRev[i] = hashRev[i-1];
			}
			hash[i].first += s[i] * pw1[i]; hash[i].first %= MOD1;
			hash[i].second += s[i] * pw2[i]; hash[i].second %= MOD2;
			hashRev[i].first += s[i] * pw1[n-1-i]; hashRev[i].first %= MOD1;
			hashRev[i].second += s[i] * pw2[n-1-i]; hashRev[i].second %= MOD2;
		}
	}
	pair<ll, ll> getHash(int l, int r){
		if(l > r) return {0, 0};
		pair<ll, ll> hsh = hash[r];
		if(!l) return hsh;
		hsh.first = (hsh.first + MOD1 - hash[l-1].first) % MOD1;
		hsh.second = (hsh.second + MOD2 - hash[l-1].second) % MOD2;
		hsh.first *= inv1[l]; hsh.first %= MOD1;
		hsh.second *= inv2[l]; hsh.second %= MOD2;
		return hsh;
	}
	pair<ll, ll> append(int k){
		//New string formed by removing k first and appending them to the end.
		pair<ll, ll> hsh = getHash(k, n-1);
		if(k > 0){
			hsh.first += hash[k-1].first * pw1[n-k]; hsh.first %= MOD1;
			hsh.second += hash[k-1].second * pw2[n-k]; hsh.second %= MOD2;
		}
		return hsh;
	}
	pair<ll, ll> appendRev(int k){
		//New string formed by removing k first and appending them to the end in reversed order.
		pair<ll, ll> hsh = getHash(k, n-1);
		if(k > 0){
			hsh.first += hashRev[k-1].first; hsh.first %= MOD1;
			hsh.second += hashRev[k-1].second; hsh.second %= MOD2;
		}
		return hsh;
	}
};
