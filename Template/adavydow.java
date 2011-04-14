import java.io.*;
import java.math.*;
import java.util.*;

public class Main implements Runnable {
	boolean local = true;
	String filename = "";

	private void solve() throws IOException {
		// TODO write code here
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
			if (Boolean.getBoolean("SpbAU") && local) {
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

