import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;


interface Operation {
    abstract String undo(String s);
}
class OpAppend implements Operation {
    private int _size;
    OpAppend(int size) {
        _size = size;
    }
    @Override
    public String undo(String s) {
        return s.substring(0,s.length()-_size);
    }
}
class OpDelete implements Operation {
    private String _s;
    OpDelete(String s) {
        _s = s;
    }
    @Override
    public String undo(String s) {
        return s+_s;
    }
}
class Editor {
    private String s = new String();
    private Stack<Operation> stack = new Stack<>();

    public void append(String w) {
        stack.push(new OpAppend(w.length()));
        s += w;
    }
    public void delete(int k) {
        stack.push(new OpDelete(s.substring(s.length()-k)));
        s = s.substring(0,s.length()-k);
    }
    public void print(int k) {
        System.out.println(s.charAt(k-1));
    }
    public void undo() {
        s = stack.pop().undo(s);
    }
}

public class Solution {

    public static void main(String[] args) {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution. */
        Editor ed = new Editor();

        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        for (int i = 0; i < n; i++) {
            int op = scan.nextInt();

            switch (op) {
                case 1: {
                    String w = scan.nextLine();
                    ed.append(w.trim());
                    break;
                } case 2: {
                    int k = scan.nextInt();
                    ed.delete(k);
                    break;
                } case 3:
                    int k = scan.nextInt();
                    ed.print(k);
                    break;
                case 4: {
                    ed.undo();
                    break;
                }
            }
        }
    }
}