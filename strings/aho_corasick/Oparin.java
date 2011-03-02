import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.*;

public class Oparin implements Runnable {

    Scanner in;
    PrintWriter out;

    String alphabet;
    Map<Character, Integer> num;
    int SIZE;

    class Vertex {

        int from;
        int number;

        Vertex[] child;
        Vertex parent;
        Vertex link;

        boolean leaf;
        Boolean bad;
        boolean root;

        Vertex() {
            this.from = SIZE;
            this.link = this;
            this.parent = this;
            this.child = new Vertex[SIZE];
            this.bad = false;
            this.root = true;
        }

        Vertex(char c, Vertex parent) {
            this.from = num.get(c);
            this.parent = parent;
            this.child = new Vertex[SIZE];
        }

        Vertex goBy(int symbol) {
            if (child[symbol] == null && root) {
                return this;
            }
            return child[symbol] == null ? link.goBy(symbol) : child[symbol];
        }

        boolean isBad() {
            if (bad == null) {
                bad = leaf || link.isBad();
            }
            return bad;
        }

        Vertex getLink() {
            if (link != null) {
                return link;
            }
            if (parent.root) {
                return link = parent;
            }
            Vertex i = parent.getLink();
            while (!i.root && i.child[from] == null)
                i = i.getLink();
            return link = (i.child[from] == null ? i : i.child[from]);
        }
        void print(String gap) {
            System.err.println(gap + " " + (from < SIZE ? alphabet.charAt(from) : "!") + " " + number + " " + getLink().number + " " + isBad());
            for (Vertex ch : child) {
                if (ch != null) {
                    ch.print(gap + "  ");
                }
            }
        }
    }

    class AhoCorasick {
        ArrayList<Vertex> list;
        Vertex root;
        AhoCorasick() {
            list = new ArrayList<Vertex>();
            root = new Vertex();
            root.number = 0;
            list.add(root);
        }
        void add(String word) {
            Vertex cur = root;
            for (int i = 0; i < word.length(); ++i) {
                char wc = word.charAt(i);
                int c = num.get(wc);
                if (cur.child[c] == null) {
                    cur.child[c] = new Vertex(wc, cur);
                    cur.child[c].number = list.size();
                    list.add(cur.child[c]);
                }
                cur = cur.child[c];
            }
            cur.leaf = true;
        }
        void build() {
            for (Vertex v : list) {
                v.getLink();
            }
        }
        void print() {
            root.print("");
        }


        BigInteger countSentence(int m) {
            int l = list.size();
            BigInteger[][] d = new BigInteger[m + 1][l];
            for (BigInteger[] i : d) {
                Arrays.fill(i, BigInteger.ZERO);
            }
            d[0][0] = BigInteger.ONE;
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < l; ++j) {
                    Vertex v = list.get(j);
                    if (!v.isBad() && !d[i][j].equals(BigInteger.ZERO)) {
                        for (int k = 0; k < SIZE; ++k) {
                            int to = v.goBy(k).number;
                            d[i + 1][to] = d[i + 1][to].add(d[i][j]);
                        }
                    }
                }
            }
            BigInteger ans = BigInteger.ZERO;
            for (int i = 0; i < l; ++i) {
                if (!list.get(i).isBad()) {
                    ans = ans.add(d[m][i]);
                }
            }
            return ans;
        }
    }



    private void solve() {
        int n = in.nextInt();
        int m = in.nextInt();
        int p = in.nextInt();
        alphabet = in.next();
        SIZE = alphabet.length();
        int cnt = 0;
        num = new HashMap<Character, Integer>();
        for (int i = 0; i < alphabet.length(); ++i) {
            num.put(alphabet.charAt(i), cnt++);
        }
        AhoCorasick dict = new AhoCorasick();
        for (int i = 0; i < p; ++i) {
            String word = in.next();
            dict.add(word);            
        }
        dict.build();
        //dict.print();
        out.println(dict.countSentence(m));

    }

    public static void main(String[] args) {
        (new Thread(new Oparin())).start();
    }

    public void run() {
        try {
            Locale.setDefault(Locale.US);
            //in = new Scanner(new FileReader("input.txt"));
            out = new PrintWriter(System.out);
            in = new Scanner(new InputStreamReader(System.in));
            solve();
            out.close();
        } catch (Exception e) {
            e.printStackTrace();;
            System.exit(-1);
        }
    }
}
