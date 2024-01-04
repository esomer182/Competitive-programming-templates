string to_s(int x){
	string ans = "";
	while(x){
		ans += char(x % 10 +'0');
		x /= 10;
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

ll to_int(string& s){
	ll x = 0;
	ll curr = 1;
	for(int i = (int)s.size() - 1; i >= 0; i--){
		x += (int)(s[i] - '0') * curr;
		curr *= 10;
	}
	return x;
}

ll to_int_r(string& s){
	unordered_map<char, int> m;
	m['I'] = 1;
	m['V'] = 5;
	m['X'] = 10;
	m['L'] = 50;
	m['C'] = 100;
	m['D'] = 500;
	m['M'] = 1000;
	int curr = 0;
	char lst = 'a';
	ll ans = 0;
	for(int i = 0; i < (int)s.size(); i++){
		int lstc = curr;
		if(s[i] == lst){
			curr++;
		}else curr = 1;
		if(curr > 3 || (curr > 1 && (s[i] == 'V' || s[i] == 'L' || s[i] == 'D'))){
			return -1;
		}
		bool gd = m.count(s[i]);
		if(!gd){
			return -1;
		}
		if(i > 0 && m[lst] < m[s[i]]){
			if(lstc > 1){
				return -1;
			}else ans -= 2 * m[lst];
		}
		ans += m[s[i]];
		lst = s[i];
	}
	return ans;
}
