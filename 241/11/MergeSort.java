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
        int left = 0;
        int right = nums.length - 1;
        mergeSort(left, right);
    }

    private void mergeSort (int left, int right){
        if (left < right){
            int mid = (left + right) / 2;
            mergeSort(left, mid);
            mergeSort(mid + 1, right);
            merge(left, mid + 1, right);
            update();
        }
        update();
    }
    private void merge (int left, int mid, int right){
        Integer[] temp = new Integer[nums.length];
        for (int h = 0; h < nums.length; h++){
            temp[h] = nums[h];
        }
        i = left;
        j = left;
        int k = mid;

        while (i < mid && k <= right){
            comparisons++;
            if (temp[i] < temp[k]){
                nums[j++] = temp[i++];
            } else {
                nums[j++] = temp[k++];
            }
            update();
        }
        while (i < mid){
            comparisons++;
            nums[j++] = temp[i++];
            update();
        }
        while (j <= right){
            comparisons++;
            nums[j++] = temp[k++];
            update();
        }
        update();
    }
}

