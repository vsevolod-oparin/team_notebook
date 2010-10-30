#include <iostream>
#include <stack>
using namespace std;

int operatorPriority(char c) {
  switch (c) {
  case '^':
    return 5;
  case '/':
    return 4;
  case '*':
    return 3;
  case '-':
    return 2;
  case '+':
    return 1;
  default:
    return -1;
  }
}

bool isOperator(char c) {
  return operatorPriority(c) >= 0;
}

int proceedTestCase() {
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
      for(; !stck.empty() && stck.top() != '(' && operatorPriority(stck.top()) >= operatorPriority(c); stck.pop()) {
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
