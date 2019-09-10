package week11;

import java.util.*;

/** A merge sort implementation which is able to be observed through its
 *  Sorter superclass.
 *
 *  @author Marcus Anderson.
 */
public class MergeSort extends Sorter {

    /** Create a new MergeSort sorter with the given integers to sort.
     * 
     *  @param nums the integers to sort.
     */
    public MergeSort(Integer[] nums) {
        super(nums); // pass nums[] to the superclass Sort
    }

    /**
     * Sort the integers which are stored in the parent Sorter class
     * using the MergeSort algorithm. 
     */
    public void sortNums() {
        comparisons = 0;
        i = 0;
        j = nums.length;
        sort(i, j);
    }

    /** Splits the data in half recursively
     *  and then merges it all back together.
     *
     *  @param left of type int which is the left most position.
     *  @param right of type int which is the right most position.
     */
    public void sort(int left, int right) {
        if (right - left <= 1){
            return;
        }
        int mid = (left + right)/2;
        sort(left, mid);
        sort(mid, right);
        merge(left, mid, right);
    }

    /** Merges the split data back together.
     *
     *  @param left of type int which is the left most position.
     *  @param right of type int which is the right most position.
     *  @param mid which is the middle position of left and right.
     */
    public  void merge(int left, int mid, int right) {
        Integer[] temp = new Integer[right - left];
        int leftPos = left; int rightPos = mid; int i = 0;
        while (leftPos < mid && rightPos < right) {
            if (nums[leftPos] < nums[rightPos]) {
                temp[i++] = nums[leftPos++];
                update();
                comparisons ++;
            } else {
                temp[i++] = nums[rightPos++];
                update();
                comparisons ++;
            }
        }
        while (leftPos < mid) {
            temp[i++] = nums[leftPos++];
            update();
            comparisons ++;
        }
        while (rightPos < right) {
            temp[i++] = nums[rightPos++];
            update();
            comparisons ++;
        }
        System.arraycopy(temp, 0, nums, left, right-left);
    }
}

