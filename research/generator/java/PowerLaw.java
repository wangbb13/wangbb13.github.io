/*
 * create time : 2019-03-26 20:41
 * author : wangbb13
 */
import java.util.Map;

public class PowerLaw extends Distribution {
    public PowerLaw() {
        super();
    }

    public PowerLaw(long mid, long mxd, long n, long m, Map<String, Double> params) {
        super(mid, mxd, n, m, params);
    }

    @Override
    public double pdf(long x) {
        return Math.pow(x * 1.0, theta.get("lambda"));
    }
}