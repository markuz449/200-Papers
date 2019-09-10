package week01;

import java.util.Scanner;

/** Counter.java.
 *  COSC241 Lab 01
 *
 *  @author Marcus Anderson 
 */
public class Counter {

    // Data Fields
    /** int counter for number of lines. */
    private static int lines = 0;
    /** int counter for number of words. */
    private static int words = 0;
    /** Empty user String. */
    private static String userString = ""; 

    /** Main method which calls InputNums().
     *  Prints out the number of lines and words
     *
     *  @param args Main method parameters of an array of Strings
     */
    public static void main (String [] args){
        inputNums();
        System.out.println("lines: " + lines);
        System.out.println("words: " + words);
    }

    /** inputNums() uses scanners to count the number of lines and words.
     */
    public static void inputNums(){
        String line = null;
        Scanner userInput = new Scanner(System.in);
        
        while (userInput.hasNextLine()) { //Checks if there is a next line
            line = userInput.nextLine();
            Scanner checkLine = new Scanner(line);
            while (checkLine.hasNext()){ //Checks if there is words in line
                checkLine.next();
                words ++;
            }
            userString += line + "\n";
            checkLine.close();
        }
        if (line == null){
        } else {
            lines = getLineNumber(userString);
        }
        userInput.close();
    }

    /** getLineNumber counts the number of lines.
     *
     *  @param userLine the line that the scanner is on
     *  @return The amount of new lines that the userLine has
     */
    public static int getLineNumber(String userLine){
        if (words == 0){
            return userLine.split("[\n|\r]").length + 1;
        } else {
            return userLine.split("[\n|\r]").length;
        }
    }

}


