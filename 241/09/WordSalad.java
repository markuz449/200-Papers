/* File: WordSalad.java - April 2018 */
package week09;

import java.util.*;
/**
 *  Complete implementation of WordSalad class.
 *
 *  @author Michael Albert
 *  @author Marcus Anderson
 *  @author Tim Kern
 *  @author Logan Bartosh
 *
 */
public class WordSalad implements Iterable<String> {
  
    /** WordNode data field which indicates the first node in a WordSalad. */
    private WordNode first;
    /** WordNode data field which indicates the last node in a WordSalad. */
    private WordNode last;
  
    /** Base constructor which sets the data fields to null. */
    public WordSalad() {
        this.first = null;
        this.last = null;
    }
  
    /** Constructor which fills the WordSalad with a list parameter.
     * 
     * @param words a list of type String.
     */
    public WordSalad(java.util.List<String> words) {
        for (String word : words) {
            addLast(word);
        }
    }
  
    /** Adds a node in the first position with the value of the parameter String.
     * 
     * @param word of type String.
     */
    public void add(String word) {
        if (this.first == null) {
            this.first = new WordNode(word, null);
            this.last = this.first;
            return;
        }
        WordNode newFirst = new WordNode(word, this.first);
        this.first = newFirst;
    }
  
    /** Adds a node in the last position with the value of the parameter String.
     * 
     * @param word of type String.
     */
    public void addLast(String word) {
        if (this.first == null) {
            add(word);
            return;
        }
        WordNode newLast = new WordNode(word, null);
        this.last.next = newLast;
        this.last = newLast; 
    }
  
    /** Inner class WordNode creates a node which holds a String value. */
    private class WordNode {
        private String word;
        private WordNode next;
    
        /** Constructor which creates the new node.
         * 
         * @param word of type String which is the value.
         * @param next of type WordNode which sets the next node.
         */
        private WordNode(String word, WordNode next) {
            this.word = word;
            this.next = next;
        }
    }
  
    public java.util.Iterator<String> iterator() {
        return new java.util.Iterator<String>() {
            private WordNode current = first;
      
            /** Checks if there is a next node.
             * 
             * @return true if there is, and false if there isn't a next node.
             */
            public boolean hasNext() {
                return current != null;
            }
      
            /** Moves the current node to the next node.
             * 
             * @return String value of the current node.
             */
            public String next() {
                String result = current.word;
                current = current.next;
                return result;
            }
      
            /** Throws an Exception if remove is called.
             */
            public void remove() {
                throw new UnsupportedOperationException();
            }
        };
    }
  
    /** Returns a String of WordNode values which resembles an array of WordSalad.
     * 
     * @return String of the WordNode values.
     */
    public String toString() {
        StringBuilder result = new StringBuilder("[");
        WordNode node = first;
        while (node != null) {
            result.append(node.word);
            result.append(node.next == null ? "" : ", ");
            node = node.next;
        }
        return result.toString() + "]";
    }
  
    /** Returns a String of the WordNode values which is used for the Join method.
     * 
     * @return String of the WordNode values.
     */
    public String toJoinedString() {
        StringBuilder result = new StringBuilder("");
        WordNode node = first;
        while (node != null) {
            result.append(node.word);
            result.append(node.next == null ? "" : ", ");
            node = node.next;
        }
        return result.toString() + "";
    }
  
    /** Fills array salads[] with WordSalad objects.
     * 
     *  @param k the length of the array.
     *  @param salads array which gets filled.
     *  @return Filled WordSalad array.
     */
    private static WordSalad[] fillArray(int k, WordSalad[] salads){
        for (int i = 0; i < k; i++){
            WordSalad newSalad = new WordSalad();
            salads[i] = newSalad;
        }
        return salads;
    }
  
    /** Returns the total amount of words in a WordSalad[].
     * 
     * @param blocks of type WordSalad[].
     * @return the total length.
     */
    private static int getLength(WordSalad[] blocks){
        int length = 0;
        for (int i = 0; i < blocks.length; i ++){
            WordSalad select = blocks[i];
            WordNode node = select.first;
            while (node != null){
                length ++;
                node = node.next;
            }
        }
        return length;
    }
  
    /** Returns an int for the count of words in a WordSalad.
     * 
     * @param blocks of type WordSalad.
     * @return The count of words.
     */
    private static int getBlockLength(WordSalad blocks){
        int length = 0;
        for (WordNode node = blocks.first; node != null; node = node.next){
            length++;
        }
        return length;
    }
  
    /** Determines the amount of blocks needed for the split method.
     * 
     * @param k which is the Split value.
     * @param l which is the amount of words in the current WordSalad.
     * @return The amount of blocks needed for the Split method.
     */
    private int splitLength(int k, int l){
        if(l==0){
            return 0;
        } else if(l%k==0){
            return 1 + splitLength(k, l-l/k);
        } else{
            return 1 + splitLength(k, l-((l/k)+1)); 
        }
    }
  
    /** Counts and returns the amount of words in the original input WordSalad. 
     * 
     * @return amount of words in the input WordSalad.
     */
    private int getInputLength(){
        int count = 0;
        for (WordNode node = first; node != null; node = node.next){
            count++;
        }
        return count;
    }
  
    /** Fills an ArrayList with the words of the current WordSalad.
     * 
     * @return ArrayList of type String filled with WordNode values.
     */
    private ArrayList<String> getItems(){
        ArrayList<String> items = new ArrayList<String>();
        for (WordNode node = first; node != null; node = node.next){
            items.add(node.word);
        }
        return items;
    }
  
    /** Fills a new ArrayList with all words that weren't used in split.
     * 
     * @param items which is the old list of WordNode values remaining.
     * @param salad which contains the WordNode values to be removed from items.
     * @return ArrayList of type String filled with WordNode values.
     */
    private ArrayList<String> newItemList(ArrayList<String> items, WordSalad salad){
        for (WordNode node = salad.first; node != null; node = node.next){
            String check = node.word;
            if (items.contains(check)){
                items.remove(check);
            }
        }
        return items;
    }
  
   
  
    /** Distributes the input into k blocks.
     *  Adds a word to each block then starts again until words left.
     * 
     *  
     *  @param k number of blocks decided by the user.
     *  @return An array of WordSalads.
     */
    public WordSalad[] distribute(int k) {
        WordSalad[] salads = new WordSalad[k];
        WordNode node = first;
    
        // Distributes the input into WordSalads.
        salads = fillArray(k, salads);
        while (node != null){
            for (int i = 0; i < k && node != null; i++){
                salads[i].addLast(node.word); //Fills the array.
                node = node.next;
            }
        }
        return salads;
    }
  
    /** Divides the input into k blocks of mostly equal size.
     *  
     *  @param k number of blocks decided by the user.
     *  @return An array of type WordSalad.
     */
    public WordSalad[] chop(int k) {
        WordSalad[] salads = new WordSalad[k];
        WordNode node = first;
        salads= fillArray(k, salads);
    
        while (node != null){
            int length = getInputLength();
            boolean check = true;
            for (int j = 0; j < k && node != null; j++){ 
                int i =0;
                int div = length / k;
                if (length % k != 0 && check == true){
                    div = div + 1;
                    length--;
                } else if (check == true){
                    check = false;
                    length--;
                } else {
                    check = false;
                    div++;
                }
                while(i < div && node != null){
                    salads[j].addLast(node.word); 
                    node = node.next;
                    i++;
                } 
            } 
        }
        return salads;
    }
  
    /** Splits input into progressively smaller blocks based on distribute.
     * 1.Distributes the input with a value of k.
     * 2.Adds the block at position 0 to the result splitSalad.
     * 3.Removes the values in the first block.
     * Repeats steps 1-3 until no words are left. 
     *  
     *  @param k the parameter to be used when distributing.
     *  @return An array or WordSalad objects.
     */
    public WordSalad[] split(int k) {
        int l = getInputLength();
        WordSalad[] splitSalad = new WordSalad[splitLength(k, l)];
        ArrayList<String> items = getItems();
        int count = 0;
        while (items.isEmpty() == false){
            WordSalad salad = new WordSalad(items);
            WordSalad[] select = salad.distribute(k);
            splitSalad[count] = select[0];
            items = newItemList(items, select[0]);
            count++;
        }  
        return splitSalad;
    }
  
    /**Undoes distribute method. 
     *
     * Adds contents of  WordSalad[] to a WordSalad, inverse
     * order to distribute.
     * 
     * @param blocks an array of WordSalad, distributed for desired effect.
     * @return A single WordSalad which contains all words.
     */
    public static WordSalad merge(WordSalad[] blocks) {
        int length = getLength(blocks); //Local Variables
        WordSalad mergeSalad = new WordSalad();
        int nodeCount = 0;
        int blockCount = 0;
        //Adds the words to mergeSalad
        for (int i = 0; i < length; i ++){
            if (blockCount >= blocks.length){
                blockCount = 0; //Resets the block which is being selected
                nodeCount ++;
            }
            WordSalad select = blocks[blockCount];
            WordNode node = select.first;
            for (int j = 0; j < nodeCount && node.next != null; j++){
                node = node.next;
            }
            mergeSalad.addLast(node.word);
            blockCount++;
        }
        return mergeSalad;
    }
  
    /** Undoes the chop method.
     *
     * Adds words in a WordSalad[] to a WordSalad in the order they come in.
     * 
     * @param blocks an array of WordSalad, chopped for desired effect.
     * @return A single WordSalad which contains all of the words.
     */
    public static WordSalad join(WordSalad[] blocks) {
        WordSalad newD = new WordSalad();
        for(int i=(blocks.length)-1; i>=0;i--){
            newD.add(blocks[i].toJoinedString());
        }
        return newD;
    }
  
    /**Undoes the split method.
     *
     * Iterates through an array of WordSalad and adds the required
     * item to indexes of an array list items.
     * Indexes are 0 or multiples of k. Depending block length.
     *
     * @param blocks an array of WordSalad, split for desired effect.
     * @param k parameter that was used to split. 
     * @return A single WordSalad which contains all of the words.
     */
    public static WordSalad recombine(WordSalad[] blocks, int k) {
        ArrayList<String> items = new ArrayList<String>();
        int blockLength = blocks.length - 1;
        for (int i = blockLength; i >= 0; i--){
            WordSalad firstSalad = blocks[i];
            int count = 0;
            for (WordNode node = firstSalad.first; node != null; node = node.next){
                items.add(count, node.word);
                count = count + k;
            }
        }
        WordSalad recombined = new WordSalad(items);
        return recombined;
    }
}
