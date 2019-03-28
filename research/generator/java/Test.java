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

    public static void main(String[] args) {
        Test t = new Test();
        // t.misc();
        // t.testIO();
        // t.testSet();
        // t.testIntLong();
        // t.testArrayList();
        // t.testMyUtil();
        // t.testMT();
        t.testRV();
    }
}