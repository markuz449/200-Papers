package week10;

import java.util.*;

/**
 * This class should be extended by classes that want to perform sorts
 * which can be observed while they are taking place.
 *
 * @author Iain Hewson
 */
public abstract class Sorter extends Observable {

    /** Represents the possible sorts that can be done. */
    public static enum Type {
        /** A pretty silly sorting algorithm. */
        SILLY,
        /** Selection sort. */
        SELECTION,
        /** Insertion sort. */
        INSERTION,
        // MERGE,
        // QUICK,
        // HEAP,
        // SHELL,
    };

    /** Represents all possible states that a Sorter can be in. */
    public static enum State {
        /** Sort is ready to start. */
        READY,
        /** Sort is running and can be paused. */
        RUNNING,
        /** Sort is paused and can be resumed. */
        PAUSED
    };

    /** Holds the numbers which are to be sorted. Individual elements can be
     *  accessed by index using the getValue() method.
     */
    protected Integer[] nums;

    /** Holds the number of comparisons used while sorting. */
    protected int comparisons = 0;
   
    /** Variable J can be used by subclasses, and has an accessor. */
    protected int j = 0;

    /** Variable I can be used by subclasses, and has an accessor. */
    protected int i = 0;

    /** The current state of this Sorter. */
    private State state = State.READY;

    /**
     * Create a new Sorter with the given array of integers to sort.
     *
     * @param nums the integers to sort.
     */
    public Sorter(Integer[] nums) {
        if (nums == null) {
            throw new IllegalArgumentException("Nums can't be null!");
        }
        this.nums = nums;
    }

    /**
     * This should be called by subclasses of Sorter, whenever they alter
     * the contents of nums, i, j, or comparisons.
     */
    public void update() {
        setChanged();
        notifyObservers(this);
        while (state == State.PAUSED) { // we can pause a sort here
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                System.err.println(e);
            }
        }
    }
   
    /** This method should be implemented by sub-classes to perform a sort. */
    public abstract void sortNums();

    /**
     * Change the state of this Sorter to newState.
     *
     * @param newState a new state for this Sorter.
     */
    public void setState(State newState) {
        state = newState;
    }

    /**
     * Return the current state of this Sorter.
     *
     * @return the current state of this Sorter.
     */
    public State getState() {
        return state;
    }

    /**
     * Accessor for individual elements of the number array.
     *
     * @param index the index of the array element to access.
     * @return the value at the given index of the number array, or -1 if the 
     *         index is out of range.
     */
    public int getValue(int index) {
        return (index  < 0 || index > nums.length-1) ? -1 : nums[index];
    }
   
    /**
     * Return how many numbers are in this Sorter.
     *
     * @return how many numbers are in this Sorter.
     */
    public int size() {
        return nums.length;
    }

    /**
     * Accessor for the number of comparisons performed while sorting.
     *
     * @return the number of comparisons performed while sorting.
     */
    public int getComparisons() {
        return comparisons;
    }

    /**
     * Accessor for the data field j.
     *
     * @return the value of j.
     */
    public int getJ() {
        return j;
    }
   
    /**
     * Accessor for the data field i.
     *
     * @return value of i.
     */
    public int getI() {
        return i;
    }
   
}
