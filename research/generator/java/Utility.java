/*
 * create time : 2019-03-26 10:00
 * author : wangbb13
 */
import java.util.ArrayList;

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

    public static void showList(int[] list) {
        for (int i = 0; i < list.length; ++i) {
            System.out.printf("%d ", list[i]);
        }
        System.out.println();
    }

    /*
     * k: the number of comms
     * n: # nodes
     */
    public static int[] splitScalar(int n, int k, double lambda) {
        lambda = -Math.abs(lambda);
        int avgSize = n / k;
        int step = 0;
        int memory = 0;
        int lr = 0;
        int memCount = 0;
        ArrayList<Integer> alSize = new ArrayList<Integer>(1);
        ArrayList<Integer> alCount = new ArrayList<Integer>(1);
        while (true) {
            int currSize = 1 + lr * 2;
            int[] sizeList = new int[currSize];
            sizeList[lr] = avgSize;
            step = (int)Math.max(avgSize / (lr + k + 2), 1);
            for (int i = 1; i <= lr; ++i) {
                sizeList[lr + i] = sizeList[lr + i - 1] + step;
                sizeList[lr - i] = sizeList[lr - i + 1] - step;
            }
            double[] probability = new double[currSize];
            for (int i = 0; i < currSize; ++i) {
                probability[i] = Math.pow((double)sizeList[i], lambda);
            }
            double lastP = probability[currSize - 1];
            int[] count = new int[currSize];
            int spectrum = 0;
            for (int i = 0; i < currSize; ++i) {
                count[i] = (int)Math.round(probability[i] / lastP);
                spectrum += count[i] * sizeList[i];
            }
            if (spectrum > n) {
                break;
            } else {
                memory = spectrum;
                memCount = 0;
                for (int i = 0; i < currSize; ++i) {
                    memCount += count[i];
                    if (i >= alSize.size()) {
                        alSize.add(sizeList[i]);
                        alCount.add(count[i]);
                    } else {
                        alSize.set(i, sizeList[i]);
                        alCount.set(i, count[i]);
                    }
                }
            }
            lr += 1;
        }
        alSize.set(alSize.size() - 1, alSize.get(alSize.size() - 1) + n - memory);
        int[] res = new int[memCount];
        int j = 0;
        for (int i = alSize.size() - 1; i >= 0; --i) {
            for (int p = 0; p < alCount.get(i); ++p) 
                res[j++] = alSize.get(i);
        }
        int[] ans = new int[k];
        if (memCount < k) {
            // int fission = k / memCount + ((k % memCount == 0) ? 0 : 1);
            // int more = k - memCount;
            // int resI = memCount - 1, ansI = k - 1;
            // while (more > 0) {
            //     int cumuSize = 0;
            //     int perSize = res[resI] / fission;
            //     for (int i = 0; i < fission - 1; ++i) {
            //         ans[ansI] = perSize;
            //         ansI--;
            //         cumuSize += perSize;
            //     }
            //     ans[ansI] = res[resI] - cumuSize;
            //     ansI--;
            //     resI--;
            //     more -= (fission - 1);
            // }
            // while (ansI >= 0 && resI >= 0) {
            //     ans[ansI] = res[resI];
            //     ansI--;
            //     resI--;
            // }
            
            int fission = k / memCount + ((k % memCount == 0) ? 0 : 1);
            int more = k - memCount;
            int resI = 0, ansI = 0;
            while (more > 0) {
                int cumuSize = 0;
                int perSize = res[resI] / fission;
                for (int i = 0; i < fission - 1; ++i) {
                    ans[ansI] = perSize;
                    ansI++;
                    cumuSize += perSize;
                }
                ans[ansI] = res[resI] - cumuSize;
                ansI++;
                resI++;
                more -= (fission - 1);
            }
            while (ansI < k && resI < memCount) {
                ans[ansI] = res[resI];
                ansI++;
                resI++;
            }
        } else if (memCount > k) {
            // int fission = memCount / k + ((memCount % k == 0) ? 0 : 1);
            // int less = memCount - k;
            // int resI = 0, ansI = 0;
            // while (less > 0) {
            //     ans[ansI] = res[resI];
            //     resI++;
            //     for (int i = 0; i < fission - 1; ++i) {
            //         ans[ansI] += res[resI];
            //         resI++;
            //     }
            //     less -= (fission - 1);
            //     ansI++;
            // }
            // while (ansI < k && resI < memCount) {
            //     ans[ansI] = res[resI];
            //     ansI++;
            //     resI++;
            // }

            int fission = memCount / k + ((memCount % k == 0) ? 0 : 1);
            int less = memCount - k;
            int resI = memCount - 1, ansI = k - 1;
            while (less > 0) {
                ans[ansI] = res[resI];
                resI--;
                for (int i = 0; i < fission - 1; ++i) {
                    ans[ansI] += res[resI];
                    resI--;
                }
                less -= (fission - 1);
                ansI--;
            }
            while (ansI < k && resI < memCount) {
                ans[ansI] = res[resI];
                ansI--;
                resI--;
            }
        } else {
            for (int i = 0; i < k; ++i)
                ans[i] = res[i];
        }
        return ans;
    }

    public static int[] splitScalar(int n, int k, double lambda, int size) {
        // TODO : unnecessary
        int[] ans = new int[1];
        return ans;
    }

    public static int[][] splitCommunity(int row, int col, int k, double lambda) {
        int[] rowAns = splitScalar(row, k, lambda);
        int[][] ans = new int[rowAns.length][2];
        if (row == col) {
            for (int i = 0; i < rowAns.length; ++i) 
                ans[i][0] = ans[i][1] = rowAns[i];
        } else {
            // int[] colAns = splitScalar(col, k, lambda, rowAns.length);
            int cum = 0;
            for (int i = rowAns.length - 1; i > 0; --i) {
                ans[i][0] = rowAns[i];
                ans[i][1] = (int)Math.round(rowAns[i] * 1.0 * col / row);
                cum += ans[i][1];
            }
            ans[0][0] = rowAns[0];
            ans[0][1] = col - cum;
        }
        return ans;
    }
}
