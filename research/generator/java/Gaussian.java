/*
 * create time : 2019-03-26 20:50
 * author : wangbb13
 */

public class Gaussian extends Distribution {
    public Gaussian() {
        super();
    }

    public Gaussian(long mid, long mxd, long n, long m, Map<String, Double> params) {
        super(mid, mxd, n, m, params);
    }

    @Override
    public double pdf(long x) {
        double mu = params.get("mu");
        double sigma = params.get("sigma");
        double a = (x + 0.1 - mu) / sigma;
        double b = (x - 0.1 - mu) / sigma;
        return Utility.normCdf(a) - Utility.normCdf(b);
    }
}