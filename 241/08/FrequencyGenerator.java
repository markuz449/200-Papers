package week08;

import java.io.*;
import java.util.*;

/**
 *  Random Word Generator which depends on certain frequencies of characters.
 *
 * @author Marcus Anderson
 */
public class FrequencyGenerator implements WordGenerator {

    /** Random source used to generate words. */
    private Random random;
    /** An Array which will store frequency values. */
    private double[] alphabetFrequency;    

    /** Constructor which loads the file and sets the random datafield.
     *
     *  @param r of type Random, used to get random values.
     */
    public FrequencyGenerator(Random r) {
        random = r;
        loadFile();
    }

    /** Returns a String of random charachters depending on a given probability.
     *
     *  @param n the amount of characters is wanted.
     *  @return String of random characters.
     */
    public String nextWord(int n) {
        final int alphabetLength = 26;
        StringBuilder returnString = new StringBuilder();
        for(int i = 0; i < n; i++) {
            char c = (char) ('a' +  getRandom(alphabetFrequency));
            returnString.append(c);
        }
        return returnString.toString();
    }

    /** Gets a random value from the alphabetFrequency.
     *
     *  @param alphabet an array of type double filled with frequencies.
     *  @return a random int value.
     */
    public int getRandom(double[] alphabet){
        int i = 0;
        double r = random.nextDouble();
        while (r > alphabet[i]){
            r = r - alphabet[i];
            i = i + 1;
        }
        return i;
    }

    /** Loads the values of the specified file into an array.
     */
    public void loadFile() {
        Scanner frequencies;
        File file = new File ("letter-frequencies.txt");
        int count = 0;
        try {
            /** Reads and counts the number of lines in the file
                to initalise the array to the correct length.
            */
            BufferedReader reader = new BufferedReader(new FileReader(file));
            int lines = 0;
            while (reader.readLine() != null){
                lines++;
            }
            reader.close();
            
            alphabetFrequency = new double[lines];
            frequencies = new Scanner (file);
            while (frequencies.hasNextDouble()) {
                alphabetFrequency[count] = frequencies.nextDouble();
                count ++;
            }
        } catch (Exception error) {
            System.err.println(error.getMessage());
        }
    }

}
