package week11;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import static week11.Sorter.State.*;

/**
 * Provides a way of running different sorting algorithms which extend
 * the Sort class and optionally display a graphical representation of
 * the sort as it is performed.
 *
 * @author Iain Hewson
 */
public class SortApp {

    /** Index of the current sort. */
    private static int sortNum = 0;
    /** Holds the type of the current sort. */
    private static Sorter.Type sortType = Sorter.Type.values()[0];
    /** Maximum width for the GUI. */
    private static final int MAX_WIDTH = 600;
    /** Maximum height for the GUI. */
    private static final int MAX_HEIGHT = 300;
    /** How many numbers to display and sort. */
    private static int guiWidth = MAX_WIDTH;
    /** The biggest number to display and sort. */
    private static int guiHeight = MAX_HEIGHT;
    /** Holds the sorter used to perform the sorting algorithm. */
    private static Sorter sorter;
    /** Holds the numbers to be sorted. */
    private static Integer[] nums;
    /** Holds a backup copy of the numbers to be sorted. */
    private static Integer[] original;
    /** Whether a GUI will be shown. */
    private static boolean gui = false;
    
    /**
     * Creates and displays a SortGUI.  By default an insertion sort is shown.
     * This can be changed to shell sort by passing '-s' on the command line.
     *
     * @param args '-s' as the first command line argument will display a shell
     *             sort instead of an insertion sort.
     */
    public static void main(String[] args) {
        String commandLine = String.join(" ", args);
        Scanner input = new Scanner(commandLine);
        while (input.hasNext()) {
            if (input.hasNextInt()) {
                int n = input.nextInt();
                if (n >= 0 && n < Sorter.Type.values().length) {
                    sortNum = n;
                    sortType = Sorter.Type.values()[sortNum];
                }
            } else {
                String token = input.next();
                switch (token) {
                    case "-g":
                        gui = true;
                        break;
                    case "-h": default:
                        printHelp();
                        System.exit(0);
                }
            }
        }
        original = readNums(new Scanner(System.in));
        if (gui) {
            JFrame f = new JFrame("Sorting");
            f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            f.getContentPane().add(new SortGUI(guiWidth, guiHeight));
            f.setResizable(false);
            f.pack();
            f.setVisible(true);
        } else {
            createSorter();
            sorter.sortNums();
            for (Integer num : sorter.nums) {
                System.out.println(num);
            }
            System.err.println(sorter.comparisons);
        }
    }

    /**
     *  Print help message to stderr.
     */
    private static void printHelp() {
        System.err.println("java week10.SortApp [options] <ints from stdin>");
        System.err.println("Valid options:");
        System.err.println("-h    - print this message");
        System.err.println("-g    - display the gui");
        System.err.println(" N    - use sort N where valid values are:");
        Sorter.Type[] sorts = Sorter.Type.values();
        for (int i = 0; i < sorts.length; i++) {
            System.err.printf("        %d = %s\n", i, sorts[i].name());
        }
    }
    
    /**
     *  Read integers from the given input source into an array.
     * 
     * @param input the source to read numbers from.
     * @return the numbers read in.
     */
    public static Integer[] readNums(Scanner input) {
        ArrayList<Integer> numbers = new ArrayList<>();
        guiWidth = 0;
        guiHeight = 0;
        while (input.hasNextInt()) {
            int val = input.nextInt();
            if (gui) {
                if (guiWidth++ > MAX_WIDTH) {
                    break;
                }
                if (val < 0) {
                    val *= -1;
                }
                val = val % MAX_HEIGHT;
                if (val > guiHeight) {
                    guiHeight = val;
                }
            }
            numbers.add(val);
        }
        return numbers.toArray(new Integer[0]);
    }

    /**
     *  Instantiates a subclass of Sort based on the data field sortType to
     *  perform a sort with.
     */
    private static void createSorter() {
        if (nums == null) {
            nums = original;
        }
        switch (sortType) {
            case SILLY:
                sorter = new SillySort(nums);
                break;
            case SELECTION:
                sorter = new SelectionSort(nums);
                break;
            case INSERTION:
                sorter = new InsertionSort(nums);
                break;
            case MERGE:
                sorter = new MergeSort(nums);
                break;
            case QUICK:
                sorter = new QuickSort(nums);
                break;
            case HEAP:
                sorter = new HeapSort(nums);
                break;
            // case SHELL:
            //     sorter = new ShellSort(nums);
            //     break;
        }
    }

    /**
     *  Class used to display a graphical view of a sort being performed.
     */
    private static class SortGUI extends JPanel implements Observer {
        
        /** Needed because JPanel is serializable. */
        private static final long serialVersionUID = 1L;
        /** Shows how many comparisons have been done so far. */
        private JLabel comparisons = new JLabel("Comparisons: 0");
        /** Flag to say whether to have short pauses during sorting. */
        private boolean slower = true;
        /** Start/pause/resume button for controlling the sort. */
        private JButton startButton = new JButton("Start");
        
        /**
         * Create a new SortGUI with the given dimensions and type.
         *
         * @param width how many numbers to sort (and display).
         * @param height maximum value for the numbers to sort.
         */
        public SortGUI(int width, int height) {
            setLayout(new BorderLayout());
            JPanel topPanel = new JPanel();
            topPanel.add(comparisons);
            add(topPanel, BorderLayout.NORTH);
            DrawingPanel drawingPanel = new DrawingPanel();
            drawingPanel.setPreferredSize(new Dimension(width, height));
            JPanel centrePane = new JPanel();
            centrePane.add(drawingPanel);
            add(centrePane, BorderLayout.CENTER);
            JPanel bottomPanel = new JPanel();
            add(makeControlPanel(), BorderLayout.SOUTH);
            reset();
        }

        /**
         * Create a control panel with a start/pause/resume button, a reset
         * button, and two speed buttons (faster and slower).
         *
         * @return the control panel.
         */
        private JComponent makeControlPanel() {
            JPanel pane = new JPanel();
            final Dimension buttonSize = new Dimension(95,29);
            startButton.setPreferredSize(buttonSize);
            pane.add(makeSortSelector());
            pane.add(startButton);
            JButton resetButton = new JButton("Reset");
            resetButton.setPreferredSize(buttonSize);
            resetButton.addActionListener((ActionEvent e) -> {
                    reset();
                });
            pane.add(resetButton);
            startButton.addActionListener((ActionEvent e) -> {
                    switch (sorter.getState()) {
                        case READY:    
                            Runnable r = () -> {
                                sorter.sortNums();
                            };
                            new Thread(r).start();
                            sorter.setState(RUNNING);
                            startButton.setText("Pause");
                            break;
                        case RUNNING:
                            sorter.setState(PAUSED);
                            startButton.setText("Resume");
                            break;
                        default:
                            sorter.setState(RUNNING);
                            startButton.setText("Pause");
                            break;
                    }
                });
            pane.add(makeSpeedSelectors());
            return pane;
        }

        /**
         * (Re)initialise things so that we are ready to perform a sort.
         */
        private void reset() {
            if (sorter != null) {
                sorter.setState(RUNNING);  // don't leave old sorter paused
                sorter.deleteObserver(this);
            }
            nums = original.clone();
            createSorter();
            startButton.setText("Start");
            sorter.addObserver(this);
            update(null,null);
        }

        /**
         *  Creates a JComboBox to select which sort to perform using
         *  the values in the enum Sort.Type.  Values are mapped from
         *  SORTNAME to "Sortname sort".
         * @return the sort selector combo box.
         */
        private JComboBox<String> makeSortSelector() {
            // Make a list of sort names from Sort.Type enum values
            // for example SELECTION becomes "Selection sort"
            ArrayList<String> names = new ArrayList<>();
            Sorter.Type[] types = Sorter.Type.values();
            for (Sorter.Type t : types) {
                char[] name = t.name().toLowerCase().toCharArray();
                name[0] = Character.toUpperCase(name[0]);
                names.add(new String(name) + " sort");
            }
            JComboBox<String> sorts = 
                new JComboBox<>(names.toArray(new String[0]));
            sorts.addActionListener((ActionEvent e) -> {
                    @SuppressWarnings("unchecked")
                        JComboBox<String> c = (JComboBox<String>) e.getSource();
                    String choice = (String) c.getSelectedItem();
                    int index = c.getSelectedIndex();
                    sortType = types[index];
                    reset();
                });
            sorts.setSelectedIndex(sortNum);
            return sorts;
        }

        /**
         * Create a panel containing two selectors (slower and faster) to
         * control the speed of the sort.
         *
         * @return a panel containing the speed selectors.
         */
        private JComponent makeSpeedSelectors() {
            JPanel pane = new JPanel();
            ButtonGroup group = new ButtonGroup();
            pane.add(makeSpeedButton("Slower", group, true));
            pane.add(makeSpeedButton("Faster", group, false));
            return pane;
        }

        /**
         * Create a radio button with the given name, belonging to the given
         * group, which sets the value of the data field slower to the value of
         * isSlow when pressed.
         *
         * @param name the name of the button.
         * @param group the button group to add the button to.
         * @param isSlow the value to set data field slower to when pressed.
         * @return the created radio button.
         */
        private JRadioButton makeSpeedButton(String name, ButtonGroup group,
                                             final boolean isSlow) {
            JRadioButton button = new JRadioButton(name);
            group.add(button);
            button.setSelected(isSlow);
            button.addActionListener((ActionEvent e) -> {
                    slower = isSlow;
                });
            return button;
        }
      
        @Override
        public void update(Observable obs, Object obj) {
            comparisons.setText("Comparisons: " + sorter.getComparisons());
            if (slower) {
                try {
                    Thread.sleep(1);
                } catch (InterruptedException e) {
                    System.err.println(e);
                }
            }
            repaint();
        }
   
        /**
         * This panel is used to show a graphical representation of the numbers
         * which are being sorted.
         */
        private class DrawingPanel extends JPanel {
      
            /** Needs one of these since JPanel is serializable. */
            public static final long serialVersionUID = 2;
      
            /**
             * This method gets called when the panel needs to be repainted.
             * Black vertical lines drawn on it to represent numbers which are
             * being sorted. Two coloured lines are also drawn to show each
             * comparison, so we can see where we are up to.
             * 
             * @param g the Graphics context in which to paint.
             */
            public void paintComponent(Graphics g) {
                super.paintComponent(g);
                // draw a line for each value in the sorter's array of integers
                for (int i = 0; i < sorter.size(); i++) {
                    g.drawLine(i, getHeight(), i,
                               getHeight() - sorter.getValue(i));
                }
                int i = sorter.getI(), j = sorter.getJ();
                // draw coloured lines to show each comparison
                if (i >= 0 && j >= 0 && i < sorter.size() &&
                    j < sorter.size()) {
                    g.setColor(Color.RED);
                    g.drawLine(i, 0, i, getHeight());
                    g.setColor(Color.GREEN);
                    g.drawLine(j, 0, j, getHeight());
                }
            }
        }
    }
}
