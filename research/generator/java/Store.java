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
                pw.printf(" %d", n);
            }
            pw.println();
        }
    }

    public void writelnWithBW(long i, Set<Long> adj) {
        if (!adj.isEmpty()) {
            String ans = String.valueOf(i);
            for (Long n : adj) {
                ans = ans + " " + String.valueOf(n);
            }
            ans = ans + "\n";
            write(ans, bw);
        }
    }

    private static void write(String record, Writer writer) {
        try {
            writer.write(record);
            writer.flush();
        } catch (IOException ie) {

        }
    }

    public void writeln(long i, Set<Long> adj) {
        writelnWithPW(i, adj);
        // writelnWithBW(i, adj);
    }

    public void flush() {
        pw.flush();
        // bw.flush();
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