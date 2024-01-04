struct P{
	ll x, y;
	P(){}
	P(ll x_, ll y_) : x(x_), y(y_) {} 
};
 
P operator+(P u, P v){
	return P(u.x + v.x, u.y + v.y);
}
 
P operator-(P u, P v){
	return P(u.x - v.x, u.y - v.y);
}
 
P operator*(P u, ll k){
	return P(u.x * k, u.y * k);
}
 
ll dot(P u, P v){
	return u.x * v.x + u.y * v.y;
}
 
ll cross(P u, P v){
	return u.x * v.y - u.y * v.x;
}
 
ll norm(P u){
	return dot(u, u);
}
 
int sgn(ll k){
	if(k == 0) return 0;
	return (k < 0 ? -1 : +1);
}
 
int orient(P u, P v){
	return sgn(cross(u, v));
}
 
bool point_in_segment(P a, P b, P c){
	if(orient(a-b, c-a) == 0 && min(a.x, b.x) <= c.x && max(a.x, b.x) >= c.x && min(a.y, b.y) <= c.y && max(a.y, b.y) >= c.y) return 1;
	else return 0;
}
 
bool collinear(P a, P b, P c){
	if(orient(a-b, c-a) == 0) return 1;
	else return 0;
}
 
bool intersect(P a, P b, P c, P d){
	if(point_in_segment(a, b, c) || point_in_segment(a, b, d) || point_in_segment(c, d, a) || point_in_segment(c, d, b)) return 1;
	if(orient(a-b, c-a) == orient(a-b, d-a)) return 0;
	if(orient(c-d, a-c) == orient(c-d, b-c)) return 0;
	return 1;
}

//Three points -> Point C with straight AB.
//Four points -> Straight AB with straight CD.
