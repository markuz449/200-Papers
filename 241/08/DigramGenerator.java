package week08;

import java.util.*;
import java.io.*;

/**
 *  Random Word Generator which depends on the two files that are loaded.
 *
 * @author Marcus Anderson
 */
public class DigramGenerator implements WordGenerator {

    /** Random source used to generate words. */
    private Random random;
    /** Array of Strings that are loaded from a file. */
    private String[] alphabetString;
    /** Final int which is the length of the alphabet. */
    private final int alphabetLength = 26;
    /** Declares a scanner called scan. */
    private Scanner scan;

    /** Constructor which loads the file and sets the random datafield.
     *
     *  @param r of type Random, used to get random values.
     */
    public DigramGenerator(Random r) {
        random = r;
        loadFile();
    }

    /** Returns a String of random charachters which are
        randomy chosen from two files.
     *
     *  @param n the amount of characters is wanted.
     *  @return String of random characters.
     */
    public String nextWord(int n) {
        StringBuilder returnString = new StringBuilder();
        char firstLetter = getRandomChar();
        returnString.append(firstLetter);
        for (int i = 1; i < n; i++){
            int indexSelect = firstLetter - 'a';
            String secondString = alphabetString[indexSelect];
            int secondChar = random.nextInt(secondString.length());
            firstLetter = secondString.charAt(secondChar);
            returnString.append(firstLetter);
        }
        return returnString.toString();
    }

    /** Loads the values of the specified file into an array.
     */
    public void loadFile() {
        File file = new File ("continuations.txt");
        int count = 0;
        try {
            alphabetString = new String[alphabetLength];
            scan = new Scanner (file);
            while (scan.hasNextLine()) {
                alphabetString[count] = scan.nextLine();
                count ++;
            }
        } catch (Exception error) {
            System.err.println(error.getMessage());
        }
    }

    /** Returns a random character from a file loaded.
     *
     *  @return A random char from a file.
     */
    public char getRandomChar() {
        File file = new File ("first-letters.txt");
        String letters = "";
        int index = 0;
        try {
            scan = new Scanner (file);
            while (scan.hasNextLine()){
                letters += scan.nextLine();
            }
            index = random.nextInt(letters.length());
        } catch (Exception error) {
            System.err.println(error.getMessage());
        }
        return letters.charAt(index);
    }
}
