import java.io.*;
import java.math.*;
import java.util.*;

public class Main implements Runnable {
	boolean local = true;
	String filename = "e9";

	ArrayList<Integer>[] edges;
	ArrayList<Integer>[] bedges;

	ArrayList<Integer> topsorted;
	boolean[] visited;
	int[] outDeg;
	int[] color;
	int cColor;

	void topsort(int u) {
		visited[u] = true;
		for (int to : bedges[u]) {
			if (!visited[to]) {
				topsort(to);
			}
		}
		topsorted.add(u);
	}

	void colorComponent(int u) {
		visited[u] = true;
		for (int to : edges[u]) {
			if (!visited[to]) {
				colorComponent(to);
			}
		}
		color[u] = cColor;
	}

	@SuppressWarnings("unchecked")
	private void solve() throws IOException {
		int n = nextInt();
		edges = new ArrayList[n];
		bedges = new ArrayList[n];
		topsorted = new ArrayList<Integer>();
		for (int i = 0; i < n; ++i) {
			edges[i] = new ArrayList<Integer>();
			bedges[i] = new ArrayList<Integer>();
		}
		color = new int[n];
		visited = new boolean[n];
		int m = nextInt();
		for (int i = 0; i < m; ++i) {
			int a = nextInt() - 1;
			int b = nextInt() - 1;
			edges[a].add(b);
			bedges[b].add(a);
		}

		for (int u = 0; u < n; ++u) {
			if (!visited[u]) {
				topsort(u);
			}
		}

		Arrays.fill(visited, false);
		Collections.reverse(topsorted);
		for (int u : topsorted) {
			if (!visited[u]) {
				colorComponent(u);
				++cColor;
			}
		}
		outDeg = new int[cColor];
		for (int u = 0; u < n; ++u) {
			for (int to : edges[u]) {
				if (color[u] != color[to]) {
					++outDeg[color[u]];
				}
			}
		}

		ArrayList<Integer> sinks = new ArrayList<Integer>();
		for (int u = 0; u < n; ++u) {
			if (outDeg[color[u]] == 0) {
				sinks.add(u);
				outDeg[color[u]] = 1;
			}
		}

		out.println(sinks.size());
		for (int u : sinks) {
			out.print((u + 1) + " ");
		}
		out.println();
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
			if (false && Boolean.getBoolean("SpbAU") && local) {
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

