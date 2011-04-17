import java.io.*;
import java.math.*;
import java.util.*;

public class Main implements Runnable {
	boolean local = true;
	String filename = "p9";

	ArrayList<Integer>[] edges;
	ArrayList<Integer> topsorted;
	boolean[] visited;
	int[] order;

	void topsort(int u) {
		visited[u] = true;
		for (int to : edges[u]) {
			if (!visited[to]) {
				topsort(to);
			}
		}
		order[u] = topsorted.size();
		topsorted.add(u);
	}

	private void solve() throws IOException {
		int n = nextInt();
		edges = new ArrayList[n];
		visited = new boolean[n];
		order = new int[n];
		topsorted = new ArrayList<Integer>();
		for (int i = 0; i < n; ++i) {
			edges[i] = new ArrayList<Integer>(0);
		}
		int m = nextInt();
		for (int i = 0; i < m; ++i) {
			int a = nextInt() - 1;
			int b = nextInt() - 1;
			edges[a].add(b);
		}
		boolean ok = true;
		for (int u = 0; u < n; ++u) {
			if (!visited[u]) {
				topsort(u);
			}
		}
		Collections.reverse(topsorted);
		for (int u = 0; u < n; ++u) {
			for (int to : edges[u]) {
				if (order[to] >= order[u]) {
					ok = false;
				}
			}
		}
		if (!ok) {
			out.println(-1);
		} else {
			for (int u : topsorted) {
				out.print((u + 1) + " ");
			}
			out.println();
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

