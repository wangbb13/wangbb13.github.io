import java.math.BigDecimal;
import java.util.Map;
import java.util.HashMap;
import java.util.Random;
import java.io.PrintWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Set;
import java.util.HashSet;

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

    public static void main(String[] args) {
        Test t = new Test();
        // t.misc();
        // t.testIO();
        t.testSet();
    }
}