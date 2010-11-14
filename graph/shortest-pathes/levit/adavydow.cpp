#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define N 1000
#define INF 10000000
class Deque{
  int arr[N];
  int begin;
  int end;
public:
  void PushFront(int x) {
    arr[--begin] = x;
    if (begin == -1) begin = N - 1;
  }

  void PushBack(int x) {
    arr[end++] = x;
    if (end == N) end = 0;
  }

  bool Empty() {
    return end == begin;
  }

  int PopFront() {
    if (++begin == N) begin = 0;
    return arr[begin - 1];
  }

  int PopBack() {
    if (--end == -1) end = N - 1;
    return arr[end];
  }

  void Clear() {
    begin = end = N / 2; 
  }
};
vector<int> type;
vector< vector< pair<int, int> > > graph;
vector<int> dists;
Deque M1;

int n, m;

void processTestCase() {
  type.assign(n, 0);
  dists.assign(n, INF);
  M1.Clear();
  type[0] = 1;
  dists[0] = 0;
  M1.PushBack(0);
  while (!M1.Empty()) {
    int cur = M1.PopFront();
    type[cur] = 2;
    for (int i = 0; i < graph[cur].size(); ++i) {
      int dest = graph[cur][i].first;
      int dist = dists[cur] + graph[cur][i].second;
      switch (type[dest]) {
      case 0:
	dists[dest] = dist;
	M1.PushBack(dest);
	break;
      case 1:
	dists[dest] = min(dists[dest], dist);
	break;
      case 2:
	if (dists[dest] > dist) {
	  dists[dest] = dist;
	  type[dest] = 1;
	  M1.PushFront(dest);
	}
	break;
      } 
    }
  }
}

bool readData() {
  graph.clear();
  cin >> n >> m;
  if (n == 0 && m == 0) return false;
  graph.resize(n);
  for (int i = 0; i < m; ++i) {
    int a, b, w;
    cin >> a >> b >> w;
    a--; b--;
    graph[a].push_back(make_pair<int, int>(b, w));
  }
  return true;
}


void printAnswer() {
  for (int i = 0; i < n; i++) {
    cout << "D(" << i + 1 << ") = " << dists[i] << endl;
  }
}

int main() {
  while (readData()) {
    processTestCase();
    printAnswer();
  }
  return 0;
}
