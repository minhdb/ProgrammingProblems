/**
 * HRT Task 3
 *
 * A retail store chain wants to expand into a new neighborhood. To maximize
 * the number of clients, the new branch should be at a distance of no more
 * than K from all the houses in the neighborhood. A is a matrix of size N x M,
 * representing the neighborhood as a rectangular grid, in which each cell is
 * either 0 (empty) or 1 (a house). The distance between 2 cells is calculated
 * as the minimum number of cell borders (regardless of wether the cells on
 * the way are empty or occupied) that one has to cross to move from the source
 * to the target cell (without moving through corners). A store can be only
 * built on an empty plot. How many suitable locations are there?
 *
 * For example, given K = 2 and matrix A = [ [0,0,0,0], [0,0,1,0], [1,0,0,1] ],
 * houses are located in cells with coordinates (2, 3), (3, 1), and (3, 4). We
 * can build a new store on 2 empty plots that are close enough to all the
 * houses. The first possible empty plot is located at (3, 2). The distance to
 * the first house at (2, 3) is 2, the distance to the second house at (3, 1)
 * is 1, and the third house at (3, 4) is at a distance of 2. The second
 * possible empty plot is located at (3, 3). The distances to the first,
 * second, and third houses are respectively, 1, 2, and 1.
 *
 * Write a function which, given a positive integer K and matrix A of size
 * N x M, returns the number of empty plots that are close enough to all the
 * houses.
 *
 * Examples:
 *
 * 1. Given K = 2 and A = [[0,0,0,0],[0,0,1,0],[1,0,0,1]], the function should
 * return 2, as explained above.
 *
 * 2. Given K = 1 and A = [[0,1], [0,0]], the function should return 2. We can
 * build a store on empty plots at (1, 1) and (2, 2).
 *
 * 3. Given K = 4 and A = [[0,0,0,1], [0,1,0,0], [0,0,1,0],[1,0,0,0],[0,0,0,0]]
 * the function should return 8. Stores can be built on the following plots:
 * (1, 1), (1, 2), (2, 1), (2, 3), (3, 2), (3, 4), (4, 3), and (4, 4).
 *
 * Write an efficient algorithm for the following assumptions:
 *
 * K is an integer within the range [1..800];
 * N and M are integers within the range [2..400];
 * Each element of matrix A is an integer within the range [0..1];
 */

#include <vector>

using std::vector;

int NumberOfBanks(int K, vector<vector<int>>& A)
{
    return 0;
}

int main()
{
    return 0;
}
