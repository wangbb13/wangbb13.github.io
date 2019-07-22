/*
 * create time : 2019-07-09 15:45
 * author : wangbb13
 */
import java.io.File;
import java.io.IOException;
import java.util.Map;
import java.util.Set;
import java.util.List;
import java.util.Random;
import java.util.HashMap;
import java.util.HashSet;
import java.util.ArrayList;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

public class Generation {
    private String jsonFilename;
    private JSONObject jsonObj;
    private Random rand;

    public Generation(String filename) {
        jsonFilename = filename;
        LoadJson lj = new LoadJson(filename);
        jsonObj = lj.load();
        rand = new Random();
    }

    public void run() {
        // mkdir
        String graph = (String)jsonObj.get("graph");
        mkdir(graph);
        // vss
        List<Object> vss = (ArrayList<Object>)jsonObj.get("node");
        Map<String, Long> vLabelAmount = new HashMap<String, Long>();
        for (int i = 0; i < vss.size(); ++i) {
            String vLabel = (String)(((Map)vss.get(i)).get("label"));
            long amount = (Long)(((Map)vss.get(i)).get("amount"));
            vLabelAmount.put(vLabel, amount);
        }
        // ess, generate
        List<Object> ess = (ArrayList<Object>)jsonObj.get("edge");
        for (int i = 0; i < ess.size(); ++i) {
            String eLabel = (String)(((Map)ess.get(i)).get("label"));
            String vSource = (String)(((Map)ess.get(i)).get("source"));
            String vTarget = (String)(((Map)ess.get(i)).get("target"));
            long nEdges = (Long)(((Map)ess.get(i)).get("amount"));
            
            Map inDist = (Map)(((Map)ess.get(i)).get("in"));
            Map outDist = (Map)(((Map)ess.get(i)).get("out"));
            String inDType = (String)inDist.get("type");
            String outDType = (String)outDist.get("type");
            Map<String, Double> outParams = getParams(outDist);
            Map<String, Double> inParams = getParams(inDist);
            long sNodes = vLabelAmount.get(vSource);
            long tNodes = vLabelAmount.get(vTarget);
            String dumpFilename = graph + "/" + eLabel + "_" + vSource + "_" + vTarget + ".adj";

            if (((Map)ess.get(i)).containsKey("community")) {
                Map commDist = (Map)(((Map)ess.get(i)).get("community"));
                Map<String, Double> commParams = new HashMap<String, Double>();
                commParams.put("n", (Long)(commDist.get("amount")) + 0.0);
                commParams.put("lambda", (Double)(commDist.get("lambda")));
                commParams.put("rho", (Double)(commDist.get("rho")));
                socialGraph(outParams, inParams, inDType, outDType, commParams, sNodes, tNodes, nEdges, dumpFilename);
            } else {
                simpleGraph(outParams, inParams, inDType, outDType, sNodes, tNodes, nEdges, dumpFilename);
            }
            // TODO: streaming 
            if (((Map)ess.get(i)).containsKey("gr")) {
                Double gr = (Double)(((Map)ess.get(i)).get("gr"));
            }
        }
        // done
        System.out.println("Generation end. ");
    }

    private Map<String, Double> getParams(Map input) {
        Map<String, Double> params = new HashMap<String, Double>();
        params.put("min-d", (Long)(input.get("min-d")) + 0.0);
        params.put("max-d", (Long)(input.get("max-d")) + 0.0);
        if (input.containsKey("lambda")) {
            params.put("lambda", (Double)(input.get("lambda")));
        } else if (input.containsKey("mu")) {
            params.put("mu", (Double)(input.get("mu")));
        } else if (input.containsKey("sigma")) {
            params.put("sigma", (Double)(input.get("sigma")));
        }
        return params;
    }

    private void simpleGraph(Map<String, Double> outParams, Map<String, Double> inParams, String inDType, String outDType, 
                             long sNodes, long tNodes, long nEdges, String filename) {
        long idMin = inParams.get("min-d").longValue();
        long idMax = inParams.get("max-d").longValue();
        long odMin = outParams.get("min-d").longValue();
        long odMax = outParams.get("max-d").longValue();
        Distribution outDist = getDist(odMin, odMax, sNodes, nEdges, outParams, true, outDType);
        Distribution inDist = getDist(idMin, idMax, tNodes, nEdges, inParams, false, inDType);

        long actualEdges = 0;
        Store store = new Store(filename, 1 << 21);
        Set<Long> adj = new HashSet<Long>();

        double progress = 0.0;
        System.out.print("[ 0% ] ... \t");
        for (long i = 0; i < sNodes; ++i) {
            if (i * 1.0 / sNodes * 1.0 - progress > 0.01) { 
                progress += 0.01;
                System.out.printf("[ %d%% ] ... \t", (int)(progress * 100));
            }
            long outDegree = outDist.genOutDegree(i);
            for (long j = 0; j < outDegree; ++j) {
                long t = inDist.genTargetID();
                adj.add(t);
            }
            actualEdges += adj.size();
            store.writeln(i, adj);
            adj.clear();
        }
        store.close();
	System.out.println();

	System.out.printf("# of source nodes = %d, # of target nodes = %d. \n", sNodes, tNodes);
        System.out.println("actual number of edges = " + String.valueOf(actualEdges));
        System.out.println("expected number of edges = " + String.valueOf(nEdges));
    }

    private void socialGraph(Map<String, Double> outParams, Map<String, Double> inParams, String inDType, String outDType, 
                             Map<String, Double> commParams, long sNodes, long tNodes, long nEdges, String filename) {
        long actualEdges = 0;
        long extraEdges = 0;
        Store store = new Store(filename, 1 << 21);

        int nCom = commParams.get("n").intValue();
        double cLambda = commParams.get("lambda");
        double rho = commParams.get("rho");
        Set<Long> adj = new HashSet<Long>();
        int[][] split = Utility.splitCommunity((int)sNodes, (int)tNodes, nCom, cLambda);
        int anComms = split.length;
        System.out.println("# Communities = " + String.valueOf(anComms));

        long idMin = inParams.get("min-d").longValue();
        long idMax = inParams.get("max-d").longValue();
        long odMin = outParams.get("min-d").longValue();
        long odMax = outParams.get("max-d").longValue();
        Map<Integer, Distribution> rowDistr = new HashMap<Integer, Distribution>();
        Map<Integer, Distribution> colDistr = new HashMap<Integer, Distribution>();
        Map<Integer, PowerLaw> colPowerLaw = new HashMap<Integer, PowerLaw>();
        for (int i = 0; i < split.length; ++i) {
            if (!rowDistr.containsKey(split[i][0])) {
                long subEdges = Math.round(split[i][0] * 1.0 / sNodes * nEdges);
                
                Distribution oDist = getDist(odMin, odMax, split[i][0], subEdges, outParams, true, outDType);
                rowDistr.put(split[i][0], oDist);
                
                // if (outDType.equals("power_law")) {
                //     PowerLaw oPL = new PowerLaw(odMin, odMax, split[i][0], subEdges, outParams);
                //     oPL.preProcess(true);
                //     rowDistr.put(split[i][0], oPL);
                // } else if (outDType.equals("gaussian")) {
                //     Gaussian oGs = new Gaussian(odMin, odMax, split[i][0], subEdges, outParams);
                //     oGs.preProcess(true);
                //     rowDistr.put(split[i][0], oGs);
                // } else if (outDType.equals("lognormal")) {
                //     LogNormal iLg = new LogNormal(odMin, odMax, split[i][0], subEdges, outParams);
                //     oLg.preProcess(true);
                //     rowDistr.put(split[i][0], oLg);
                // } else if (outDType.equals("uniform")) {
                //     Uniform oUf = new Uniform(odMin, odMax, split[i][0], subEdges, outParams);
                //     rowDistr.put(split[i][0], oUf);
                // } else {
                //     System.out.printf("Unkown Out-Distribution: %s \n", outDType);
                // }
            }
            if (!colDistr.containsKey(split[i][1])) {
                long subEdges = Math.round(split[i][1] * 1.0 / tNodes * nEdges);
                
                PowerLaw iPL = new PowerLaw(idMin, idMax, split[i][1], subEdges, inParams);
                iPL.preProcess(false);
                colPowerLaw.put(split[i][1], iPL);
                
                Distribution iDist = getDist(idMin, idMax, split[i][1], subEdges, inParams, false, inDType);
                colDistr.put(split[i][1], iDist);

                // if (inDType.equals("power_law")) { 
                //     colDistr.put(split[i][1], iPL);
                // } else if (inDType.equals("gaussian")) {
                //     Gaussian iGs = new Gaussian(idMin, idMax, split[i][1], subEdges, inParams);
                //     iGs.preProcess(false);
                //     colDistr.put(split[i][1], iGs);
                // } else if (inDType.equals("lognormal")) {
                //     LogNormal iLg = new LogNormal(idMin, idMax, split[i][1], subEdges, inParams);
                //     iLg.preProcess(false);
                //     colDistr.put(split[i][1], iLg);
                // } else if (inDType.equals("uniform")) {
                //     Uniform iUf = new Uniform(idMin, idMax, split[i][1], subEdges, inParams);
                //     colDistr.put(split[i][1], iUf);
                // } else {
                //     System.out.printf("Unkown In-Distribution: %s \n", inDType);
                // }
            }
        }

        int cumuRow = 0;
        int cumuCol = 0;
        int spRowI = 0;
        int spColJ = 0;

	double progress = 0.0;
        System.out.print("[ 0% ] ... \t");
        for (long i = 0; i < sNodes; ++i) {
	    if (i * 1.0 / sNodes * 1.0 - progress > 0.01) { 
                progress += 0.01;
                System.out.printf("[ %d%% ] ... \t", (int)(progress * 100));
            }

            cumuRow++;
            if (cumuRow > split[spRowI][0]) {
                spRowI++;
                if (spRowI >= anComms) spRowI = anComms - 1;
                cumuRow = 1;
            }
            Distribution oPL = rowDistr.get(split[spRowI][0]);
            long mainOutDegree = oPL.genOutDegree(cumuRow - 1);
            int extraOutDegree = 0;
            if (rand.nextDouble() < rho)
                extraOutDegree = extraDegree(odMax - mainOutDegree + 10, rho + 1.0);

            cumuCol = 0;
            spColJ = 0;
	    while (spColJ < anComms) {
                int num;
                if (spColJ == spRowI) { // main diagonal
                    num = (int)mainOutDegree;
                } else {
                    num = (int)Math.round(extraOutDegree * 1.0 * split[spColJ][1] / (1.0 * (tNodes - split[spRowI][1])));
                }
                
                // origin
                Distribution iPL = colDistr.get(split[spColJ][1]);
                while (adj.size() < num) {
                    long t = iPL.genTargetID();
                    adj.add(t + cumuCol);
                }
                
                // uniform 
                // if (spColJ == spRowI) {
                //     Distribution iPL = colDistr.get(split[spColJ][1]);
                //     while (adj.size() < num) {
                //         long t = iPL.genTargetID();
                //         adj.add(t + cumuCol);
                //     }
                // } else {
                //     int size = split[spColJ][1];
                //     while (adj.size() < num) {
                //         long t = (long)rand.nextInt(size);
                //         adj.add(t + cumuCol);
                //     }
                // }
                
                // power_law 
                // if (spColJ == spRowI) {
                //     Distribution iPL = colDistr.get(split[spColJ][1]);
                //     while (adj.size() < num) {
                //         long t = iPL.genTargetID();
                //         adj.add(t + cumuCol);
                //     }
                // } else {
                //     PowerLaw iPL = colPowerLaw.get(split[spColJ][1]);
                //     while (adj.size() < num) {
                //         long t = iPL.genTargetID();
                //         adj.add(t + cumuCol);
                //     }
                // }

                // connected
                // if (spColJ == anComms - 1) 
                //     adj.add(tNodes - 1);

                actualEdges += adj.size();
                if (spColJ != spRowI) {
                    extraEdges += adj.size();
                }
                store.writeln(i, adj);

                adj.clear();
                cumuCol += split[spColJ][1];
                spColJ++;
            }
        }
        store.close();
	System.out.println();

        // end
	System.out.printf("# of source nodes = %d, # of target nodes = %d. \n", sNodes, tNodes);
        System.out.println("actual number of edges = " + String.valueOf(actualEdges));
        System.out.println("extra number of edges = " + String.valueOf(extraEdges));
        System.out.println("expected number of edges = " + String.valueOf(nEdges));
    }

    private void streamingGraph() {
        // TODO: streaming graph generation
    }

    private Distribution getDist(long mid, long mxd, long n, long m, Map<String, Double> params, boolean outPP, String dType) {
        Distribution ans;
        if (dType.equals("power_law")) {
            ans = new PowerLaw(mid, mxd, n, m, params);
            ans.preProcess(outPP);
        } else if (dType.equals("gaussian")) {
            ans = new Gaussian(mid, mxd, n, m, params);
            ans.preProcess(outPP);
        } else if (dType.equals("lognormal")) {
            ans = new LogNormal(mid, mxd, n, m, params);
            ans.preProcess(outPP);
        } else if (dType.equals("uniform")) {
            ans = new Uniform(mid, mxd, n, m, params);
        } else {
            ans = null;
            System.out.printf("Unkown Distribution: %s \n", dType);
        }
        return ans;
    }

    private int extraDegree(long maxDegree, double c) {
        double a = Math.exp(-1.0 / c);
        double b = a - Math.exp(-maxDegree * 1.0 / c);
        double y = rand.nextDouble();
        return Math.max((int)(-c * Math.log(a - y * b)), 0);
    }

    private void mkdir(String path) {
        File theDir = new File(path);
        if (!theDir.exists()) {
            try {
                theDir.mkdir();
            } catch (SecurityException se) {
                se.printStackTrace();
            }
        }
    }
}
