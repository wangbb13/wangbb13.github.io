/*
 * create time : 2019-03-27
 * author : wangbb13
 */
import java.util.Map;
import java.util.HashMap;
import java.util.Set;
import java.util.HashSet;

public class Generator {
    public void genPWL(String[] args) {
        // System.out.println(args.length);
        if (args.length != 9) {
            System.out.println("usage: java Generator ilambda idmin idmax olambda odmin odmax nodes edges filename");
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
        
        Map<String, Double> iTheta = new HashMap<String, Double>();
        iTheta.put("lambda", iLambda);
        Map<String, Double> oTheta = new HashMap<String, Double>();
        oTheta.put("lambda", oLambda);
        
        PowerLaw iPL = new PowerLaw(idMin, idMax, nNodes, nEdges, iTheta);
        iPL.preProcess(false);

        PowerLaw oPL = new PowerLaw(odMin, odMax, nNodes, nEdges, oTheta);
        oPL.preProcess(true);
        // oPL.setOutBucket(100);

        // generation
        long actualEdges = 0;
        // Store store = new Store(filename, 1 << 21);
        Set<Long> adj = new HashSet<Long>();
        for (long i = 0; i < nNodes; ++i) {
            long outDegree = oPL.genOutDegree(i);
            while (adj.size() < outDegree) {
                long t = iPL.genTargetID();
                // System.out.println(String.valueOf(t) + " ");
                adj.add(t);
            }
            actualEdges += adj.size();
            // store.writeln(i, adj);
            adj.clear();
        }
        // store.close();
        // end
        System.out.println("actual number of edges = " + String.valueOf(actualEdges));
        System.out.println("expected number of edges = " + String.valueOf(nEdges));
    }

    public static void main(String[] args) {
        long start = System.nanoTime();
        Generator gen = new Generator();
        gen.genPWL(args);
        long end = System.nanoTime();
        long totalTime = end - start;
        System.out.println("Total running time: ");
        System.out.println(String.valueOf(totalTime) + " ns.");
        double sec = totalTime * 1.0 / 1e9;
        System.out.println(String.valueOf(sec) + " s.");
    }
}