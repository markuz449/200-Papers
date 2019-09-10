 

/** RecursiveApp.java.
 *  COSC241 Lab 03.
 *
 *  @author Marcus Anderson 
 */
public class RecursiveApp {

    /** Static method Digits counts how many digits in a positive integer.
     *
     *  @param n of type long.
     *  @return returns n and recursively runs the method.
     */
    public static long digits (long n){
        if (n < 10){
            return 1;
        }
        return 1 + digits(n / 10);
    }

    /** Static method sumOfDigits computes the sum of it's input.
     *
     *  @param n of type long.
     *  @return returns the sum of type long.
     */
    public static long sumOfDigits(long n){
        int sum = 0;
        String number = Long.toString(n);
        
        for (int i = 0; i < number.length(); i++){
            char charDigit = number.charAt(i);
            int sumDigit = Character.getNumericValue(charDigit);
            sum += sumDigit;
            
        }
        if (n < 0){
            return ((sum + 1) * -1);
        } else {
            return sum;
        }
    }

}
