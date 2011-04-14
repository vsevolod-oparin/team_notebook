import java.io.*;
import java.math.*;
import java.util.*;

public class Main implements Runnable {
	boolean local = true;
	String filename = "k9";

	int[] tIn;
	int[] minA;
	int cTime;
	boolean[] visited;
	ArrayList<Integer> bridges;
	ArrayList<int[]>[] edges;
	final int ESIZE = 2;
	final int TO = 0;
	final int ID = 1;

	int vn;

	@SuppressWarnings("unchecked")
	void initGraph() {
		tIn = new int[vn];
		minA = new int[vn];
		visited = new boolean[vn];
		bridges = new ArrayList<Integer>();
		edges = new ArrayList[vn];
		for (int i = 0; i < vn; ++i) {
			edges[i] = new ArrayList<int[]>();
		}
	}

	void findBridges(int u, int pre) {
		visited[u] = true;
		tIn[u] = minA[u] = cTime++;
		for (int[] edge : edges[u]) {
			if (edge[ID] == pre) {
				continue;
			}
			int to = edge[TO];
			if (visited[to]) {
				minA[u] = Math.min(minA[u], tIn[to]);
			} else {
				findBridges(to, edge[ID]);
				minA[u] = Math.min(minA[u], minA[to]);
				if (minA[to] > tIn[u]) {
					bridges.add(edge[ID]);
				}
			}
		}
	}

	private void solve() throws IOException {
		vn = nextInt();
		int m = nextInt();
		initGraph();
		for (int i = 0; i < m; ++i) {
			int a = nextInt() - 1;
			int b = nextInt() - 1;
			edges[a].add(new int[] { b, i + 1 });
			edges[b].add(new int[] { a, i + 1 });
		}
		for (int i = 0; i < vn; ++i) {
			if (!visited[i]) {
				findBridges(i, -1);
			}
		}
		Collections.sort(bridges);
		out.println(bridges.size());
		for (int id : bridges) {
			out.println(id);
		}
	}

	public static void main(String[] args) {
		new Thread(new Main()).start();
	}

	BufferedReader br;
	StringTokenizer tok;
	PrintWriter out;

	@Override
	public void run() {
		try {
			if (local && Boolean.getBoolean("SpbAU")) {
				br = new BufferedReader(new FileReader(filename + ".in"));
				out = new PrintWriter(System.out);
			} else {
				br = new BufferedReader(new FileReader(filename + ".in"));
				out = new PrintWriter(filename + ".out");
			}
			tok = new StringTokenizer("");
			while (hasNext()) {
				solve();
			}
			out.checkError();
		} catch (Exception e) {
			e.printStackTrace();
			System.exit(1);
		}
	}

	private boolean hasNext() throws IOException {
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
		throw new IOException("No more tokens");
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
