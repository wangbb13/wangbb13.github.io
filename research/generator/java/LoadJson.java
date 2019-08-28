/*
 * create time : 2019-07-09 15:45
 * author : wangbb13
 */
import org.json.simple.JSONObject;
import org.json.simple.JSONArray;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;
import java.util.Map;
import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;
import java.io.IOException;
import java.io.FileWriter;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;

public class LoadJson {
    private String jsonFilename;

    public LoadJson(String filename) {
        jsonFilename = filename;
    }

    public JSONObject load() {
        String jsonStr = readFile(jsonFilename);
        JSONParser parser = new JSONParser();
        JSONObject jsonObj = null;
        try {
            jsonObj = (JSONObject)parser.parse(jsonStr);
        } catch (ParseException pe) {
            pe.printStackTrace();
        }
        return jsonObj;
    }

    public void dump(String str) {
        writeFile(jsonFilename, str);
    }

    private void writeFile(String filename, String content) {
        try {
            FileWriter fw = new FileWriter(filename);
            BufferedWriter bw = new BufferedWriter(fw, 1024);
            bw.write(content);
            bw.newLine();
            bw.flush();
            bw.close();
            fw.close();
        } catch (IOException ioe) {
            ioe.printStackTrace();
        }
    }

    private String readFile(String filename) {
        String ans = "";
        String line;
        try {
            FileReader fr = new FileReader(filename);
            BufferedReader br = new BufferedReader(fr);
            while ((line = br.readLine()) != null) {
                ans = ans + line.trim();
            }
        } catch (IOException ioe) {
            ioe.printStackTrace();
        }
        return ans;
    }

    public static void main(String[] args) {
        JSONObject obj = new JSONObject();

        obj.put("name", "foo");
        obj.put("num", new Integer(100));
        obj.put("balance", new Double(100.21));
        obj.put("is_vip", new Boolean(true));
        List<Integer> idList = new ArrayList<Integer>(10);
        for (int i = 0; i < 10; ++i) {
            idList.add(i);
        }
        obj.put("id_list", idList);

        String jsonStr = obj.toString();
        // System.out.println(jsonStr);

        // init file writer and write json str. 
        String filename = "LoadJson.json";
        LoadJson lj = new LoadJson(filename);
        lj.dump(jsonStr);

        // decoding JSON
        JSONObject jsonObj = lj.load();
        String name = (String)jsonObj.get("name");
        System.out.printf("name = %s\n", name);
        long num = (Long)jsonObj.get("num");
        System.out.printf("num = %d\n", num);
        double balance = (Double)jsonObj.get("balance");
        System.out.printf("balance = %.2f\n", balance);
        boolean is_vip = (Boolean)jsonObj.get("is_vip");
        List<Integer> a_list = (ArrayList<Integer>)jsonObj.get("id_list");
        System.out.printf("lise size = %d\n", a_list.size());
    }
}
