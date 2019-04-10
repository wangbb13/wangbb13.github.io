/*
 * create time : 2019-03-27
 * author : wangbb13
 */
import java.io.Writer;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.io.BufferedWriter;
import java.io.IOException;
import java.util.Set;
import java.util.List;
import java.util.ArrayList;
// import java.util.HashSet;

public class Store {
    private FileWriter fw;
    private PrintWriter pw;
    private BufferedWriter bw;
    private int bufferSize;

    public Store(String filename) {
        bufferSize = 1 << 20;
        try {
            fw = new FileWriter(filename);
            pw = new PrintWriter(fw);
            bw = new BufferedWriter(fw, bufferSize);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void writelnWithPW(long i, Set<Long> adj) {
        if (!adj.isEmpty()) {
            pw.print(i);
            for (Long n : adj) {
                // pw.printf(" %d", n);
                pw.print(" ");
                pw.print(n);
            }
            pw.println();
        }
    }

    public void writelnWithBW(long i, Set<Long> adj) {
        if (!adj.isEmpty()) {
            try {
                bw.write(Long.toString(i));
                for (long n : adj) {
                    bw.write(" ");
                    bw.write(Long.toString(n));
                }
                // bw.write("\n");
                bw.newLine();
            } catch (IOException ioe) {

            }
        }
    }

    public void writeln(long i, Set<Long> adj) {
        // writelnWithPW(i, adj);
        writelnWithBW(i, adj);
    }

    public void flush() {
        try {
            bw.flush();
        } catch (IOException ioe) {

        }
        // pw.flush();
    }

    public void close() {
        try {
            pw.close();
            fw.close();
            bw.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}