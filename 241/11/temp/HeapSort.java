package week11;

/** A heap sort implementation which is able to be observed through its
 *  Sorter superclass.
 *
 *  @author Marcus Anderson.
 */
public class HeapSort extends Sorter {

    /** Create a new HeapSort sorter with the given integers to sort.
     * 
     *  @param nums the integers to sort.
     */
    public HeapSort(Integer[] nums) {
        super(nums); // pass nums[] to the superclass Sort
    }

    /**
     * Sort the integers which are stored in the parent Sorter class
     * using the HeapSort algorithm. 
     */
    public void sortNums() {
        int numLength = nums.length;
        comparisons = 0;

        /** Turns array into a heap. */
        for (int counter = numLength / 2 - 1; counter >= 0; counter--){
            heapify(numLength, counter);
        }

        for (int h = numLength - 1; h>=0; h--) {
            swap (0, h);
 
            heapify(h, 0);
            comparisons++;
            update();
        }
        comparisons++;
        update();
    }

    /** Heapify method which takes in the root and the value
     *  and checks if the left or right is larger than the value.
     *
     *  Switches the values if let or right is larger and then swaps them
     *  and recursively call heapify again with the new value.
     *
     *  @param root of type int.
     *  @param k of type int which is the value we're moving.
     */
    private void heapify(int root, int k) {
        int largest = k; 
        int left = 2*k + 1;  
        int right = 2*k + 2;  
 
        if (left < root && nums[left] > nums[largest]){
            largest = left;
        }
        if (right < root && nums[right] > nums[largest]){
            largest = right;
        }
        if (largest != k) {
            swap (k, largest);
 
            heapify(root, largest);
        }
        comparisons++;
        update();
    }

    private void swap(int left, int right){
        i = left; j = right;
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }
}

