/*
 * create time : 2019-04-06 22:03
 * author : wangbb13
 */
import java.util.Set;
import java.util.HashSet;
import java.util.Map;
import java.util.HashMap;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;

public class Streaming {
    public void copyFiles(File source, File dest) {
        try {
            Files.copy(source.toPath(), dest.toPath());
        } catch (IOException ioe) {
            ioe.printStackTrace();
        }
    }

    public void genPWL(String[] args) {
        if (args.length != 10) {
            System.out.println("usage: java Streaming ilambda idmin idmax olambda odmin odmax nodes edges filename gr");
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
        double generationRate = Double.parseDouble(args[9]);
        
        String[] splitStr = filename.split("\\.");
        String basename = splitStr[0];
        String suffix = splitStr[1];

        Map<String, Double> iTheta = new HashMap<String, Double>();
        iTheta.put("lambda", iLambda);
        Map<String, Double> oTheta = new HashMap<String, Double>();
        oTheta.put("lambda", oLambda);
        
        PowerLaw iPL = new PowerLaw(idMin, idMax, nNodes, nEdges, iTheta);
        iPL.preProcess(false);

        // generation
        int fileNo = 0;
        File sourceFile = new File(filename);
        long actualEdges = 0, iterEdges = 0;
        double curRate = generationRate;
        Store store = new Store(filename, 1 << 20);
        Set<Long> adj = new HashSet<Long>();
        OutDegreeDistribution preOdd = null;
        do {
            iterEdges = 0;
            int involvedN = Math.min((int)(curRate * nNodes), (int)nNodes);
            int involvedE = Math.min((int)(curRate * nEdges), (int)nEdges);
            int startNodeID = (int)nNodes - (int)involvedN;
            OutDegreeDistribution curOdd = new OutPowerLaw((int)odMin, (int)odMax, involvedN, involvedE, oTheta);
            DeltaOutDistribution dod = new DeltaOutDistribution(preOdd, curOdd);
            dod.setBucket(2);
            for (int i = 0; i < involvedN; ++i) {
                int outDegree = dod.getOutDegree(i);
                while (adj.size() < outDegree) {
                    long t = iPL.genTargetID();
                    if ((int)t < startNodeID) {
                        continue;
                    }
                    adj.add(t);
                }
                actualEdges += adj.size();
                iterEdges += adj.size();
                int nodeId = startNodeID + i;
                store.writeln(nodeId, adj);
                adj.clear();
            }
            // copy file
            store.flush();
            String newFilename = basename + "_" + String.valueOf(fileNo) + "." + suffix;
            File destFile = new File(newFilename);
            copyFiles(sourceFile, destFile);
            fileNo++;
            // end copying
            System.out.println("Iteration " + String.valueOf(curRate) + " : " + String.valueOf(iterEdges));
            curRate += generationRate;
            preOdd = curOdd;
        } while (curRate < 1.0);
        // end
        System.out.println("actual number of edges = " + String.valueOf(actualEdges));
        System.out.println("expected number of edges = " + String.valueOf(nEdges));
    }

    public static void main(String[] args) {
        long start = System.nanoTime();
        Streaming gen = new Streaming();
        gen.genPWL(args);
        long end = System.nanoTime();
        long totalTime = end - start;
        System.out.println("Total running time : ");
        System.out.println(String.valueOf(totalTime) + " ns.");
        System.out.println(String.valueOf(totalTime * 1.0 / 1e9) + " s.");
    }
}
