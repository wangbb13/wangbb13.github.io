/*
 * create time : 2019-03-26 22:18
 * author : wangbb13
 */
import java.util.Map;

public class LogNormal extends Distribution {
    public LogNormal() {
        super();
    }

    public LogNormal(long mid, long mxd, long n, long m, Map<String, Double> params) {
        super(mid, mxd, n, m, params);
    }

    @Override
    public double pdf(long x) {
        double mu = theta.get("mu");
        double sigma = theta.get("sigma");
        double a = (Math.log(x + 0.1) - mu) / sigma;
        double b = (Math.log(x - 0.1) - mu) / sigma;
        return Utility.normCdf(a) - Utility.normCdf(b);
    }
}