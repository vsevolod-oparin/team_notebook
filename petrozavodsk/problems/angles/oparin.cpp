#include <cstdio>

const int MOD = (int)1e9 + 7;
const int FAKE = 30;

int get(int mask, int n) {
	return (mask >> n) & 1;
}

int set_(int mask, int n, int v) {
	return get(mask, n) == v ? mask : (mask ^ (1 << n));
}

int add1(int mask, int n1, int n2) {
	return set_(set_(mask, n1, 1), n2, 1);
}
int add1(int mask, int n1) {
	return set_(mask, n1, 1);
}

int check1(int mask, int n1, int n2, int n3) {
	return get(mask, n1) + get(mask, n2) + get(mask, n3) == 0;
}
int check1(int mask, int n1, int n2) {
	return get(mask, n1) + get(mask, n2) == 0;
}



void add(int& x, int v) { 
	x += v;
	x %= MOD;
}

int solve(int n, int m) {
	if (n > m) {
		int tmp = n;
		n = m;
		m = tmp;
	}
	int** s = new int*[n + 1];
	for (int i = 0; i < n + 1; ++i) {
		s[i] = new int[1 << (n + 1)];
		for (int j = 0; j < (1 << (n + 1)); ++j) {
			s[i][j] = 0;
		}
	}
	s[0][0] = 1;
	int sz = 1 << (n + 1);
	for (int im = 0; im < (m - 1); ++im) {
		for (int in = 0; in < n; ++in) {
			for (int ms = 0; ms < sz; ++ms) {
				if (get(ms, in) == 0) {
					if (in > 0 && check1(ms, in, in - 1, n)) {
						add(s[in + 1][set_(add1(ms, in, in - 1), n, 0)], s[in][ms]);
					}
					if (in < n - 1) {
						if (check1(ms, in, n)) {
							add(s[in + 1][add1(ms, in, n)], s[in][ms]);
						}
						if (check1(ms, in, in + 1, n)) {	
							add(s[in + 1][set_(add1(ms, in, in + 1), n, 0)], s[in][ms]);
						}
						if (check1(ms, in, in + 1)) {	
							add(s[in + 1][set_(add1(ms, in + 1, n), in, get(ms, n))], s[in][ms]);
						}
					} 
				} else {
					add(s[in + 1][set_(set_(ms, n, 0), in, get(ms, n))], s[in][ms]);
				}
//				printf("%d ", s[in][ms]);
				s[in][ms] = 0;
			}
		//	printf("\n");

		}
		for (int ms = 0; ms < sz; ++ms) {
	//		printf("%d ", s[n][ms]);
			s[0][ms] = s[n][ms];
			s[n][ms] = 0;
		}
	//	printf("\n");
	//	printf("\n");
	}
	return s[0][(1 << n) - 1];	
}

int main() {

	int n = 0;
	int m = 0;
	scanf("%d %d", &m, &n);
	printf("%d", solve(m, n));

	return 0;
}