/*
 * create time : 2019-04-07 21:36
 * author : wangbb13
 */
import java.util.Map;
import java.util.HashMap;
import java.text.DecimalFormat;

public class OutDegreeDistribution {
    private int minDegree;
    private int maxDegree;
    private int degreeRange;
    private int numNodes;
    private int numEdges;
    protected Map<String, Double> theta;

    private int[] eachDegreeNums;

    public OutDegreeDistribution(int minD, int maxD, int n, int m, Map<String, Double> params) {
        minDegree = minD;
        maxDegree = maxD;
        numNodes = n;
        numEdges = m;
        // For Power-Law etc.
        if (params.containsKey("lambda")) {
            double lambda = -Math.abs(params.get("lambda"));
            params.put("lambda", lambda);
        }
        // End
        theta = new HashMap<String, Double>();
        for (Map.Entry<String, Double> entry : params.entrySet()) {
            theta.put(entry.getKey(), entry.getValue());
        }
        matchEdges();
        build();
    }

    public int getNodes() {
        return numNodes;
    }

    public int getMinDegree() {
        return minDegree;
    }

    public int getMaxDegree() {
        return maxDegree;
    }

    public int getRange() {
        return degreeRange;
    }

    public int[] getEachDegreeNums() {
        int len = eachDegreeNums.length;
        int[] ans = new int[len];
        for (int i = 0; i < len; ++i) {
            ans[i] = eachDegreeNums[i];
        }
        return ans;
    }

    public double pdf(int x) {
        return 0.0;
    }

    public int numberOfMaxDegree() {
        double maxPDF = pdf(maxDegree);
        double sumPDF = maxPDF;
        for (int i = minDegree; i < maxDegree; ++i) {
            sumPDF += pdf(i);
        }
        return (int)Math.round(numNodes * (maxPDF / sumPDF));
    }

    public int currentEdges() {
        degreeRange = maxDegree - minDegree + 1;
        double sum = 0.0;
        double[] p = new double[degreeRange];
        for (int i = minDegree; i <= maxDegree; ++i) {
            p[i - minDegree] = pdf(i);
            sum += p[i - (int)minDegree];
        }
        double alpha = numNodes / sum;
        int ans = 0;
        for (int i = 0; i < degreeRange; ++i) {
            ans += Math.round(alpha * p[i] * (i + minDegree));
        }
        return ans;
    }

    public void matchEdges() {
        // adjust maxDegree so that the number of nodes 
        // whose degree is maxDegree is equal to or more than 1
        maxDegree = Math.min(maxDegree, numNodes);
        int binL = maxDegree + 1;
        int binR = maxDegree;
        while (binR > 0 && numberOfMaxDegree() < 1) {
            binR = maxDegree;
            maxDegree /= 2;
            binL = maxDegree;
        }
        while (binL < binR) {
            maxDegree = (binL + binR) / 2;
            int num = numberOfMaxDegree();
            if (num < 1) 
                binR = maxDegree;
            else
                binL = maxDegree + 1;
        }
        maxDegree = binL - 1;
        // end adjust maxDegree
        System.out.println("=================Adjustment.========================");
        int actualEdges = currentEdges();
        System.out.println("max degree = " + String.valueOf(maxDegree) + " actual edges = " + String.valueOf(actualEdges) + " expected edges = " + String.valueOf(numEdges));
        // match the expected number of edges
        if (actualEdges < numEdges) {
            int temp = maxDegree;
            binL = binR = maxDegree + 1;
            while (maxDegree < numNodes && numberOfMaxDegree() > 0) {
                binL = maxDegree;
                maxDegree *= 2;
                binR = maxDegree;
            }
            binR = Math.min(binR, numNodes);
            while (binL < binR) {
                maxDegree = (binL + binR) / 2;
                if (numberOfMaxDegree() < 1)
                    binR = maxDegree;
                else
                    binL = maxDegree + 1;
            }
            maxDegree = binL - 1;
            actualEdges = currentEdges();
            if (actualEdges > numEdges) {
                binL = temp;
                binR = maxDegree;
                while (binL < binR) {
                    maxDegree = (binL + binR) / 2;
                    actualEdges = currentEdges();
                    if (actualEdges > numEdges) 
                        binR = maxDegree;
                    else
                        binL = maxDegree + 1;
                }
                maxDegree = binL - 1;
                actualEdges = currentEdges();
            }
        } else if (actualEdges > numEdges) {
            binL = minDegree;
            binR = maxDegree;
            while (binL < binR) {
                maxDegree = (binL + binR) / 2;
                actualEdges = currentEdges();
                if (actualEdges > numEdges)
                    binR = maxDegree;
                else
                    binL = maxDegree + 1;
            }
            maxDegree = binL - 1;
            actualEdges = currentEdges();
        }
        System.out.println("max degree = " + String.valueOf(maxDegree) + " actual edges = " + String.valueOf(actualEdges) + " expected edges = " + String.valueOf(numEdges));
        System.out.println("===============Adjustment Done.=======================");
        // end match the expected number of edges
        // update degreeRange
        degreeRange = maxDegree - minDegree + 1;
        // end update
    }

    public void build() {
        double sum = 0.0;
        double[] temp = new double[degreeRange];
        for (int i = minDegree; i <= maxDegree; ++i) {
            temp[i - minDegree] = pdf(i);
            sum += temp[i - minDegree];
        }
        double alpha = numNodes / sum;
        eachDegreeNums = new int[degreeRange];
        for (int i = 0; i < degreeRange; ++i) {
            eachDegreeNums[i] = (int)Math.round(alpha * temp[i]);
        }
    }

    public void showDegreeNums() {
        System.out.println("OutDegreeDistribution : ");
        int length = eachDegreeNums.length;
        for (int i = 0; i < length; ++i) {
            System.out.printf("%2d ", eachDegreeNums[i]);
        }
        System.out.println();
        for (int i = 0; i < length; ++i) {
            System.out.printf("%2d ", i + minDegree);
        }
        System.out.println();
    }
}