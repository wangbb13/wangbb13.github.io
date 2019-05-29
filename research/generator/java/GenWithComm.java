/*
 * create time : 2019-03-28 10:23
 * author : wangbb13
 */
import java.util.Map;
import java.util.HashMap;
import java.util.Set;
import java.util.HashSet;
import java.util.Random;

public class GenWithComm {
    private Random rand;

    public GenWithComm() {
        rand = new Random();
    }

    public int extraDegree(long maxDegree, double c) {
        double a = Math.exp(-1.0 / c);
        double b = a - Math.exp(-maxDegree * 1.0 / c);
        double y = rand.nextDouble();
        return Math.max((int)(-c * Math.log(a - y * b)), 0);
    }

    public void genPWL(String[] args) {
        // System.out.println(args.length);
        if (args.length != 12) {
            System.out.println("usage: java GenWithComm ilambda idmin idmax olambda odmin odmax nodes edges filename comms clambda param-c");
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
        int nCom = Integer.parseInt(args[9]);
        double cLambda = Double.parseDouble(args[10]);
        double pC = Double.parseDouble(args[11]);
        double rho = pC - 1.0;
        
        Map<String, Double> iTheta = new HashMap<String, Double>();
        iTheta.put("lambda", iLambda);
        Map<String, Double> oTheta = new HashMap<String, Double>();
        oTheta.put("lambda", oLambda);
        
        // generation
        long actualEdges = 0;
        long extraEdges = 0;
        Store store = new Store(filename, 1 << 21);

        // record statistics 
        // Store stats = new Store("stats.txt", 1 << 21);

        Set<Long> adj = new HashSet<Long>();
        int[][] split = Utility.splitCommunity((int)nNodes, (int)nNodes, nCom, cLambda);
        int anComms = split.length;

        // record the comm size
        // for (int i = 0; i < split.length; ++i) {
        //     for (int j = 0; j < split[0].length; ++j) 
        //         stats.write(split[i][j]);
        //     stats.newLine();
        // }

        // build Distributions
        Map<Integer, PowerLaw> rowDistr = new HashMap<Integer, PowerLaw>();
        Map<Integer, PowerLaw> colDistr = new HashMap<Integer, PowerLaw>();
        for (int i = 0; i < split.length; ++i) {
            if (!rowDistr.containsKey(split[i][0])) {
                long subEdges = Math.round(split[i][0] * 1.0 / nNodes * nEdges);
                PowerLaw oPL = new PowerLaw(odMin, odMax, split[i][0], subEdges, oTheta);
                oPL.preProcess(true);
                rowDistr.put(split[i][0], oPL);
            }
            if (!colDistr.containsKey(split[i][1])) {
                long subEdges = Math.round(split[i][1] * 1.0 / nNodes * nEdges);
                PowerLaw iPL = new PowerLaw(idMin, idMax, split[i][1], subEdges, iTheta);
                iPL.preProcess(false);
                colDistr.put(split[i][1], iPL);
            }
        }
        // end
        int cumuRow = 0;
        int cumuCol = 0;
        int spRowI = 0;
        int spColJ = 0;
        for (long i = 0; i < nNodes; ++i) {
            cumuRow++;
            if (cumuRow > split[spRowI][0]) {
                spRowI++;
                cumuRow = 1;
            }
            PowerLaw oPL = rowDistr.get(split[spRowI][0]);
            long mainOutDegree = oPL.genOutDegree(cumuRow - 1);
            int extraOutDegree = 0;
            if (rand.nextDouble() < rho)
                extraOutDegree = extraDegree(odMax - mainOutDegree + 20, pC);

            // statistics info 
            // stats.write(extraOutDegree);
            // stats.newLine();

            // int eachExtraOut = (int)Math.ceil(extraOutDegree * 1.0 / anComms);
            cumuCol = 0;
            spColJ = 0;
            while (spColJ < anComms) {
                int num;
                if (spColJ == spRowI) { // main diagonal
                    num = (int)mainOutDegree;
                } else {
                    if (rand.nextDouble() > 0.6) {
                        // num = eachExtraOut;
                        num = (int)Math.ceil(extraOutDegree * split[spColJ][1] / (nNodes - split[spRowI][1]));
                    } else {
                        num = 0;
                    }
                }
                
                // power-law
                // PowerLaw iPL = colDistr.get(split[spColJ][1]);
                // while (adj.size() < num) {
                //     long t = iPL.genTargetID();
                //     adj.add(t + cumuCol);
                // }
                // uniform 
                if (spColJ == spRowI) {
                    PowerLaw iPL = colDistr.get(split[spColJ][1]);
                    while (adj.size() < num) {
                        long t = iPL.genTargetID();
                        adj.add(t + cumuCol);
                    }
                } else {
                    int size = split[spColJ][1];
                    while (adj.size() < num) {
                        long t = (long)rand.nextInt(size);
                        adj.add(t + cumuCol);
                    }
                }

                actualEdges += adj.size();
                if (spColJ != spRowI) {
                    extraEdges += adj.size();
                }
                store.writeln(i, adj);

                // record statistics
                // if (spColJ != spRowI) 
                //     stats.writeln(i, adj);

                adj.clear();
                cumuCol += split[spColJ][1];
                spColJ++;
            }
        }
        store.close();

        // record statistics
        // stats.close();

        // end
        System.out.println("actual number of edges = " + String.valueOf(actualEdges));
        System.out.println("extra number of edges = " + String.valueOf(extraEdges));
        System.out.println("expected number of edges = " + String.valueOf(nEdges));
    }

    public static void main(String[] args) {
        long start = System.nanoTime();
        GenWithComm gen = new GenWithComm();
        gen.genPWL(args);
        long end = System.nanoTime();
        long totalTime = end - start;
        System.out.println("Total running time: ");
        System.out.println(String.valueOf(totalTime) + " ns.");
        double sec = totalTime * 1.0 / 1e9;
        System.out.println(String.valueOf(sec) + " s.");
    }
}
