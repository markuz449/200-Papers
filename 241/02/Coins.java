package week02;

import java.util.*;

public class Coins{
  
  public static final boolean HEADS = true;
  public static final boolean TAILS = false;
  
  private boolean[] coins;
  
  public Coins(boolean[] coins) {
    this.coins = coins;
  }
  
  public Coins(String c){
    this.coins = new boolean[c.length()];
    for (int i = 0; i < c.length(); i ++){
      char charC = c.charAt(i);
      if (charC == 'H'){
        coins[i] = HEADS;
      } else if (charC == 'T'){
        coins[i] = TAILS;
      }
    }
  }
  
  public Coins(int length){
    this.coins = new boolean[length];
    Random rand = new Random();
    for (int i = 0; i < length; i ++){
      coins[i] = rand.nextBoolean();
    }
  }
  
  public int countHeads() {
    int headNum = 0;
    for (int i = 0; i < coins.length; i ++){
      if (coins[i] == true){
        headNum ++;
      }
    }
    return headNum;
  }
  
  public String toString() {
    String tosses = "";
    for (int i = 0; i < coins.length; i ++){
      if (coins[i] == HEADS){
        tosses = tosses + "H";
      }
      else if (coins[i] == TAILS){
        tosses = tosses + "T";
      }
    }
    return tosses;
  }
  
  public int countRuns(){
    char firstChar;
    char previousChar = ' ';
    int runs = 0;
    String tossResults = toString();
    
    for (int i = 0; i < tossResults.length(); i ++){
      firstChar = tossResults.charAt(i);
      if (firstChar != previousChar){
        runs++;
      }
      previousChar = firstChar;
    }
    return runs;
  }
  
}
