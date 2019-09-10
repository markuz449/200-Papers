package week04;

import java.util.*;

/**
 * Skeleton code for an array based implementation of Young's tableau.
 *
 * @author Iain Hewson
 */
public class TableauApp {
  
    /**
     * The main method is just used for testing.
     *
     * @param args command line arguments are not used.
     */
    public static void main(String[] args) {
        final int[][] valid = {{1, 4, 5, 10, 11}, {2, 6, 8}, {3, 9, 12}, {7}};
        final int[][] invalid = {{1, 4, 5, 10, 11}, {2, 9, 8}, {3, 5, 2}, {7}};
        System.out.println(TableauApp.toString(valid));
        System.out.println(TableauApp.isTableau(valid));
    }
  
    /**
     * Determines whether the array passed to it is a valid tableau or not.
     *
     * @param t a two-dimensional array to test for tableau-ness.
     *
     * @return true if the parameter is a valid tableau, otherwise false
     */
    public static boolean isTableau(int[][] t){
        return rowLengthsDecrease(t)
            && rowValuesIncrease(t)
            && columnValuesIncrease(t)
            && isSetOf1toN(t);
    }
  
    /**
     * Determines if no row is longer than the preceding row.
     *
     * @param t a two-dimensional array.
     *
     * @return true if no row is longer than the preceding.
     */
    public static boolean rowLengthsDecrease(int[][] t){
        int prevLength = 0;
        int rowLength = 0;
        boolean check = false;
        for (int i = 0; i < t.length; i++){
            if (rowLength > t[i].length){
                check = true;
            }
            if (prevLength < rowLength){
                check = false;
            }
            prevLength = rowLength;
            rowLength = t[i].length;
        }
        return check;
    }
  
    /**
     * Determines if the row is increasing going from left to right.
     *
     * @param t a two-dimensional array.
     *
     * @return true if row is increasing.
     */
    public static boolean rowValuesIncrease(int[][] t){
        boolean check = true;
        for (int i = 0; i < t.length; i++){
            int previousVal = 0;
            int currentVal = 0;
            for (int j = 0; j < t[i].length; j++){
                previousVal = currentVal;
                currentVal = t[i][j];
                if (previousVal > currentVal){
                    check = false;
                } 
            }
        }
        return check;
    }
  
    /**
     * Determines if the column is increasing going from top to bottom.
     *
     * @param t a two-dimensional array.
     *
     * @return true if column is increasing.
     */
    public static boolean columnValuesIncrease(int[][] t){
        boolean check = true;
        for (int i  = 1; i < t.length; i++){
            for (int j = 0; j < t[i].length && j < t[i-1].length; j++){ 
                if (t[i][j] < t[i-1][j]){
                    check = false;
                } 
            }
        }
        return check;
    }

    /**
     * Determines if all the integers used is upto
     * and equal to the number of cells.
     *
     * @param t a two-dimensional array.
     *
     * @return true if all the integers used is upto
     *         and equal to the number of cell.
     */
    public static boolean isSetOf1toN(int[][] t){
        boolean check = true;
        ArrayList<Integer> arrayCheck = new ArrayList<Integer>();
        for (int i = 0; i < t.length; i++){
            for (int j = 0; j < t[i].length; j++){
                arrayCheck.add(t[i][j]);
            }
        }
        Collections.sort(arrayCheck);
        for (int i = 0; i < arrayCheck.size(); i++){
            if (arrayCheck.indexOf(i) > arrayCheck.indexOf(i + 1)){
                check = false;
            }  
        }
        return check;
    }
  
    /**
     *  Returns a string representation of an array based tableau.
     *
     * @param t a two-dimensional array which represents a tableau.
     *
     * @return a string representation of an array based tableau.
     */
    public static String toString(int[][] t) {
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < t.length; i++) {
            for (int j = 0; j < t[i].length; j++) {
                result.append(String.format("%-4s", t[i][j]));
            }
            if (i < t.length-1) {
                result.append("\n");
            }
        }
        return result.toString();
    }
  
}
