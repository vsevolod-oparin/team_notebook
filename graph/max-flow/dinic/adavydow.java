import java.io.*;
import java.util.*;
import java.math.*;

public class Main implements Runnable {
	String file = "template";
	boolean local = false;
	ArrayList<int[]>[] edges;
	final int TO = 1;
	final int INV = 2;
	final int CAP = 3;
	final int FLOW = 4;
	final int ESIZE = 5;
	int[] dist;
	int[] que;
	boolean[] visited;
	final int inf = (int) 1e9;

	int vn;
	int S;
	int T;

	@SuppressWarnings("unchecked")
	void initFlow() {
		edges = new ArrayList[vn];
		dist = new int[vn];
		que = new int[vn];
		visited = new boolean[vn];
		for (int i = 0; i < vn; ++i) {
			edges[i] = new ArrayList<int[]>();
		}
	}

	void addEdge(int from, int to, int cap) {
		int[] eft = new int[ESIZE];
		eft[TO] = to;
		eft[CAP] = cap;
		eft[INV] = edges[to].size();
		int[] etf = new int[ESIZE];
		etf[TO] = from;
		etf[INV] = edges[from].size();
		edges[from].add(eft);
		edges[to].add(etf);
	}

	boolean findPath() {
		Arrays.fill(visited, false);
		int start = 0;
		int end = 0;
		dist[S] = 0;
		que[end++] = S;
		visited[S] = true;
		while (start < end) {
			int cur = que[start++];
			for (int[] edge : edges[cur]) {
				if (edge[CAP] - edge[FLOW] <= 0 || visited[edge[TO]]) {
					continue;
				}
				dist[edge[TO]] = dist[cur] + 1;
				visited[edge[TO]] = true;
				que[end++] = edge[TO];
			}
		}
		return visited[T];
	}

	int pushFlow(int cur, int ammount) {
		if (cur == T) {
			return ammount;
		}
		for (int[] edge : edges[cur]) {
			if (edge[CAP] - edge[FLOW] <= 0 || dist[cur] >= dist[edge[TO]]) {
				continue;
			}
			int pushed = pushFlow(edge[TO], Math.min(ammount, edge[CAP]
					- edge[FLOW]));
			if (pushed > 0) {
				edge[FLOW] += pushed;
				edges[edge[TO]].get(edge[INV])[FLOW] -= pushed;
				return pushed;
			} else {
				dist[edge[TO]] = -inf;
			}
		}
		return 0;
	}

	int Flow() {
		int flow = 0;
		while (findPath()) {
			int pushed;
			while ((pushed = pushFlow(S, inf)) != 0) {
				flow += pushed;
			}
		}
		return flow;
	}

	void solve() throws IOException {
		int n = nextInt();
		vn = 2 * n + 2;
		int L = 0;
		int R = n;
		S = 2 * n;
		T = 2 * n + 1;
		initFlow();
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				addEdge(L + i, R + j, 100);
			}
		}
		int a1 = 0;
		for (int i = 0; i < n; ++i) {
			int t = nextInt();
			addEdge(S, L + i, t);
			a1 += t;
		}
		int a2 = 0;
		for (int i = 0; i < n; ++i) {
			int t = nextInt();
			addEdge(R + i, T, t);
			a2 += t;
		}
		int a3 = Flow();
		if (a1 == a2 && a2 == a3) {
			out.println("YES");
			int[] m = new int[n];
			for (int i = 0; i < n; ++i) {
				Arrays.fill(m, 0);
				int u = L + i;
				for (int[] edge : edges[u]) {
					if (edge[TO] == S) {
						continue;
					}
					m[edge[TO] - R] += edge[FLOW];
				}
				for (int j = 0; j < n; ++j) {
					out.print(m[j] + " ");
				}
				out.println();
			}

		} else {
			out.println("NO");
		}
	}

	public static void main(String[] args) {
		new Thread(new Main()).start();
	}

	BufferedReader br;
	StringTokenizer tok;
	PrintWriter out;

	public void run() {
		try {
			Locale.setDefault(Locale.US);
			if (local && Boolean.getBoolean("SpbAU")) {
				br = new BufferedReader(new FileReader(file + ".in"));
				out = new PrintWriter(System.out);
			} else {
				br = new BufferedReader(new InputStreamReader(System.in));
				out = new PrintWriter(System.out);
			}
			tok = new StringTokenizer("");
			while (hasNext()) {
				solve();
			}
		} catch (Exception e) {
			e.printStackTrace();
			System.exit(1);
		}
		out.close();
	}

	boolean hasNext() throws IOException {
		while (!tok.hasMoreElements()) {
			String line = br.readLine();
			if (line == null) {
				return false;
			}
			tok = new StringTokenizer(line);
		}
		return true;
	}

	String next() throws IOException {
		if (hasNext()) {
			return tok.nextToken();
		}
		System.err.println("No more tokens");
		System.exit(1);
		return "";
	}

	int nextInt() throws IOException {
		return Integer.parseInt(next());
	}

	long nextLong() throws IOException {
		return Long.parseLong(next());
	}

	double nextDouble() throws IOException {
		return Double.parseDouble(next());
	}
}
