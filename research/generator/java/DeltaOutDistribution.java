/*
 * create time : 2019-04-07
 * author : wangbb13
 */
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.Random;

public class DeltaOutDistribution {
    private OutDegreeDistribution distr1;
    private OutDegreeDistribution distr2;

    private int minDegree;
    private int range;
    private int numNodes;
    private int[] eachDegreeNums;
    private int[] eachDegreeList;
    
    private double minGap;
    private int[] forOperating;

    private Random rand;
    private int bucket;
    private double bucketStep;

    public DeltaOutDistribution(OutDegreeDistribution odd1, OutDegreeDistribution odd2) {
        // odd2 - odd1, minDegrees are the same
        // odd1 may be null, but odd2 must be not null
        distr1 = odd1;
        distr2 = odd2;
        if (odd2 == null) {
            System.out.println("The second parameter for this constructor must be not null.");
            return;
        }
        minDegree = odd2.getMinDegree();
        numNodes = odd2.getNodes();
        rand = new Random();
        bucket = 2;
        bucketStep = 2 * 1.0 / numNodes;
        // preprocessing
        vernierCaliper();
        buildCDF();
    }

    public void setBucket(int b) {
        bucket = b;
        bucketStep = b * 1.0 / numNodes;
    }

    public void vernierCaliper() {
        if (distr1 == null) {
            range = distr2.getRange();
            int[] res = distr2.getEachDegreeNums();
            eachDegreeNums = new int[range];
            eachDegreeList = new int[range];
            for (int i = 0; i < range; ++i) {
                eachDegreeNums[i] = res[i];
                eachDegreeList[i] = i + minDegree;
            }
            return;
        }
        // critical part
        int odd1Range = distr1.getRange();
        int odd2Range = distr2.getRange();
        int odd1MaxDegree = odd1Range + minDegree - 1;
        int odd2MaxDegree = odd2Range + minDegree - 1;
        int[] odd1DegreeNums = distr1.getEachDegreeNums();
        int[] odd2DegreeNums = distr2.getEachDegreeNums();
        // split to achieve alignment
        int d1 = odd1MaxDegree, d2 = odd2MaxDegree;
        int i = odd1DegreeNums.length - 1, j = odd2DegreeNums.length - 1;
        List degreeList = new ArrayList<Integer>();  // inverse order
        List numberList = new ArrayList<Integer>();  // inverse order
        while (i >= 0 && j >= 0) {
            if (odd1DegreeNums[i] > odd2DegreeNums[j]) {
                degreeList.add(d2 - d1);
                numberList.add(odd2DegreeNums[j]);
                odd1DegreeNums[i] -= odd2DegreeNums[j];
                j--; d2--;
            } else if (odd1DegreeNums[i] == odd2DegreeNums[j]) {
                degreeList.add(d2 - d1);
                numberList.add(odd2DegreeNums[j]);
                i--; d1--;
                j--; d2--;
            } else {  // odd1DegreeNums[i] < odd2DegreeNums[j]
                degreeList.add(d2 - d1);
                numberList.add(odd1DegreeNums[i]);
                odd2DegreeNums[j] -= odd1DegreeNums[i];
                i--; d1--;
            }
        }
        while (j >= 0) {
            degreeList.add(d2);
            numberList.add(odd2DegreeNums[j]);
            j--; d2--;
        }
        // end alignment
        // merge switch
        int len = degreeList.size();
        for (i = j = 0; i < len; ) {
            int d = (int)degreeList.get(i);
            while (i < len && d == (int)degreeList.get(i)) {
                i++;
            }
            j++;
        }
        eachDegreeNums = new int[j];
        eachDegreeList = new int[j];
        int k = 0;
        for (i = 0; i < len; ) {
            int d = (int)degreeList.get(i);
            eachDegreeNums[k] = 0;
            eachDegreeList[k] = d;
            while (i < len && d == (int)degreeList.get(i)) {
                eachDegreeNums[k] += (int)numberList.get(i);
                i++;
            }
            k++;
        }
        // end merging
        // not merge switch
        // int len = degreeList.size();
        // eachDegreeNums = new int[len];
        // eachDegreeList = new int[len];
        // for (i = 0; i < len; ++i) {
        //     eachDegreeNums[i] = (int)numberList.get(i);
        //     eachDegreeList[i] = (int)degreeList.get(i);
        // }
        // end not merging
        // reverse
        i = 0; 
        j = eachDegreeNums.length - 1;
        while (i < j) {
            int temp = eachDegreeNums[i];
            eachDegreeNums[i] = eachDegreeNums[j];
            eachDegreeNums[j] = temp;
            temp = eachDegreeList[i];
            eachDegreeList[i] = eachDegreeList[j];
            eachDegreeList[j] = temp;
            i++; j--;
        }
        // end reversing
        range = eachDegreeNums.length;
    }

    public void buildCDF() {
        int sum = 0, cum = 0;
        for (int i = 0; i < range; ++i) {
            sum += eachDegreeNums[i];
        }
        double[] cdf = new double[range];
        double pre = 0.0;
        minGap = 1.0;
        for (int i = 0; i < range; ++i) {
            cum += eachDegreeNums[i];
            cdf[i] = 1.0 * cum / sum;
            minGap = Math.min(minGap, cdf[i] - pre);
            pre = cdf[i];
        }
        // start building
        int length = (int)Math.ceil(1.0 / minGap) + 1;
        forOperating = new int[length];
        pre = 0.0;
        int j = 0;
        for (int i = 0; i < range; ++i) {
            int steps = (int)((cdf[i] - pre) / minGap);
            for (int p = 0; p < steps; ++p) 
                forOperating[j++] = eachDegreeList[i];
            pre += steps * minGap;
            while (pre < cdf[i]) {
                forOperating[j++] = eachDegreeList[i];
                pre += minGap;
            }
        }
        while (j < length)
            forOperating[j++] = eachDegreeList[range - 1];
        // end building
    }

    public int hF(double x) {
        return Math.min((int)Math.round(x / minGap), forOperating.length - 1);
    }

    public int getOutDegree(int id) {
        double rv = ((id / bucket) + rand.nextDouble()) * bucketStep;
        int index = (int)Math.min(hF(rv), forOperating.length - 1);
        return forOperating[index];
    }

    public void showDegreeNums() {
        System.out.println("DeltaOutDistribution : ");
        int length = eachDegreeNums.length;
        for (int i = 0; i < length; ++i) {
            System.out.printf("%2d ", eachDegreeNums[i]);
        }
        System.out.println();
        for (int i = 0; i < length; ++i) {
            System.out.printf("%2d ", eachDegreeList[i]);
        }
        System.out.println();
    }
}