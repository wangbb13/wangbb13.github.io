/*
 * create time : 2019-04-08 14:28
 * author : wangbb13
 */
import java.util.Map;

public class OutPowerLaw extends OutDegreeDistribution {
    public OutPowerLaw(int mid, int mxd, int n, int m, Map<String, Double> params) {
        super(mid, mxd, n, m, params);
    }

    @Override
    public double pdf(int x) {
        return Math.pow(x * 1.0, theta.get("lambda"));
    }
}