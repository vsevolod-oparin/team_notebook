#include <iostream>
#include <stack>
using namespace std;
char priority[256];

void prepare() {
    memset(priority, -1, 256);
	priority['^'] = 5;
	priority['/'] = 4;
	priority['*'] = 3;
	priority['-'] = 2;
	priority['+'] = 1;		
}

bool isOperator(char c) {
  return priority[c] >= 0;
}

int proceedTestCase() {
  prepare();
  string var;
  cin >> var;
  stack<char> stck;
  string ans = "";
  for (int i = 0; i < var.size(); i++) {
    char c = var[i];
    if (c == '(') {
      stck.push('(');
    } else if (c == ')') {
      for(; stck.top() != '('; stck.pop()) {
	ans.push_back(stck.top());
      }
      stck.pop();
    } else if (isOperator(c)) {
      for(; !stck.empty() && stck.top() != '(' && priority[stck.top()] >= priority[c]; stck.pop()) {
	ans.push_back(stck.top());
      }
      stck.push(c);
    } else {
      ans.push_back(c);
    }
  }
  while (!stck.empty()) {
    ans.push_back(stck.top());
    stck.pop();
  }
  cout << ans << endl;
  return 0;
}

int main() {
  int n;
  for (cin >> n; n > 0; n--) {
    proceedTestCase();
  }
  return 0;
}
