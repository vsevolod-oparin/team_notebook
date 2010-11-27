#include<iostream>
#include<vector>
#include<utility>
using namespace std;

int start, end, maxFlow, n;
const int INF = 1000000000;
vector< vector<int> > cost;
vector< vector<int> > capacity;
vector< vector<int> > flow;
vector<int> dist;
vector<int> prev;
vector<int> potential;
vector<int> suppFlow;
vector<bool> visited;

bool readData() {
  int m;
  cin >> n;
  if (n == -1) {
    return false;
  }
  cin >> start >> end >> m;
  start--; end--;
  cost.resize(n);
  capacity.resize(n);
  for (int i = 0; i < n; i++) {
    cost[i].resize(n);
    capacity[i].resize(n);
  }

  for (int i = 0; i < m; i++) {
    int a, b, f, c;
    cin >> a >> b >> f >> c;
    a--; b--;
    cost[a][b] = c;
    capacity[a][b] = f;
  }
  return true;
}

void printAnswer() {
  cout << maxFlow << endl;
}

void runFlow(int i) {
  if (i == start) return;
  flow[i][prev[i]] -= suppFlow[end];
  flow[prev[i]][i] += suppFlow[end];
  maxFlow += cost[prev[i]][i] * suppFlow[end];
  runFlow(prev[i]);
}

void refreshPotential() {
  for (int i = 0; i < n; i++) {
    potential[i] += dist[i];
  }
}

int getDist(int i, int j) {
  return (potential[i] + cost[i][j] - potential[j]);
}

int findNearest() {
  int ans = -1;
  for (int i = 0; i < n; i++) {
    if (dist[i] != INF && !visited[i]) {
      if (ans == -1 || dist[i] < dist[ans]) {
	ans = i;
      }
    }
  }
  return ans;
}

void updateNeighbours(int c) {
    for (int i = 0; i < n; i++) {
      if (capacity[c][i] - flow[c][i] > 0 && dist[c] + getDist(c, i) < dist[i]) {
	dist[i] = dist[c] + getDist(c, i);
	prev[i] = c;
	suppFlow[i] = min(suppFlow[c], capacity[c][i] - flow[c][i]);
      }
    }
}

bool dijkstra() {
  prev.assign(n, -1);
  dist.assign(n, INF);
  visited.assign(n, false);
  dist[0] = 0;
  suppFlow[0] = INF;
  while (true) {
    int i = findNearest();
    if (i == -1) break;
    visited[i] = true;
    updateNeighbours(i);
  }
  return (dist[end] != INF);
}

void processTestCase() {
  maxFlow = 0;
  potential.resize(n);
  flow.resize(n);
  for (int i = 0; i < n; i++) {
    flow[i].resize(n);
  }
  while (dijkstra()) {
    runFlow(end);
    refreshPotential();
  }
}


int main() {
  while (readData()) {
    processTestCase();
    printAnswer();
  }
  return 0;
}
