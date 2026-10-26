package topcodersrm;

/**
 * SRM 211 DIV 1 500 points problem: grafixMask
 *
 * @author Minh
 */
import java.util.Stack;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;

class Node {

    int x, y;

    Node(int a, int b) {
        x = a;
        y = b;
    }
}

public class grafixMask {

    public static int doFill(boolean[][] fill, int x, int y) {
        int result = 0;

        Stack s = new Stack();
        s.push(new Node(x, y));

        while (s.empty() == false) {
            Node top = (Node) s.peek();
            s.pop();

            if (top.x < 0 || top.x >= 400) {
                continue;
            }
            if (top.y < 0 || top.y >= 600) {
                continue;
            }

            if (fill[top.x][top.y]) {
                continue;
            }

            fill[top.x][top.y] = true;
            result++;

            s.push(new Node(top.x + 1, top.y));
            s.push(new Node(top.x - 1, top.y));
            s.push(new Node(top.x, top.y + 1));
            s.push(new Node(top.x, top.y - 1));
        }
        return result;
    }

    public int[] sortedAreas(String[] rectangles) {
        boolean[][] fill = new boolean[400][600];

        for (String rec : rectangles) {
            String[] coor = rec.split(" ");
            for (int i = Integer.parseInt(coor[0]); i <= Integer.parseInt(coor[2]); i++) {
                for (int j = Integer.parseInt(coor[1]); j <= Integer.parseInt(coor[3]); j++) 
                    fill[i][j] = true;
            }
        }

        ArrayList<Integer> result = new ArrayList<>();

        for (int x = 0; x < 400; x++) {
            for (int y = 0; y < 600; y++) {
                if (!fill[x][y]) 
                    result.add(doFill(fill, x, y));
            }
        }
        Collections.sort(result);
        return convertIntegers(result);

    }

    public static int[] convertIntegers(List<Integer> integers) {
        int[] ret = new int[integers.size()];
        Iterator<Integer> iterator = integers.iterator();
        for (int i = 0; i < ret.length; i++) {
            ret[i] = iterator.next();
        }

        return ret;
    }

    public static void main(String[] args) {
        grafixMask g = new grafixMask();
        g.start();
    }

    public void start() {
        // Insert test cases.
        String[] rectangles = {"48 192 351 207", "48 392 351 407", "120 52 135 547", "260 52 275 547"};
        printArray(sortedAreas(rectangles));
    }

    /**
     * For debug purpose.
     * @param array
     */
    private static void printArray(int[] array) {
        for (int i = 0; i < array.length; i++) {
            System.out.println(array[i] + " ");
        }
    }
}
