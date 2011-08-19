#include <cstdio>
#include <algorithm>

using namespace std;

int main() {

	int n = 0;
	scanf("%d", &n);
	int* b = new int[n];
	for (int i = 0; i < n; ++i) {
		scanf("%d", &b[i]);
	}
	sort(b, b + n);
	bool lst = b[n - 1] % 5 == 0 || b[n - 1] % 7 == 0;

	if (b[0] == 5 && b[n - 1] == 5 && n % 2 == 0) {
		printf("Second");
	} else if ( (n == 1 && lst) ||
							(n % 2 == 0 && b[0] == 5 && b[n - 1] == 5) ||
							(b[0] == 5 && b[n - 2] == 5 && ((n % 2 == 0 && lst) || (n % 2 == 1 && b[n - 1] % 5 == 0)))
						) {
		printf("First");
	} else {
		printf("Draw");
	}
	
	

	delete[] b;

	return 0;
}