
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
const ll mod = 104857601;

//mod multiplication
ll mult(ll a, ll b){
	return (a*b)%mod;
}

//O(logN) power
ll fexp(ll b, ll e){
	ll r = 1;
	while(e>0){
		if(e&1)r=mult(r,b);
		b = mult(b,b);
		e /= 2;
	}
	return r;
}

//Recursive algorithm for ntt
//Computes P(x) for each N-th root of unity
//rt is a primitive N-th root of unity

//Computes the coefficients of a polynomial of degree N knowing its point values in the N-th roots of unity
//rt is the inverse of a primitive N-th root of unity

void ntt(vll& v, ll rt){
	ll N = v.size();
	if(N == 1)return;
	vll p(N/2);
	vll d(N/2);
	for(int i = 0; i < N; i++){
		if(i%2)d[i/2] = v[i];
		else p[i/2] = v[i];
	}
	ll w =1;
	ntt(d,mult(rt,rt)); ntt(p,mult(rt,rt));
	for(int i = 0; i < N/2; i++){
		v[i] = (mod +p[i] + mult(w,d[i]))%mod;
		v[i+N/2] = (mod+p[i] - mult(w,d[i]))%mod;
		w = mult(w,rt);
	}
}




//The order in which roots of unity are in v for both ntt and inverse ntt depends on rt
//v[i] = rt^(i+1)

//multiplies 2 polynomials in nlogn
vll multiply(vll a, vll b){
	ll sz = 1;
	while(sz < a.size() + b.size())sz*=2;
	a.resize(sz); b.resize(sz);
	ll rt = fexp(5,mod/sz);
	ntt(a,rt); ntt(b,rt);
	for(int i = 0; i < sz; i++)a[i] = mult(a[i],b[i]);
	ntt(a,fexp(rt,mod-2));
	for(auto &x: a)x = mult(x,fexp(sz,mod-2));
	return a;
}
