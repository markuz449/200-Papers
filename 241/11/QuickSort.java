package week11;

import java.util.*;
/** A quick sort implementation which is able to be observed through its
 *  Sorter superclass.
 *
 *  @author Marcus Anderson.
 */
public class QuickSort extends Sorter {

    /** Create a new QuickSort sorter with the given integers to sort.
     * 
     *  @param nums the integers to sort.
     */
    public QuickSort(Integer[] nums) {
        super(nums); // pass nums[] to the superclass Sort
    }

    /**
     * Sort the integers which are stored in the parent Sorter class
     * using the QuickSort algorithm. 
     */
    public void sortNums() {
        comparisons = 0;
        int i = 0;
        int j = nums.length - 1;
        quickSort(i, j);
    }

    /** Creates the pivot for quick sort
     *  and then recursivly split the data agin until there is nothing. 
     *
     *  @param lo of type int which is is the lowest value of the array.
     *  @param hi of type int which is is the largest value of the array.
     */
    public void quickSort(int left, int right) {
        if (left < right){
            int p = partition(left, right);
            quickSort(left, p);
            quickSort(p+1, right);
        }
    }

    /** Chooses the pivot point for quick sort
     *  and then puts all the larger or equal values on the right of the pivot
     *  and then puts all the smaller values on the left of the pivot.
     *
     *  @param lo of type int which is is the lowest value of the array.
     *  @param hi of type int which is is the largest value of the array.
     *
     *  @return the pivot point.
     */
    private int partition(int left, int right) {
        int pivot = nums[left];
        int hole = left;
        i = left+1;
        j = right;
        while (true){
            while (j > hole && nums[j] >= pivot) {
                j--;
                comparisons++;
                update();
            }
            if (j == hole) {
                break;
            }
            nums[hole] = nums[j];
            hole = j;
            
            while (i < hole && nums[i] < pivot) {
                i++;
                comparisons++;
                update();
            }
            if (i == hole) {
                break;
            }
            nums[hole] = nums[i];
            hole = i;
        }
        nums[hole] = pivot;
        return hole;
    }
}

