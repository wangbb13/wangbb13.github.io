/*
 * create time : 2019-03-26 10:00
 * author : wangbb13
 */

public class Utility {
    public static double normPdf(double x) {
        return Math.exp(-x * x / 2) / Math.sqrt(2 * Math.PI);
    }

    public static double normCdf(double x) {
        if (x < -8.0) return 0.0;
        if (x >  8.0) return 1.0;
        double sum = 0.0, term = x;
        for (int i = 3; sum + term != sum; i += 2) {
            sum  = sum + term;
            term = term * x * x / i;
        }
        return 0.5 + sum * Utility.normPdf(x);
    }
}