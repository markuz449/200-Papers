package week10;

/**
 *  A silly sort implementation which is able to be observed through its
 *  Sorter superclass.
 *
 * @author Iain Hewson
 */
public class SillySort extends Sorter {

    /**
     *  Create a new SillySort sorter with the given integers to sort.
     * 
     * @param nums the integers to sort.
     */
    public SillySort(Integer[] nums) {
        super(nums); // pass nums[] to the superclass Sort
    }

    /**
     * Sort the integers (which are stored in the parent Sorter class). 
     */
    public void sortNums() {
        // int i, j, comparisons, and nums[] are all protected datafields in
        // the superclass Sort so we can use them without declaring them
        comparisons = 0;
        int temp;
        for (i = 0; i < nums.length; i++) {
            for (j = 1; j < nums.length; j++) {
                if (++comparisons > 0 && nums[j] < nums[j-1]) {
                    temp = nums[j];
                    nums[j] = nums[j-1];
                    nums[j-1] = temp;
                }
                update();
            }
        }
    }
}
