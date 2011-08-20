#include <cstdio>
#include <cstring>

struct Node {
	Node** child;
	bool fin;
	Node() {
		child = new Node*[26];
		memset(child, 0, sizeof(Node*) * 26);
		fin = false;
	}	
} root;



int main() {

	char* s = new char[200010];
	int n = 0;
	scanf("%d", &n);
	bool yes = true;
	for (int i = 0; i < n; ++i) {
		scanf("%s", s);
		int l = strlen(s);
		Node* cur = &root;
		for (int j = 0; j < l; ++j) {
			int p = s[j] - 'a';
			if (cur -> child[p] == 0) {
				cur -> child[p] = new Node();
			}
			yes &= !(cur -> fin);
			cur = cur -> child[p];
		}
		for (int j = 0; j < 26; ++j) {
			yes &= cur -> child[j] == 0;
		}
		cur -> fin = true;
	}
	printf(yes ? "YES\n" : "NO\n");

	return 0;
}