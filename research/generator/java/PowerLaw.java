/*
 * create time : 2019-03-26 20:41
 * author : wangbb13
 */

public class PowerLaw extends Distribution {
    public PowerLaw() {
        super();
    }

    public PowerLaw(long mid, long mxd, long n, long m, Map<String, Double> params) {
        super(mid, mxd, n, m, params);
    }

    @Override
    public double pdf(long x) {
        return Math.pow(params.get("lambda"), x * 1.0);
    }
}