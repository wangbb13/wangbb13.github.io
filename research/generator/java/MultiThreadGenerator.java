/*
 * create time : 2019-03-27 22:54
 * author : wangbb13
 */
import java.util.Map;
import java.util.HashMap;
import java.util.Set;
import java.util.HashSet;

class Single extends Thread {
    private Thread t;
    private int startId;
    private Distribution distrIn;
    private Distribution distrOut;
    private String threadName;
    // private Store store;
    private int rowLId;
    private int rowRId;
    
    // for statistic time
    private long startTime;
    private int nThreads;
    private static int done = 0;

    public Single(int iid, Distribution in, Distribution out, String file, int lId, int rId, long sTime, int threads) {
        startId = iid;
        distrIn = in;
        distrOut = out;
        threadName = String.valueOf(iid);
        // store = new Store(file);
        t = new Thread(this, threadName);
        rowLId = lId;
        rowRId = rId;
        // for statistic time
        startTime = sTime;
        nThreads = threads;
    }

    public void run() {
        Set<Long> adj = new HashSet<Long>();
        for (int sid = rowLId; sid < rowRId; ++sid) {
            long outDegree = distrOut.genOutDegree(sid);
            while (adj.size() < outDegree) {
                long t = distrIn.genTargetID();
                adj.add(t);
            }
            // store.writeln(sid, adj);
            adj.clear();
        }
        // store.close();
        // for statistic time
        synchronized (Single.class) {
            done++;
            if (done == nThreads) {
                long end = System.nanoTime();
                long totalTime = end - startTime;
                System.out.println("Total running time: ");
                System.out.println(String.valueOf(totalTime) + " ns.");
                double sec = totalTime * 1.0 / 1e9;
                System.out.println(String.valueOf(sec) + " s.");
            }
        }
    }

    public void start() {
        if (t != null) {
            t.start();
        }
    }
}

public class MultiThreadGenerator {
    public void genPWL(String[] args, long sTime) {
        // System.out.println(args.length);
        if (args.length != 10) {
            System.out.println("usage: java MultiThreadGenerator ilambda idmin idmax olambda odmin odmax nodes edges filename threads");
            return;
        }
        double iLambda = Double.parseDouble(args[0]);
        long idMin = Long.parseLong(args[1]);
        long idMax = Long.parseLong(args[2]);
        double oLambda = Double.parseDouble(args[3]);
        long odMin = Long.parseLong(args[4]);
        long odMax = Long.parseLong(args[5]);
        long nNodes = Long.parseLong(args[6]);
        long nEdges = Long.parseLong(args[7]);
        String filename = args[8];
        int nThreads = Integer.parseInt(args[9]);
        
        Map<String, Double> iTheta = new HashMap<String, Double>();
        iTheta.put("lambda", iLambda);
        Map<String, Double> oTheta = new HashMap<String, Double>();
        oTheta.put("lambda", oLambda);
        
        PowerLaw iPL = new PowerLaw(idMin, idMax, nNodes, nEdges, iTheta);
        iPL.preProcess(false);

        PowerLaw oPL = new PowerLaw(odMin, odMax, nNodes, nEdges, oTheta);
        oPL.preProcess(true);
        oPL.setOutBucket(nThreads);

        // generation
        Single[] threads = new Single[nThreads];
        int[] split = oPL.splitSourceNodes(nThreads);
        for (int i = 0; i < nThreads; ++i) {
            String file = filename + "_" + String.valueOf(i);
            threads[i] = new Single(i, iPL, oPL, file, split[i], split[i + 1], sTime, nThreads);
        }
        for (int i = 0; i < nThreads; ++i) {
            threads[i].start();
        }

        for (int i = 0; i < nThreads; ++i) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {

            }
        }
        // end
        // System.out.println("actual number of edges = " + String.valueOf(actualEdges));
        // System.out.println("expected number of edges = " + String.valueOf(nEdges));
    }

    public static void main(String[] args) {
        long start = System.nanoTime();
        MultiThreadGenerator gen = new MultiThreadGenerator();
        gen.genPWL(args, start);
        // long end = System.nanoTime();
        // long totalTime = end - start;
        // System.out.println("Total running time: ");
        // System.out.println(String.valueOf(totalTime) + " ns.");
        // double sec = totalTime * 1.0 / 1e9;
        // System.out.println(String.valueOf(sec) + " s.");
    }
}