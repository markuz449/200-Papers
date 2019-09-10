package week11;

/** A insertion sort implementation which is able to be observed through its
 *  Sorter superclass.
 *
 *  @author Marcus Anderson.
 */
public class InsertionSort extends Sorter {

    /** Create a new InsertionSort sorter with the given integers to sort.
     * 
     *  @param nums the integers to sort.
     */
    public InsertionSort(Integer[] nums) {
        super(nums); // pass nums[] to the superclass Sort
    }

    /**
     * Sort the integers which are stored in the parent Sorter class
     * using the InsertionSort algorithm. 
     */
    public void sortNums() {
        comparisons = 0;
        for (i = 1; i < nums.length; i++) {
            for(j = i ; j > 0 ; j--){
                comparisons++;
                if(nums[j] < nums[j-1]){
                    
                    int temp = nums[j];
                    nums[j] = nums[j-1];
                    nums[j-1] = temp;
                }
                update();
            }
        }
    }
}

