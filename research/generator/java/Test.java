import java.math.BigDecimal;
import java.util.Map;
import java.util.HashMap;
import java.util.Random;
import java.io.PrintWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Set;
import java.util.HashSet;
import java.util.ArrayList;

class One extends Thread {
    private static int count = 0;
    private Thread t;
    private long start;

    public One(long n) {
        start = n;
    }

    public void run() {
        for (int i = 0; i < 10; ++i) {
            synchronized (One.class) {
                count++;
                if (count == 100) {
                    long end = System.nanoTime();
                    long totalTime = end - start;
                    System.out.println("Total running time: ");
                    System.out.println(String.valueOf(totalTime) + " ns.");
                    double sec = totalTime * 1.0 / 1e9;
                    System.out.println(String.valueOf(sec) + " s.");
                }
            }
        }
    }

    public int get() {
        return count;
    }

    public void start() {
        if (t == null) {
            t = new Thread(this, "A");
            t.start();
        }
    }
}

class Demo {
    private int x;
    public Demo(int n) {
        n = x;
    }
    public void setX(int n) {
        x = n;
    }
    public int getX() {
        return x;
    }
}

public class Test {
    void testRound() {
        long num = 10;
        double a = 5.0;
        double b = 10.0;
        System.out.println(a / b);
        System.out.println(Math.round(a / b));
    }

    void showMap(Map<String, Double> map) {
        for (Map.Entry<String, Double> entry : map.entrySet()) {
            System.out.println(String.valueOf(entry.getKey()) + " : " + String.valueOf(entry.getValue()));
        }
    }

    void testMap() {
        Map<String, Double> map1 = new HashMap<String, Double>();
        map1.put("lambda", 1.15);
        map1.put("mu", 30.0);
        map1.put("sigma", 6.0);
        Map<String, Double> map2;
        map2 = new HashMap<String, Double>();
        for (Map.Entry<String, Double> entry : map1.entrySet()) {
            System.out.println(entry.getKey() + " : " + String.valueOf(entry.getValue()));
            map2.put(entry.getKey(), entry.getValue());
        }
        showMap(map2);
    }

    void misc() {
        int a, b;
        a = b = 10;
        System.out.println(String.valueOf(a) + String.valueOf(b));
        int [] list = new int[10];
        System.out.println(list.length);
        double da = 1.001;
        System.out.println((long)Math.ceil(da));
        da = 1.501;
        System.out.println((long)Math.ceil(da));
        a = ++b;
        System.out.println(String.valueOf(a) + " " + String.valueOf(b));
        a = b++;
        System.out.println(String.valueOf(a) + " " + String.valueOf(b));
        Random rand = new Random();
        System.out.println(rand.nextDouble());
    }

    void testIO() {
        try {
            FileWriter fw = new FileWriter("test.txt");
            PrintWriter pw = new PrintWriter(fw);
            pw.println(10);
            pw.println(100);
            pw.close();
            fw.close();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {

        }
    }

    void testIOPerformance() {
        long start = System.nanoTime();
        long size = 1 << 30;
        try {
            FileWriter fw = new FileWriter("test.txt");
            PrintWriter pw = new PrintWriter(fw);
            for (long i = 0; i < size; ++i) {
                pw.print(i);
            }
            pw.close();
            fw.close();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            // 
        }
        long end = System.nanoTime();
        System.out.print((end - start) * 1.0 / 1e9);
        System.out.println(" s.");
    }

    void testSet() {
        Set<Integer> set = new HashSet<Integer>();
        set.add(10);
        set.add(20);
        for (Integer i : set) 
            System.out.println(i);
    }

    void testIntLong() {
        long a = 10000;
        int b = (int)a;
        System.out.println(b);
    }

    void testArrayList() {
        long [][] list = new long[10][];
        System.out.println(list.length);
        for (int i = 0; i < 10; ++i) {
            list[i] = new long[i+1];
            System.out.println(list[i].length);
        }
    }

    void testMyUtil() {
        int n = 10000;
        int m = 10000;
        int k = 10;
        double lambda = 1.15;
        int[][] ans = Utility.splitCommunity(n, m, k, lambda);
        for (int i = 0; i < ans.length; ++i) {
            System.out.println(String.valueOf(ans[i][0]) + " " + String.valueOf(ans[i][1]));
        }
    }

    void testMT() {
        long start = System.nanoTime();
        int n = 10;
        One[] ts = new One[n];
        for (int i = 0; i < n; ++i) {
            ts[i] = new One(start);
            ts[i].start();
        }
        // for (int i = 0; i < n; ++i) {
        //     try {
        //         ts[i].join();
        //     } catch (InterruptedException e) {

        //     }
        // }
    }

    void testRV() {
        long start = System.nanoTime();
        Random rand = new Random();
        for (long i = 0; i < 1e12; ++i) {
            double a = rand.nextDouble();
            // double b = a * a;
        }
        long end = System.nanoTime();
        long total = end - start;
        System.out.println(total * 1.0 / 1e9);
    }

    void printArray(int[] array) {
        for (int i = 0; i < array.length; ++i) {
            System.out.print(array[i]);
            System.out.print(" ");
        }
        System.out.println("");
    }

    void printArray(long[] array) {
        for (int i = 0; i < array.length; ++i) {
            System.out.print(array[i]);
            System.out.print(" ");
        }
        System.out.println("");
    }

    void testPWL() {
        long minD = 1;
        long maxD = 50;
        long n = 1000;
        long m = 18000;
        Map<String, Double> theta = new HashMap<String, Double>();
        theta.put("lambda", 1.12);
        PowerLaw pwl = new PowerLaw(minD, maxD, n, m, theta);
        // pwl.preProcess(false);  // in-degree
        // pwl.printICdf();
        // System.out.println(pwl.getIMinGap());
        // pwl.preProcess(true);   // out-degree
        // long[] oDNum = pwl.getOdNum();
        // int[] split = pwl.splitSourceNodes(10);
        // printArray(oDNum);
        // printArray(split);
        pwl.preProcess(true);   // out-degree
        pwl.printOCdf();
    }

    public void testClass() {
        Demo d1 = new Demo(10);
        Demo d2 = d1;
        d2.setX(20);
        System.out.println(d1.getX());
        System.out.println(d2.getX());
    }

    public void testDelta() {
        int n1 = 10, m1 = 100, minD1 = 1, maxD1 = 20;
        int n2 = 20, m2 = 200, minD2 = 1, maxD2 = 30;
        Map<String, Double> theta = new HashMap<String, Double>();
        theta.put("lambda", 1.12);
        OutDegreeDistribution odd1 = new OutPowerLaw(minD1, maxD1, n1, m1, theta);
        OutDegreeDistribution odd2 = new OutPowerLaw(minD2, maxD2, n2, m2, theta);
        odd1.showDegreeNums();
        odd2.showDegreeNums();
        DeltaOutDistribution dod = new DeltaOutDistribution(null, odd2);
        dod.showDegreeNums();
    }

    public void testString() {
        String filename = "test.txt";
        String[] ans = filename.split("\\.");
        System.out.println(ans.length);
        for (String str : ans) {
            System.out.println(str);
        }
    }

    public static void main(String[] args) {
        Test t = new Test();
        // t.misc();
        // t.testIO();
        // t.testSet();
        // t.testIntLong();
        // t.testArrayList();
        // t.testMyUtil();
        // t.testMT();
        // t.testRV();
        // t.testIOPerformance();
        // t.testPWL();
        // t.testClass();
        // t.testDelta();
        t.testString();
    }
}