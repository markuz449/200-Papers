package week02;

public class Test{
  
  public static void main(String[] args) {
    boolean[] b = {true, false, true, true, false};
    Coins c = new Coins(b);
    System.out.println(c.countHeads());
    Coins d = new Coins(c.toString());
    System.out.println(d.countHeads());
    Coins e = new Coins(12);
    System.out.println(e.countHeads());
    System.out.println(e.toString());
    System.out.println(e.countRuns());
  }
}
