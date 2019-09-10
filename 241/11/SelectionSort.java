package week11;

/** A selection sort implementation which is able to be observed through its
 *  Sorter superclass.
 *
 *  @author Marcus Anderson.
 */
public class SelectionSort extends Sorter {

    /** Create a new SelectionSort sorter with the given integers to sort.
     * 
     *  @param nums the integers to sort.
     */
    public SelectionSort(Integer[] nums) {
        super(nums); // pass nums[] to the superclass Sort
    }

    /**
     * Sort the integers which are stored in the parent Sorter class
     * using the SelectionSort algorithm. 
     */
    public void sortNums() {
        comparisons = 0;
        for (i = 0; i < nums.length - 1; i++){
          int index = i;
          for (j = i + 1; j < nums.length; j++){
            comparisons++;
            if (nums[j] < nums[index]){
              index = j;
            }
            update();
          }
          int temp = nums[i];
          nums[i] = nums[index];
          nums[index] = temp;
        }
    }
               
}

