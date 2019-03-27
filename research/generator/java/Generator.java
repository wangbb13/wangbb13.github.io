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
        if (args.length != 10) {
            System.out.println("usage: ./main ilambda idmin idmax olambda odmin odmax nodes edges filename");
        }
        double iLambda = Double.parseDouble(args[1]);
        long idMin = Long.parseLong(args[2]);
        long idMax = Long.parseLong(args[3]);
        double oLambda = Double.parseDouble(args[4]);
        long odMin = Long.parseLong(args[5]);
        long odMax = Long.parseLong(args[6]);
        long nNodes = Long.parseLong(args[7]);
        long nEdges = Long.parseLong(args[8]);
        String filename = args[9];
        
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
        Store store = new Store(filename);
        Set<Long> adj = new HashSet<Long>();
        for (long i = 0; i < nNodes; ++i) {
            long outDegree = oPL.genOutDegree(i);
            for (long j = 0; j < outDegree; ++j) {
                long t = iPL.genTargetID();
                adj.add(t);
            }
            store.writeln(i, adj);
            adj.clear();
        }
        store.close();
        // end
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