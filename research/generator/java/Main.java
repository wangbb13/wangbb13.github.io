/*
 * create time : 2019-07-10 12:37
 * author : wangbb13
 */

public class Main {
    public static void main(String[] args) {
        String jsonFilename = args[0];
        Generation gen = new Generation(jsonFilename);
        gen.run();
    }
}