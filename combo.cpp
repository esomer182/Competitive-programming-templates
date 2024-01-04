vector<ll> fact;

ll binpow(ll a, ll b, int mod = MOD){
    if(!b) return 1;
    else if(b % 2 == 0){
        ll x = binpow(a, b / 2, mod);
        return (x * x) % mod;
    }else{
        ll x = binpow(a, b / 2, mod);
        return (((x * x) % mod) * a) % mod;
    }
}

ll pw(ll a, ll b){
	ll ans = 1;
	for(int i = 0; i < b; i++) ans *= a;
	return ans;
}

ll inv(ll x, ll mod = MOD){
    x %= mod;
    return binpow(x, mod - 2, mod);
}

ll c(int n, int k){
    if(n < k) return 0;
    return (fact[n] * inv(fact[k] * fact[n - k], MOD)) % MOD;
}

ll c_without_mod(int n, int k){
	long double res = 1.0;
	for(ll i = 1; i <= n; i++){
		res *= i;
		if(i > k) res /= (i - k);
		else res /= i;
	}
	return (ll)res;
}

void init_fac(int n){
    fact.resize(n + 1);
    fact[0] = 1;
    for(int i = 1; i <= n; i++){
        fact[i] = fact[i - 1] * i;
        fact[i] %= MOD;
    }
}
