import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.regex.*;

class Result {

    /*
     * Complete the 'decryptMessage' function below.
     *
     * The function is expected to return a STRING.
     * The function accepts STRING encryptedMessage as parameter.
     */

    public static String decryptMessage(String encryptedMessage) {
        String res = "";

        try {
            String[] splitArray = encryptedMessage.split("\\s+");
            int ii = encryptedMessage.length()-1;

            for (int i = splitArray.length-1; i >=0; i--) {
                while(ii>=0 && encryptedMessage.charAt(ii--)!=' '){}
                ii++;
                for (int j = 0; j < splitArray[i].length(); j++) {
                    char c = splitArray[i].charAt(j);
                    char zero = '0';
                    int diff = c-zero;
                    if(diff <10) {
                        for (int k = 0; k < diff-1; k++) {
                            res = res.concat( Character.toString(splitArray[i].charAt(j-1)) );
                        }
                    } else {
                        res = res.concat( Character.toString(c));
                    }
                }
                while(ii>=0 && encryptedMessage.charAt(ii--)==' ') {
                    res = res.concat(" ");
                }
            }
        } catch (PatternSyntaxException ex) {
            res = encryptedMessage;
        }

        return res;
    }

}

public class Solution {
    public static void main(String[] args) throws IOException {
        Scanner scan = new Scanner(System.in);
        String encryptedMessage = scan.nextLine();
        String result = Result.decryptMessage(encryptedMessage);
        System.out.println(result);
    }
}

