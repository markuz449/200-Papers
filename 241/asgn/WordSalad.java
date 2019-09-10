/* File: WordSalad.java - April 2018 */
//package week09;

/**
 *  Skeleton implementation of the WordSalad class.
 *
 *  @author Michael Albert
 */
import java.util.*;

public class WordSalad implements Iterable<String> {
  
  private WordNode first;
  private WordNode last;
  
  public WordSalad() {
    this.first = null;
    this.last = null;
  }
  
  public WordSalad(java.util.List<String> words) {
    for (String word : words) {
      addLast(word);
    }
  }
  
  public void add(String word) {
    if (this.first == null) {
      this.first = new WordNode(word, null);
      this.last = this.first;
      return;
    }
    WordNode newFirst = new WordNode(word, this.first);
    this.first = newFirst;
  }
  
  public void addLast(String word) {
    if (this.first == null) {
      add(word);
      return;
    }
    WordNode newLast = new WordNode(word, null);
    this.last.next = newLast;
    this.last = newLast; 
  }
  
  //Inner Class
  private class WordNode {
    private String word;
    private WordNode next;
    
    private WordNode(String word, WordNode next) {
      this.word = word;
      this.next = next;
    }
    
  }
  // End Inner Class
  
  public java.util.Iterator<String> iterator() {
    return new java.util.Iterator<String>() {
      private WordNode current = first;
      
      public boolean hasNext() {
        return current != null;
      }
      
      public String next() {
        String result = current.word;
        current = current.next;
        return result;
      }
      
      public void remove() {
        throw new UnsupportedOperationException();
      }
    };
  }
  
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
  
  /** Fills array Salads[] with WordSalad objects.
    *  @param k
    *  @param salads.
    *  @return Filled WordSalad array.
    */
  private WordSalad[] fillArray(int k, WordSalad[] salads){
    for (int i = 0; i < k; i++){
      WordSalad newSalad = new WordSalad();
      salads[i] = newSalad;
    }
    return salads;
  }
  
  /** Gets a distributed Array.
    *  @param k.
    *  @return A distributed Array.
    */
  private WordSalad[] getDistribute(int k){
    return distribute(k);
  }
  
  /** Gets the total length of blocks of WordSalad
    * @param blocks of type WordSalad[]
    * @return the length of the total
    */
  private static int getLength(WordSalad[] blocks){
    int length = 0;
    for (int i = 0; i < blocks.length; i ++){
      WordSalad select = blocks[i];
      WordNode node = select.first;
      for (int j = 0; node != null; j ++){
        length ++;
        node = node.next;
      }
    }
    return length;
  } 
  
  /** Gets the total length of nodes of WordSalad
    * @return the length of the total
    */
  private int getInputLength(){
    int count = 0;
    for (WordNode node = first; node != null; node = node.next){
      count++;
    }
    return count;
  }
  
  private ArrayList<String> getItems(){
    ArrayList<String> items = new ArrayList<String>();
    for (WordNode node = first; node != null; node = node.next){
      items.add(node.word);
    }
    return items;
  }
  
  private ArrayList<String> newItemList(ArrayList<String> items, ArrayList<String> checkList){
    for (String check : checkList){
      items.remove(check);
    }
    return items;
  }
  
  private ArrayList<WordSalad> update (ArrayList<WordSalad> splitList, 
                                       ArrayList<String> items, int k, int totalLength, int count){
    if (items.size() > 0 && splitList.size() < totalLength){
      for (int i = 0; i < count; i++){
        WordSalad newSalad = new WordSalad(items);
        WordSalad[] getFirst = newSalad.distribute(k);
        splitList.add(getFirst[0]);
        ArrayList<String> checkList = new ArrayList<String>();
        WordSalad firstIndex = getFirst[0];
        for (WordNode node = firstIndex.first; node != null; node = node.next){
          checkList.add(node.word);
        }
        items = newItemList (items, checkList); 
      }
      count++;
      return update (splitList, items, k, totalLength, count);
    } else {
      return splitList;
    }
  }
  
  // Method stubs to be completed for the assignment.
  // See the assignment description for specification of their behaviour.
  
  /** Distributes the input into k blocks.
    *  
    *  @param k number o blocks decided by the user.
    *  @return An array or WordSalad type objects.
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
  
  public WordSalad[] split(int k) {
    ArrayList<String> items = getItems();
    ArrayList<WordSalad> splitList = new ArrayList<WordSalad>();
    int totalLength = getInputLength();
    int count = 1;
    splitList = update (splitList, items, k, totalLength, count);
    splitList.remove(splitList.size() - 1);
    
    System.out.println("arrayList size " + splitList.size());
    WordSalad[] splitSalad = new WordSalad[splitList.size()];
    splitSalad = splitList.toArray(splitSalad);
    System.out.println("array size " + splitSalad.length);
    
    return splitSalad;
  }
  
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
      for (int j = 0; j < nodeCount; j++){
        node = node.next;
      }
      mergeSalad.addLast(node.word);
      blockCount++;
    }
    return mergeSalad;
  }
  
  public static WordSalad join(WordSalad[] blocks) {
    return null;
  }
  
  public static WordSalad recombine(WordSalad[] blocks, int k) {
    return null;
  }
  
}
