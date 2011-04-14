import java.io.*;
import java.math.*;
import java.util.*;

public class Main implements Runnable {
	boolean local = false;
	String filename = "m9";
	int[] tIn;
	int[] minA;
	boolean[] visited;
	int cTime;
	ArrayList<Integer>[] edges;
	ArrayList<Integer> cutpoints;

	@SuppressWarnings("unchecked")
	void initGraph() {
		tIn = new int[vn];
		minA = new int[vn];
		visited = new boolean[vn];
		edges = new ArrayList[vn];
		for (int i = 0; i < vn; ++i) {
			edges[i] = new ArrayList<Integer>(0);
		}
		cutpoints = new ArrayList<Integer>();
	}

	int vn;

	void findCutpoints(int u, int pre) {
		visited[u] = true;
		tIn[u] = minA[u] = cTime++;
		int n = 0;
		int max = minA[u] - 1;
		for (int to : edges[u]) {
			if (to == pre) {
				continue;
			}
			if (visited[to]) {
				minA[u] = Math.min(minA[u], tIn[to]);
			} else {
				findCutpoints(to, u);
				minA[u] = Math.min(minA[u], minA[to]);
				++n;
				max = Math.max(max, minA[to]);
			}
		}
		if (pre == -1) {
			if (n > 1) {
				cutpoints.add(u + 1);
			}
		} else {
			if (max >= tIn[u]) {
				cutpoints.add(u + 1);
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
			edges[a].add(b);
			edges[b].add(a);
		}
		for (int u = 0; u < vn; ++u) {
			if (!visited[u]) {
				findCutpoints(u, -1);
			}
		}
		Collections.sort(cutpoints);
		out.println(cutpoints.size());
		for (int point : cutpoints) {
			out.println(point);
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
			if (local &&Boolean.getBoolean("SpbAU")) {
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
