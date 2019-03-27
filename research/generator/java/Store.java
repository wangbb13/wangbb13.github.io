/*
 * create time : 2019-03-27
 * author : wangbb13
 */
import java.io.IOException;
import java.io.PrintWriter;
import java.io.FileWriter;
import java.util.Set;
// import java.util.HashSet;

public class Store {
    private FileWriter fw;
    private PrintWriter pw;

    public Store(String filename) {
        try {
            fw = new FileWriter(filename);
            pw = new PrintWriter(fw);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void writeln(long i, Set<Long> adj) {
        if (!adj.isEmpty()) {
            try {
                pw.print(i);
                for (Long n : adj) {
                    pw.print(" ");
                    pw.print(n);
                }
                pw.println();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public void close() {
        try {
            pw.close();
            fw.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}