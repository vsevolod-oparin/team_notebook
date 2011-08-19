#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;

struct divisor {
	ll pa;
	ll p;
	int a;
	divisor() {
		pa = p = a = 0;
	}
};

void add_div(ll& n, vector<divisor>& d, ll p) {
		divisor t;
		t.p = p;
		t.pa = 1;
		for (; n % p == 0; n /= p) {
			t.pa *= p;
			++t.a;
		}
		d.push_back(t);
}

void factor(ll n, vector<divisor>& d) {
	if (n % 2 == 0) {
		add_div(n, d, 2);
	}                
	for (ll i = 3; i * i <= n; i += 2) {
		if (n % i == 0) {
			add_div(n, d, i);
		}
	}
	if (n != 1) {
		add_div(n, d, n);
	}
}

ll mult(ll a, ll b, ll mod) {
	ll base = (ll)1e8;
	ll A[] = {a % base, a / base};
	ll B[] = {b % base, b / base};
	ll R[8] = {0};
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			R[i + j] += A[i] * B[j];
		}
	}
	for (int i = 0; i < 7; ++i) {
		R[i + 1] += R[i] / base;
		R[i] %= base;
	}
	ll prd = 1;
	ll res = 0;
	for (int i = 0; i < 8; ++i) {
		res += prd * R[i];
		res %= mod;
		prd = (prd * base) % mod;
	}
	return res;
}

ll pw(ll a, ll pw, ll mod) {
	ll res = 1;
	ll mul = a;
	for (; pw != 0; pw /= 2) {
		if (pw % 2 == 1) {
			res = mult(res, mul, mod);
		}
		mul = mult(mul, mul, mod);
	}
	return res;
}

int jakobi(ll a, const divisor& t) {
	return pw(a, (t.p - 1) / 2, t.p);	
}

ll cnt(ll a, const divisor& t) {
	a %= t.pa;
	if (a != 0 && t.pa % 2 == 0) {
		ll res = 1;
		ll pa = t.pa;
		for (; a % 4 == 0; a /= 4) {
			res *= 2;
			pa /= 4;
		}
	//	printf("%I64d %I64d\n", a, pa);
		if (pa == 2 && a == 1) {
			return res;
		}		
		if (pa == 4 && a == 1) {
			return res * 2;
		}
		if (pa >= 8 && a % 8 == 1) {
			return res * 4;
		}
		return 0;
	}          
	if (a == 0) {
		ll pw = 1;
		for (int i = 0; 2 * i < t.a; ++i) {
			pw *= t.p;
		}
		return t.pa / pw;
	}
	int k = 0;
	for (; a % t.p == 0; a /= t.p) {
		++k;
	}
	if (k % 2 == 1) {
		return 0;
	}
	ll res = 1;
	for (int i = 0; 2 * i < k; ++i) {
		res *= t.p;
	}            	
	return jakobi(a, t) == 1 ? 2 * res : 0;
}

ll solve(ll a, ll n) {
	vector<divisor> fact;
	factor(n, fact);
	ll ans = 1;
	for (vector<divisor>::iterator i = fact.begin(); i != fact.end(); ++i) {
		ans *= cnt(a % (i -> pa), *i);
	}
	return ans;
}

ll stupid_solve(ll a, ll n) {
	ll res = 0;
	for (ll i = 0; i < n; ++i) {
		res += (i * i) % n == a ? 1 : 0;
	}
	return res;
}

int main() {
     
//	printf("%I64d %I64d\n", solve(3, 6), stupid_solve(3, 6));
#define ALL
#ifdef ALL
	for (int n = 1; n < 300; ++n) {
		if (n % 100 == 0) {
			printf("checked on %d.\n", n);
		}
		for (int a = 0; a < n; ++a) {
			if (solve(a, n) != stupid_solve(a, n)) {
				printf("Error at a = %d, n = %d (%I64d vs %I64d).\n", a, n, solve(a, n), stupid_solve(a, n));
			}
		}
	}
#endif	

	return 0;
}