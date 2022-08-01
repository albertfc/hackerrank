import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

    public static void main(String[] args) {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution. */
        Stack<String> stack = new Stack<>();
        String s = "";

        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        for (int i = 0; i < n; i++) {
            int op = scan.nextInt();

            switch (op) {
                case 1: {
                    stack.push(s);
                    String w = scan.next();
                    s += w;
                    break;
                } case 2: {
                    stack.push(s);
                    int k = scan.nextInt();
                    s = s.substring(0, s.length()-k);
                    break;
                } case 3:
                    int k = scan.nextInt();
                    System.out.println(s.charAt(k-1));
                    break;
                case 4: {
                    s = stack.pop();
                    break;
                }
            }
        }
    }
}