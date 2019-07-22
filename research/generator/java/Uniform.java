/*
 * create time : 2019-07-09 17:03
 * author : wangbb13
 */
import java.util.Map;
import java.util.Random;

public class Uniform extends Distribution {
    private boolean ifSpecial;
    private long numNodes;
    private long numEdges;
    private long minDegree;
    private long maxDegree;
    private Random rand;
    private long frequency;
    private long curDegree;
    private long cumuDegree;
    private long cumuFrequency;
    private long curId;

    public Uniform(long mid, long mxd, long n, long m, Map<String, Double> params) {
        numNodes = n;
        numEdges = m;
        rand = new Random();
        // for target id
        long avgDegree = m / n;
        if (avgDegree <= mid) {
            mid = 1;
            mxd = 2 * avgDegree - mid;
        } else {
            mxd = 2 * avgDegree - mid;
        }
        minDegree = mid;
        maxDegree = mxd;
        if (mid == mxd) {
            ifSpecial = true;
        } else {
            ifSpecial = false;
        }
        frequency = n / (mxd - mid + 1);
        curDegree = mid;
        cumuDegree = 0;
        cumuFrequency = 0;
        curId = 0;
    }

    @Override
    public long genOutDegree(long id) {
        if (ifSpecial) {
            return minDegree;
        } else {
            int bound = Math.toIntExact(maxDegree - minDegree + 1);
            return minDegree + rand.nextInt(bound);
        }
    }

    @Override
    public long genTargetID() {
        long ans = curId;
        cumuDegree++;
        if (cumuDegree == curDegree) {
            cumuDegree = 0;
            cumuFrequency++;
            curId++;
            if (curId == numNodes) {
                curId = numNodes - 1;
            }
            if (cumuFrequency == frequency) {
                cumuFrequency = 0;
                curDegree++;
            }
        }
        return ans;
    }
}
