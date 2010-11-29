#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
#define FOR(i,n) for (int i = 0; i < (n); ++i)
#define FORE(i,k,n) for (int i = (k); i < (n); ++i)

int nextInt() {
  int n;
  scanf("%d", &n);
  return n; 
}

int** m;
vector< vector<int> > edge;
vector< int > toVis;
int* mate;
int* label;
int* first;
int* flag;
int* was;
int n;

int DUMMY;

int nc(int x, int y) {
  return x * (n + 1) + y + 2 * n + 3;
}
void nd(int c, int& x, int& y) {
  x = (c - 2 * n - 3) / (n + 1);
  y = (c - 2 * n - 3) % (n + 1);
}

void R(int x, int y) {
  int t = mate[x];
  mate[x] = y;
  if (mate[t] == x) {
    int l = label[x];
    if (0 <= l && l < n) {
      mate[t] = l;
      R(l, t);
    } else if (l >= 2 * n) {
      int a, b;
      nd(l, a, b);
      R(a, b);
      R(b, a);
    }
  }
}

void L(int a, int b, int nc) {
  int x = first[a];
  int y = first[b];
  if (x == y) {
    return;
  }
  int join = DUMMY;
  flag[x] = 1;
  flag[y] = 1;
  do {
    if (y != DUMMY) {
      swap(x, y);    
    }
    x = first[label[mate[x]]];
    if (flag[x]) {
      join = x;
      break;
    } else {
      flag[x] = 1;
    }
  } while (true);
  for (int i = first[a]; i != join; i = first[label[mate[i]]]) {
    toVis.push_back(i);
    label[i] = nc;
    first[i] = join;
  }
  for (int i = first[b]; i != join; i = first[label[mate[i]]]) {
    toVis.push_back(i);
    label[i] = nc;    
    first[i] = join;
  }
  FOR(i, n) {
    first[i] = label[first[i]] >= 0 ? join : first[i];
  }
  memset(flag, 0, 4 * (n + 1));
}

bool DFS(int, int);

bool visit(int start) {
  int tvn = toVis.size();
  int* tmp = new int[tvn];
  FOR(j, tvn) {
    tmp[j] = toVis[j];
  }
  toVis.clear();
  FOR(j, tvn) {
    if (DFS(tmp[j], start)) {
      return true;
    }
  }
  delete[] tmp;
  return false;
}

bool DFS(int u, int start) {
  if (was[u]) {
    return false;
  }
  was[u] = true;
  vector<int>& edges = edge[u];
  for (vector<int>::iterator i = edges.begin(); i != edges.end(); ++i) {
    int v = *i;
    int mt = mate[v];
    if (mt == -1 && v != start) {
      mate[v] = u;
      R(u, v);
      return true;
    } else if (label[v] >= 0) {
      int code = nc(u, v);
      L(u, v, code);    
      if (visit(start)) {
        return true;
      }
    } else if (label[mt] == -1) {
      label[mt] = u;
      first[mt] = v;
      if (DFS(mt, start)) {
        return true;
      }
    }
  }
  return false;
}

void allocation() {
  m = new int*[n];
  m[0] = new int[n * n];
  mate = new int[n];
  label = new int[n + 1];
  first = new int[n + 1];
  was = new int[n + 1];
  flag = new int[n + 1];
  memset(m[0], 0, 4 * n * n);
  memset(mate, -1, 4 * n);
  edge.resize(n);
  FORE(i, 1, n) {
    m[i] = m[0] + i * n;
  }
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "rt", stdin);
  //freopen("output.txt", "wt", stdout);
#endif

  n = nextInt();
  allocation();
  
  while (!feof(stdin)) {
    int a = nextInt() - 1;
    if (feof(stdin)) {
      break;
    }
    int b = nextInt() - 1;
    m[a][b] = m[b][a] = 1;    
  }
  FOR(i, n) {
    FOR(j, n) {
      if (m[i][j]) {
        edge[i].push_back(j);
      }
    }
  }

  DUMMY = n;
  FOR(i,n) {
    if (mate[i] == -1) {
      memset(first, -1, 4 * (n + 1));
      memset(label, -1, 4 * (n + 1));
      memset(flag, 0, 4 * (n + 1));
      memset(was, 0, 4 * (n + 1));
      label[i] = first[i] = DUMMY;      
      DFS(i, i);
    }
  }
  int ans= 0;
  FOR(i,n) {
    if (mate[i] >= 0) {
      ans++;
    }
  }
  printf("%d\n", ans);
  FOR(i,n) {
    if (mate[i] >= 0 && i < mate[i]) {
      printf("%d %d\n", i + 1, mate[i] + 1);
    }
  }

  delete[] was;
  delete[] first;
  delete[] label;
  delete[] mate;
  delete[] m[0];
  delete[] m;

  return 0;
}