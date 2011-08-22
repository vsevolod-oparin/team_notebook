#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define MAX 200010
char s[MAX];
char S0[MAX];
char S1[MAX];

int* zfunc(const char* s, int len) {
	int* z = new int[len];
	z[0] = len;
	int left = 0;
	int right = 0;
	// [left, right)
	for (int i = 1; i < len; ++i) { // [i, ls)
		int j = i >= right ? i : min(i + z[i - left], len);		
		for (; s[j] == s[j - i] && j < len; ++j)
			;
		z[i] = j - i; 
		if (j >= right) {
			left = i;
			right = j;
		}
	}	
	return z;
}

#define LIM 40

int F[LIM] = {0};

void prepare() {
	F[0] = F[1] = 1;
	for (int i = 2; i < LIM; ++i) {
		F[i] = F[i - 1] + F[i - 2];
	}
}

int getFib(int n, int s0, int s1) {
	return F[n - 2] * s0 + F[n - 1] * s1;
}

int getSecondSeed(int val, int n, int s0) {
	int tmp = val - F[n - 2] * s0;
	return tmp % F[n - 1] == 0 ? tmp / F[n - 1] : -1;
}

int rank(int val) {
	int i = 0;
	for (i = 0; F[i] < val && i < LIM; ++i)
		;
	return i;
}

bool isBorder(int pref, int len, int* z) {
	return z[len - pref] >= pref;
}

bool check(int rank, int s0, int s1, int* z, int* rz) {
	bool ok = true;
	for (int i = rank; i > 2 && ok; i -= 2) {
		ok &= isBorder(getFib(i - 2, s0, s1), getFib(i, s0, s1), z);		
	}
	for (int i = rank - 1; i > 2 && ok; i -= 2) {
		ok &= isBorder(getFib(i - 2, s0, s1), getFib(i, s0, s1), rz);		
	}
	return ok;
}

int main() {

	scanf("%s", s);
	int ls = strlen(s);

	prepare();

	int* z  = zfunc(s, ls);
	reverse(s, s + ls);
	int* rz = zfunc(s, ls);
	reverse(s, s + ls);

	for (int n = rank(ls); n > 2; --n) {
		for (int f0 = 1; getFib(n, f0, 0) <= ls; ++f0) {
			int f1 = getSecondSeed(ls, n, f0);
			if (f1 > 0) {
				if (check(n, f0, f1, z, rz)) {
					if (n % 2 == 0) {
						memcpy(S0, s, f0);
						memcpy(S1, s + f0, f1);
					} else {	
						memcpy(S1, s, f1);
						memcpy(S0, s + f1, f0);
					}
					printf("%d\n", n);
					printf("%s %s", S0, S1);	
					
					delete[] z;
					delete[] rz;
					return 0;								
				}
			}
		}
	}
	printf("2\n%c %s", s[0], s + 1);

	delete[] z;
	delete[] rz;   
	return 0;
}