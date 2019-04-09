/*
 * create time : 2019-03-26 09:06
 * author : wangbb13
 */
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.Random;
import java.math.BigDecimal;

public class Distribution {
    private long minDegree;
    private long maxDegree;
    private long degreeRange;
    private long numNodes;
    private long numEdges;
    protected Map<String, Double> theta;  // parameters of distribution

    // arrays and variables for getting out-degree simply
    private long odSimpleCurrNo;    // node ID
    private long odSimpleCurrId;    // array index
    private long odSimpleOffset;    // offset in [Id]
    private long odSimpleMemNo;     // memory
    private int odSimpleMemId;     // memory
    private long odSimpleMemoff;    // memory
    private long [] odSimpleCNum;   // number of nodes whose degree is i + minDegree
    // arrays and variables for getting out-degree intricately
    private long [] odComplexDegree;    // get a degree directly
    private double oMinGap;
    private int bucket;         // generate out-degree randomly
    private double bucketStep;  // [0, 1]

    // arrays and variables for getting target vertex ID
    private long [] idHashTID;      // corresponding target vertex ID
    private double [] idHashCDF;    // cumulative distribution function for sum of degrees
    private double [] idHashRatio;  // corresponding ratio, for getting a ID in [idHashTID[i], idHashTID[i+1]]
    private double iMinGap;
    private double iMinRV;

    // random number generator
    private Random rand;

    public Distribution() {
        minDegree = 0;
        maxDegree = 0;
        numNodes = 0;
        numEdges = 0;
        degreeRange = 0;
        theta = new HashMap<String, Double>();
        rand = new Random();
        bucket = 1;
        bucketStep = 1 * 1.0 / numNodes;
        odSimpleCurrNo = odSimpleCurrId = odSimpleOffset = 0;
    }

    public Distribution(long mid, long mxd, long n, long m, Map<String, Double> params) {
        minDegree = mid;
        maxDegree = mxd;
        numNodes = n;
        numEdges = m;
        degreeRange = maxDegree - minDegree + 1;
        theta = new HashMap<String, Double>();
        // For PowerLaw
        if (params.containsKey("lambda")) {
            double l = -Math.abs(params.get("lambda"));
            params.put("lambda", l);
            // System.out.print("Constructor: ");
            // System.out.println(params.get("lambda"));
        }
        // End
        for (Map.Entry<String, Double> entry : params.entrySet()) {
            theta.put(entry.getKey(), entry.getValue());
        }
        rand = new Random();
        bucket = 1;
        bucketStep = 1 * 1.0 / numNodes;
        odSimpleCurrNo = odSimpleCurrId = odSimpleOffset = 0;
    }

    public void preProcess(boolean out) {
        mathEdges();
        if (out) {
            buildForOdSimply();
            buildForOdIntricately();
        } else {
            buildForIdHashTables();
        }
    }

    public void setStartSourceNo(long no) {
        if (no < numNodes) {
            odSimpleMemNo = no++;
            odSimpleMemId = 0;
            long cum = 0;
            while (odSimpleMemId < odSimpleCNum.length && cum < no) 
                cum += odSimpleCNum[++odSimpleMemId];
            odSimpleCurrNo = odSimpleMemNo;
            odSimpleCurrId = odSimpleMemId;
            odSimpleOffset = odSimpleMemoff = cum - no;
        }
    }

    public void setOutBucket(int x) {
        bucket = x;
        bucketStep = x * 1.0 / numNodes;
    }

    public double pdf(long x) {
        return 0.0;
    }

    public long numberOfMinDegree() {
        double minPDF = pdf(minDegree);
        double sumPDF = minPDF;
        for (long i = minDegree + 1; i <= maxDegree; ++i) {
            sumPDF += pdf(i);
        }
        return Math.round(numNodes * (minPDF / sumPDF));
    }

    public long numberOfMaxDegree() {
        double maxPDF = pdf(maxDegree);
        double sumPDF = maxPDF;
        for (long i = minDegree; i < maxDegree; ++i) {
            sumPDF += pdf(i);
        }
        return Math.round(numNodes * (maxPDF / sumPDF));
    }

    public long currentEdges() {
        degreeRange = maxDegree - minDegree + 1;
        double sum = 0.0;
        double[] p = new double[(int)degreeRange];
        for (int i = (int)minDegree; i <= maxDegree; ++i) {
            p[i - (int)minDegree] = pdf(i);
            sum += p[i - (int)minDegree];
        }
        double alpha = numNodes / sum;
        long ans = 0;
        for (int i = 0; i < degreeRange; ++i) {
            ans += Math.round(alpha * p[i] * (i + minDegree));
        }
        // System.out.println("Edges = " + String.valueOf(ans));
        return ans;
    }

    public void mathEdges() {
        System.out.println("======================Adjust====================");
        // adjust maxDegree so that the number of nodes 
        // whose degree is maxDegree is equal to or more than 1
        maxDegree = Math.min(maxDegree, numNodes);
        long binL = maxDegree + 1;
        long binR = maxDegree;
        while (binR > 0 && numberOfMaxDegree() < 1) {
            binR = maxDegree;
            maxDegree /= 2;
            binL = maxDegree;
        }
        while (binL < binR) {
            maxDegree = (binL + binR) / 2;
            long num = numberOfMaxDegree();
            if (num < 1) 
                binR = maxDegree;
            else
                binL = maxDegree + 1;
        }
        maxDegree = binL - 1;
        // end adjust maxDegree
        long actualEdges = currentEdges();
        System.out.println("max degree = " + String.valueOf(maxDegree) + " actual edges = " + String.valueOf(actualEdges) + " expected edges = " + String.valueOf(numEdges));
        // match the expected number of edges
        if (actualEdges < numEdges) {
            long temp = maxDegree;
            binL = binR = maxDegree + 1;
            while (maxDegree < numNodes && numberOfMaxDegree() > 0) {
                binL = maxDegree;
                maxDegree *= 2;
                binR = maxDegree;
            }
            binR = Math.min(binR, numNodes);
            while (binL < binR) {
                // System.out.println("If : " + String.valueOf(binL) + " " + String.valueOf(binR));
                maxDegree = (binL + binR) / 2;
                if (numberOfMaxDegree() < 1)
                    binR = maxDegree;
                else
                    binL = maxDegree + 1;
            }
            maxDegree = binL - 1;
            actualEdges = currentEdges();
            // System.out.println("If : " + String.valueOf(maxDegree) + " , " + String.valueOf(actualEdges));
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
        System.out.println("adjusted maxDegree = " + String.valueOf(maxDegree));
        System.out.println("actual edges = " + String.valueOf(actualEdges) + " expected edges = " + String.valueOf(numEdges));
        // end match the expected number of edges
        // update degreeRange
        degreeRange = maxDegree - minDegree + 1;
        // end update
        System.out.println("===================End====================");
    }

    public void buildForOdSimply() {
        int size = (int)degreeRange;
        double [] temp = new double[size];
        double sum = 0.0;
        int iminDegree = (int)minDegree;
        int imaxDegree = (int)maxDegree;
        for (int i = iminDegree; i <= imaxDegree; ++i) {
            temp[i - iminDegree] = pdf(i);
            sum += temp[i - iminDegree];
        }
        double alpha = numNodes / sum;
        odSimpleCNum = new long[size];
        for (int i = 0; i < size; ++i) {
            odSimpleCNum[i] = Math.round(alpha * temp[i]);
        }
    }

    public void buildForOdIntricately() {
        // get CDF of out-degree distribution
        int size = (int)degreeRange;
        double [] temp = new double[size];
        double sum = 0.0;
        double minGap = 1.0;
        double pre = 0.0;
        int iminDegree = (int)minDegree;
        int imaxDegree = (int)maxDegree;
        for (int i = iminDegree; i <= imaxDegree; ++i) {
            sum += pdf(i);
            temp[i - iminDegree] = sum;
        }
        double alpha = 1.0 / sum;
        for (int i = 0; i < size; ++i) {
            temp[i] *= alpha;
            minGap = Math.min(minGap, temp[i] - pre);
            pre = temp[i];
        }
        // end CDF
        int length = (int)Math.ceil(1.0 / minGap) + 1;
        odComplexDegree = new long[length];
        pre = 0.0;
        int j = 0;
        long d = minDegree;
        // build
        for (int i = 0; i < degreeRange; ++i) {
            int steps = (int)((temp[i] - pre) / minGap);
            for (int p = 0; p < steps; ++p) 
                odComplexDegree[j++] = d;
            pre += steps * minGap;
            while (pre < temp[i]) {
                odComplexDegree[j++] = d;
                pre += minGap;
            }
            d = i + minDegree;
        }
        while (j < length)
            odComplexDegree[j++] = d;
        // end build
        oMinGap = minGap;
    }

    public void buildForIdHashTables() {
        // start temp
        int size = (int)degreeRange;
        double [] temp = new double[size];
        double cum = 0.0;
        int iminDegree = (int)minDegree;
        int imaxDegree = (int)maxDegree;
        for (int i = iminDegree; i <= imaxDegree; ++i) {
            cum += pdf(i);
            temp[i - iminDegree] = cum;
            // if (i - iminDegree == 37) {
            //     System.out.println(temp[i - iminDegree]);
            // }
        }
        double alpha = numNodes / cum;
        // System.out.println("numNodes = " + String.valueOf(numNodes));
        // System.out.println("cum = " + String.valueOf(cum));
        for (int i = 0; i < degreeRange; ++i) {
            // if (i == 37) {
            //     System.out.println(temp[i]);
            // }
            temp[i] *= alpha;
            // if (i == 37) {
            //     System.out.println(temp[i]);
            //     System.out.println(alpha);
            // }
        }
        // end temp
        // build CDF and maximum ID first
        double [] iCdf = new double[size + 1];
        long [] iIndex = new long[size + 1];
        iCdf[0] = 0.0;
        iIndex[0] = -1;
        for (int i = 1; i <= degreeRange; ++i) {
            long num = (long)Math.round(temp[i - 1]);
            // iIndex[i] = iIndex[i - 1] + num;
            // iCdf[i] = iCdf[i - 1] + num * (i - 1 + minDegree);
            iIndex[i] = num;
            iCdf[i] = num * (i - 1 + minDegree);
            // if (i == 38) {
            //     System.out.println(num);
            // }
        }
        // System.out.println("iCdf[1] = " + String.valueOf(temp[0]));
        // iCdf[0] = minDegree / iCdf[size];
        iMinRV = minDegree / iCdf[size];
        iCdf[0] = 0.0;
        iIndex[0] = 0;
        iIndex[size] = numNodes - 1;
        // end build CDF and ID list
        iMinGap = 1.0;
        // int memI = -1;
        for (int i = 1; i <= degreeRange; ++i) {
            iCdf[i] /= iCdf[size];
            // if (iCdf[i] - iCdf[i - 1] < iMinGap) {
            //     iMinGap = iCdf[i] - iCdf[i - 1];
            //     memI = i;
            // }
            iMinGap = Math.min(iMinGap, iCdf[i] - iCdf[i - 1]);
        }
        // build hash tables
        // for (int i = 0; i <= degreeRange; ++i) {
        //     System.out.print(String.valueOf(iCdf[i]) + " ");
        // }
        // System.out.println(memI);
        // System.out.println(iCdf[memI]);
        // System.out.println(iCdf[memI - 1]);
        // System.out.println("iMinGap = " + String.valueOf(iMinGap));
        // iMinGap = Math.max(iMinGap, 4.761904761904762e-10);
        int length = (int)Math.ceil(1.0 / iMinGap) + 1;
        // System.out.println("length = " + String.valueOf(length));
        idHashTID = new long[length];
        idHashCDF = new double[length];
        idHashRatio = new double[length];
        long iTIDNext;
        double iCDFNext;
        long preV = 0;
        int preI = 0;
        for (int j = 1; j <= degreeRange; ++j) {
            int i = (int)iHF(iCdf[j]);
            iTIDNext = iIndex[j];
            iCDFNext = iCdf[j];
            for (int k = preI; k < i; ++k) {
                idHashTID[k] = preV;
                idHashCDF[k] = iCdf[j - 1];
                if ((iCDFNext - idHashCDF[k]) < 1e-8)
                    idHashRatio[k] = 0.0;
                else
                    idHashRatio[k] = (iTIDNext - idHashTID[k]) / (iCDFNext - idHashCDF[k]);
            }
            preV = iIndex[j];
            preI = i;
        }
        iTIDNext = numNodes - 1;
        iCDFNext = 1.0;
        for (int k = preI; k < length; k++) {
            idHashTID[k] = preV;
            idHashCDF[k] = iCdf[size];
            if ((iCDFNext - idHashCDF[k]) < 1e-8)
                idHashRatio[k] = 0.0;
            else
                idHashRatio[k] = (iTIDNext - idHashTID[k]) / (iCDFNext - idHashCDF[k]);
        }
        // end build 
        // iMinRV = minDegree / iCdf[size];
    }

    public long oHF(double x) {
        return Math.min(Math.round(x / oMinGap), odComplexDegree.length - 1);
    }

    public long iHF(double x) {
        return Math.min(Math.round(x / iMinGap), idHashTID.length - 1);
    }

    public long genOutDegreeSimple(long id) {
        if (id == odSimpleMemNo) {
            odSimpleCurrNo = odSimpleMemNo;
            odSimpleCurrId = odSimpleMemId;
            odSimpleOffset = odSimpleMemoff;
            return odSimpleCurrId + minDegree;
        } else if (id == (int)odSimpleCurrNo + 1) {
            odSimpleCurrNo = id;
            if (odSimpleCurrId < odSimpleCNum.length) {
                if (odSimpleOffset < odSimpleCNum[(int)odSimpleCurrId]) {
                    odSimpleOffset += 1;
                } else {
                    odSimpleOffset = 1;
                    odSimpleCurrId += 1;
                }
                return odSimpleCurrId + minDegree;
            } else {
                return odSimpleCurrId + minDegree - 1;
            }
        } else {
            long no = odSimpleMemNo + odSimpleCNum[odSimpleMemId] - odSimpleMemoff;
            int index = odSimpleMemId;
            while (index < odSimpleCNum.length && no < id) {
                no += odSimpleCNum[++index];
            }
            return index + minDegree - 1;
        }
    }

    public long genOutDegreeComplex(long id) {
        // System.out.println((id / bucket) * bucketStep);
        double rv = (id / bucket) * bucketStep + rand.nextDouble() * bucketStep;
        int index = (int)Math.min(oHF(rv), odComplexDegree.length - 1);
        // System.out.println(String.valueOf(rv) + " " + String.valueOf(odComplexDegree[index]));
        // System.out.println(odComplexDegree[index]);
        return odComplexDegree[index];
    }

    public long genOutDegree(long id) {
        return genOutDegreeComplex(id);
    }

    public long genTargetID() {
        double rv = Math.max(rand.nextDouble(), iMinRV);
        int index = (int)iHF(rv);
        // System.out.println(String.valueOf(rv) + " " + String.valueOf(index));
        long a;
        double c, r;
        if (rv >= idHashCDF[index]) {
            a = idHashTID[index];
            c = idHashCDF[index];
            r = idHashRatio[index];
        } else {
            a = idHashTID[index - 1];
            c = idHashCDF[index - 1];
            r = idHashRatio[index - 1];
        }
        return a + Math.round((rv - c) * r);
    }

    public double getOMinGap() {
        return oMinGap;
    }

    public double getIMinGap() {
        return iMinGap;
    }

    public void printICdf() {
        for (int i = 0; i < idHashCDF.length; ++i) {
            System.out.println(idHashCDF[i]);
        }
    }

    public void printOCdf() {
        int size = odSimpleCNum.length;
        double[] cdf = new double[size];
        cdf[0] = odSimpleCNum[0];
        for (int i = 1; i < size; ++i) {
            cdf[i] = cdf[i - 1] + odSimpleCNum[i];
        }
        for (int i = 0; i < size; ++i) {
            cdf[i] /= cdf[size - 1];
        }
        double ans = 1.0;
        for (int i = 0; i < size; ++i) {
            System.out.println(cdf[i]);
            if (i > 0) {
                ans = Math.min(ans, cdf[i] - cdf[i - 1]);
            }
        }
        System.out.println("min out gap = " + String.valueOf(ans));
    }

    public int[] splitSourceNodes(int nThreads) {
        int[] ans = new int[nThreads + 1];
        ans[0] = 0;
        long step = (long)(numEdges / nThreads);
        long vc = step;
        int j = 0;
        int d = (int)minDegree;
        long sum = 0;
        int acc = 0;
        for (int i = 1; i < nThreads; ++i) {
            while (j < odSimpleCNum.length && sum < vc) {
                sum += d * odSimpleCNum[j];
                acc += (int)odSimpleCNum[j];
                d++;
                j++;
            }
            vc += step;
            ans[i] = acc;
        }
        ans[nThreads] = (int)numNodes;
        return ans;
    }

    public long[] getOdNum() {
        return odSimpleCNum;
    }
}