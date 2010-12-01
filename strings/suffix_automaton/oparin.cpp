#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

int MAX_SIZE = 1e4;
int K = 256;

struct Node {
  Node** edge;
  Node* link;
  int len;
  bool terminal;
  int num;
  Node() :
    edge(new Node*[K])
  {
    static int i = 0;
    num = i++;
    memset(edge, 0, 4 * K);    
    memset(&link, 0, 4);
    len = 0;
    terminal = false;
  }
  
};

struct Automaton {
  vector<Node*> nd;
  Node* last_;
  Automaton() {
    nd.push_back(new Node());
    nd[0] -> len = 0;
    last_ = nd[0];
  }
  void extend(char c) {
    Node& last = *last_;
    nd.push_back(new Node());
    Node& nlast = *nd.back();
    nlast.len = last.len + 1;    
    Node* p = &last;
    for (; p != 0 && p -> edge[c] == 0; p = p -> link) {
      p -> edge[c] = &nlast;
    }
    last.edge[c] = &nlast;
    if (p == 0) {
      nd.front() -> edge[c] = &nlast;
      nlast.link = nd.front();
    } else {
      Node* q = p -> edge[c];
      if (q -> len == p -> len + 1) {
        nlast.link = q;
      } else {
        nd.push_back(new Node());
        Node& clone = *nd.back();        
        memcpy(clone.edge, q -> edge, 4 * K);
        clone.len = p -> len + 1;
        clone.link = q -> link;
        q -> link = &clone;
        nlast.link = &clone;
        for (; p != 0 && p -> edge[c] == q; p = p -> link) {
          p -> edge[c] = &clone;
        }
      }
    }
    last_ = &nlast;
  }
  void terminate() {
    for (Node* p = last_; p != 0; p = p -> link) {
      p ->terminal = true;
    }
  }
  void print() {
    for (vector<Node*>::iterator i = nd.begin(); i != nd.end(); ++i) {
      printf("%d\n", (*i) -> num);
      for (int c = 0; c < K; ++c) {
        if ((*i) -> edge[c] != 0) {
          printf("  %c %d\n", c, (*i) -> edge[c] -> num);
        }
      }
    }
  }
  ~Automaton() {
    for (vector<Node*>::iterator i = nd.begin(); i != nd.end(); ++i) {
      delete *i;
    }
  }
};

int tc(const Automaton& a, int* cnt, int node) {
  if (cnt[node] >= 0) {
    return cnt[node];
  }  
  cnt[node] = 1;
  for (int i = 0; i < K; i++) {
    Node* ci = a.nd[node] -> edge[i] ;
    cnt[node] += ci == 0 ? 0 : tc(a, cnt, ci -> num);
  }
  return cnt[node];
}

int count(const Automaton& a) {  
  int sz = a.nd.size();
  int* cnt = new int[sz];
  memset(cnt, -1, 4 * sz);  
  int res = tc(a, cnt, 0);
  return res;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "rt", stdin);
#endif
  char* inp = new char[MAX_SIZE];
  scanf("%s", inp);
  Automaton t;
  int len = strlen(inp);
  for (int i = 0; i < len; ++i) {
    t.extend(inp[i]);
  }
  //t.print();
  printf("%d", count(t) - 1);
  delete[] inp; 

  return 0;
}